// imageitem.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//

#include <math.h>

#include <QPainter>

#include "axesitem.h"
#include "imageitem.h"
#include "exceptions.h"

namespace QOGraphics {

// ============================================================================
// Constructor
ImageItem::ImageItem(QGraphicsItem* parent): PlotItem(parent)
{
	// empty
}

// ============================================================================
// Destructor
ImageItem::~ImageItem()
{
	// nic tu nie ma i niczego nie bedzie
}

// ============================================================================
/// Paints item
void ImageItem::paint
	( QPainter *pPainter
	, const QStyleOptionGraphicsItem* /*option*/
	, QWidget * /*widget*/ /*= NULL*/ )
{
	pPainter->save();
	
		// set clipping
		if ( clipping == On )
		{
			pPainter->setClipRect( plotBox(), Qt::IntersectClip );
		}
		
		// get image rectangle in plot coordinates
		QRectF ir = imageRect();
		
		// translate to pixel coordinates
		QPointF tl = axesItem()->plotToPixel( ir.topLeft() ); // top left
		QPointF br = axesItem()->plotToPixel( ir.bottomRight() );// bottom roght
		
		// draw scaled image
		QRectF pixelRect( tl.x(), tl.y(), br.x() - tl.x(), br.y() - tl.y() );
		pPainter->drawImage( pixelRect, _image );
	
	pPainter->restore();
}
	
// ============================================================================
/// Returns item bounding rectangle
QRectF ImageItem::boundingRect() const
{
	// TODO upper bound for now
	
	return plotBox();
}

// ============================================================================
/// Creates image from data, according to current mode.
void ImageItem::createImage()
{
	if( mode == Colormap )			// Colormap mode
	{
		createColormapImage();
	}
	else if ( mode == Intensity )	// Intensity mode
	{
		createIntensityImage();
	}
	else if ( mode == RGB )			// RGB
	{
		createRGBImage();
	}
	else
	{
		qWarning("Other image modes not supported yet");
	}
}

// ============================================================================
/// Returns rectangle which image occupies on plot plane
QRectF ImageItem::imageRect() const
{
	// x-origin
	double x = 0.0;
	if ( xdata.vectorSize() > 0 )
	{
		x = xdata.vectorValue( 1 );
	}
	
	// y-origin
	double y = 0.0;
	if ( ydata.vectorSize() > 0 )
	{
		y = ydata.vectorValue( 1 );
	}
	
	// width
	double w = _image.width();
	if ( xdata.vectorSize() > 1 )
	{
		w = xdata.vectorValue( 2 ) - x;
	}
	
	// height
	double h = _image.height();
	if ( ydata.vectorSize() > 1 )
	{
		h = ydata.vectorValue( 2 ) - y;
	}
	
	return QRectF( x, y, w, h );
}

// ============================================================================
/// Handles property change. Re-genrates QImage form data
void ImageItem::propertyChanged()
{
	PlotItem::propertyChanged();
	createImage();
}

// ============================================================================
/// Creates colormap image from CData. Uses current figure colormap.
void ImageItem::createColormapImage()
{
	int w = cdata.cols();
	int h = cdata.rows();
	
	if ( (w*h) == 0 )
	{
		_image = QImage(); // null image
		return;
	}
	
	// init Qt image
	_image = QImage( w, h, QImage::Format_RGB32 );
	
	// get colormap
	Figure* pFig = figure();
	
	// check colormap validity
	if ( pFig->colorMap().cols() < 3 || pFig->colorMap().rows() < 1 )
	{
		throw Exception("Figure colormap invalid, can't initialize image");
	}
	int cmlength = pFig->colorMap().rows();
	
	// get axes's CLim
	double cmin = axesItem()->clim.vectorValue( 1 );
	double cmax = axesItem()->clim.vectorValue( 2 );
	
	// get data
	for ( int y = 0; y < h; y++)
	{
		for( int x = 0; x< w; x++ )
		{
			int colorIndex = (int)round(( cdata.value(y+1, x+1)-cmin)/(cmax-cmin)*cmlength)+1;
			
			if ( colorIndex < 1 ) colorIndex = 1;
			if ( colorIndex > cmlength ) colorIndex = cmlength;
			
			_image.setPixel( x, y, qRgb
					( int( 255*pFig->colorMap().value( colorIndex, 1 ) )
					, int( 255*pFig->colorMap().value( colorIndex, 2 ) )
					, int( 255*pFig->colorMap().value( colorIndex, 3 ) )
					)
				);
		}
	}
	
}

// ============================================================================
/// Creates intensity image, consisting of grayscasle values from 0.0. to 1.0
void ImageItem::createIntensityImage()
{
	int w = cdata.cols();
	int h = cdata.rows();
	
	if ( (w*h) == 0 )
	{
		_image = QImage(); // null image
		return;
	}
	
	// init Qt image
	_image = QImage( w, h, QImage::Format_RGB32 );
	
	// get data
	for ( int y = 0; y < h; y++)
	{
		for( int x = 0; x< w; x++ )
		{
			double intensity = cdata.value( y+1, x+1 );
			
			if ( intensity < 0.0 ) intensity = 0.0;
			if ( intensity > 1.0 ) intensity = 1.0;
			
			_image.setPixel( x, y, qRgb
					( int( 255*intensity )
					, int( 255*intensity )
					, int( 255*intensity )
					)
				);
		}
	}	
}

// ============================================================================
/// Creates rgb image.
void ImageItem::createRGBImage()
{
	int w = qMin( qMin( cdataR.cols(), cdataG.cols() ), cdataB.cols() );
	int h = qMin( qMin( cdataR.rows(), cdataG.rows() ), cdataB.rows() );
	
	if ( (w*h) == 0 )
	{
		_image = QImage(); // null image
		return;
	}
	
	// init Qt image
	_image = QImage( w, h, QImage::Format_RGB32 );
	
	// get data
	for ( int y = 0; y < h; y++)
	{
		for( int x = 0; x< w; x++ )
		{
			double r = cdataR.value( y+1, x+1 );
			double g = cdataG.value( y+1, x+1 );
			double b = cdataB.value( y+1, x+1 );
			
			if ( r < 0.0 ) r = 0.0;
			if ( r > 1.0 ) r = 1.0;
			
			if ( g < 0.0 ) g = 0.0;
			if ( g > 1.0 ) g = 1.0;
			
			if ( b < 0.0 ) b = 0.0;
			if ( b > 1.0 ) b = 1.0;
			
			_image.setPixel( x, y, qRgb
					( int( 255*r )
					, int( 255*g )
					, int( 255*b )
					)
				);
		}
	}	
}

}
