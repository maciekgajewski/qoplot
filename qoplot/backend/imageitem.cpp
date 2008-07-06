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
#include "figurewindow.h"

namespace QOGraphics
{

// ============================================================================
// Constructor
ImageItem::ImageItem( AxesItem* parent): PlotItem(parent)
{
	_pProperties = NULL;
	setZValue( 0.4 ); // bit below other objects
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
	image::properties* pProps = properties();
	// do nathing if called before properties provided
	if ( ! pProps ) return;
	
	std::string clipping = pProps->get_clipping();
	
	pPainter->save();
	
		// set clipping
		if ( clipping == "on" )
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
	image::properties* pProps = properties();
	
	if ( pProps->get_cdata().ndims() == 3 )
	{
		if ( pProps->get_cdata().is_uint8_type() )
		{
			createUint8RGBImage( pProps->get_cdata().uint8_array_value() );
		}
		else
		{
			createFloatRGBImage( pProps->get_cdata().float_array_value() );
		}
	}
	else
	{
		createColormapImage( pProps->get_cdata().matrix_value() );
	}
}

// ============================================================================
// Copies properties.
void ImageItem::copyProperties( const base_properties* pProps )
{
	if ( _pProperties )
	{
		delete _pProperties;
	}
	
	_pProperties = new image::properties( *dynamic_cast<const image::properties*>( pProps ) );
	propertiesChanged();
}

// ============================================================================
/// Returns rectangle which image occupies on plot plane
QRectF ImageItem::imageRect() const
{
	image::properties* pProps = properties();
	
	// xdata/data
	Matrix xdata = pProps->get_xdata().matrix_value();
	Matrix ydata = pProps->get_ydata().matrix_value();
	// image size
	double imageW = pProps->get_cdata().matrix_value().dim2();
	double imageH = pProps->get_cdata().matrix_value().dim1();
	
	// calculkated below are coordinates of CNETERS OF PIXELS
	// so, at the and, i'm adding half-pixel mrgin around it to get real rect
	
	// x-origin
	double x = 1.0;
	if ( xdata.nelem() > 0 )
	{
		x = xdata.elem( 0 );
	}
	
	// y-origin
	double y = 1.0;
	if ( ydata.nelem() > 0 )
	{
		y = ydata.elem( 0 );
	}
	
	// width
	double w = _image.width();
	if ( xdata.nelem() > 1 )
	{
		w = xdata.elem( 1 ) - x;
	}
	
	// height
	double h = _image.height();
	if ( ydata.nelem() > 1 )
	{
		h = ydata.elem( 1 ) - y;
	}
	
	// find pixel width snd height in plot coordinates
	double xunit = (w+1) / imageW;
	double yunit = (h+1) / imageH;
	
	qDebug("image size: %gx%g", imageW, imageH );
	
	qDebug("image rect: %g,%g %gx%g", x-xunit/2, y-yunit/2, w+xunit/2, h+yunit/2);
	return QRectF( x - xunit/2, y - yunit/2, w + xunit/2, h + yunit/2 );
}

// ============================================================================
/// Handles property change. Re-genrates QImage from data
void ImageItem::propertiesChanged()
{
	PlotItem::propertiesChanged();
	createImage();
}

// ============================================================================
/// Creates colormap image from CData. Uses current figure colormap.
void ImageItem::createColormapImage( const Matrix& cdata )
{
	int w = cdata.dim2();
	int h = cdata.dim1();
	
	if ( (w*h) == 0 )
	{
		_image = QImage(); // null image
		return;
	}
	
	// init Qt image
	_image = QImage( w, h, QImage::Format_RGB32 );
	
	image::properties* pProps = properties();
	
	// get colormap
	figure::properties* pFigProp = figure()->properties();
	
	Matrix colormap = pFigProp->get_colormap().matrix_value();
	int cmlength = colormap.dim1();
	
	// get axes's CLim
	axes::properties* pAxesProps = axesItem()->properties();
	double cmin = pAxesProps->get_clim().matrix_value().elem( 0 );
	double cmax = pAxesProps->get_clim().matrix_value().elem( 1 );
	
	// get mode
	bool scaled = pProps->get_cdatamapping() == "scaled";
	
	// get data
	for ( int y = 0; y < h; y++)
	{
		for( int x = 0; x< w; x++ )
		{
			int colorIndex = 0;
			if ( scaled )
			{
				// mapping scaled to clim
				colorIndex = (int)round(( cdata.elem(y, x)-cmin) / (cmax-cmin)*cmlength);
			}
			else
			{
				// direct index in colormap
				colorIndex = cdata.elem(y, x);
			}
			
			
			if ( colorIndex < 0 ) colorIndex = 0;
			if ( colorIndex >= cmlength ) colorIndex = cmlength-1;
			
			_image.setPixel( x, y, qRgb
					( int( 255*colormap.elem( colorIndex, 0 ) )
					, int( 255*colormap.elem( colorIndex, 1 ) )
					, int( 255*colormap.elem( colorIndex, 2 ) )
					)
				);
		}
	}
	
}


// ============================================================================
/// Creates rgb image from floating-point matrix
void ImageItem::createFloatRGBImage( const FloatNDArray& cdata )
{
	int w = cdata.dim2();
	int h = cdata.dim1();
	
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
			double r = cdata.elem( y, x, 0 );
			double g = cdata.elem( y, x, 1 );
			double b = cdata.elem( y, x, 2 );
			
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

// ============================================================================
/// Creates rgb image from uint8 matrix
void ImageItem::createUint8RGBImage( const uint8NDArray& cdata )
{
	int w = cdata.dim2();
	int h = cdata.dim1();
	
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
			int r = cdata.elem( y, x, 0 );
			int g = cdata.elem( y, x, 1 );
			int b = cdata.elem( y, x, 2 );
			
			_image.setPixel( x, y, qRgb
					( int( r )
					, int( g )
					, int( b )
					)
				);
		}
	}	
}

}
