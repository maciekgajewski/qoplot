// textitem.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#include <QFontMetricsF>
#include <QPainter>

#include "textitem.h"

namespace QOGraphics 
{

// ============================================================================
// Constructor
TextItem::TextItem() : PlotItem()
{
	// nothing
}

// ============================================================================
// Destructor
TextItem::~TextItem()
{
	// nothing
}

// ============================================================================
/// Paints item
void TextItem::paint
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
	
		// transform
		QMatrix matrix;
		pPainter->rotate( -rotation );
		pPainter->translate( alignTranlsation() );
		
		// draw frame
		QRectF extent = textExtent();
		QRectF frame = QRectF( -margin, -margin, extent.width() + 2*margin, extent.height() + 2*margin );
		
		pPainter->setPen( pen( QColor(edgeColor) ) );
		pPainter->setBrush( QColor( backgroundColor ) );
		pPainter->drawRect( frame );
	
		// draw text
		pPainter->setPen( QColor( color ) );
		pPainter->setFont( font() );
		pPainter->drawText( 0, extent.height(), string );
	pPainter->restore();
}
	
// ============================================================================
/// Returns item's bounding rectangle
QRectF TextItem::boundingRect() const
{
	// get extent
	QRectF extent = textExtent();
	
	// get margin
	double m = margin + lineWidth;
	
	// create bounding rect by adding margin to extent
	QRectF br = QRectF( -m, -m, extent.width() + 2*m, extent.height() + 2*m );
	
	// apply alignment translation
	br.translate( alignTranlsation() );
	
	// rotate!
	QMatrix matrix;
	matrix.rotate( -rotation );
	return matrix.mapRect( br );
}

// ============================================================================
/// Fints text extent, from text's top-left corner.
QRectF TextItem::textExtent() const
{
	// get text extent
	QFontMetricsF metrics( font() );
	
	return metrics.tightBoundingRect( string );

}

// ============================================================================
/// Finds transformation that has to be applied to text rect to get desired alignment.
/// It is assumed that without translation text will be paited aligned left-cap
QPointF TextItem::alignTranlsation() const
{
	QRectF extent = textExtent();
	
	double w = extent.width();
	double h = extent.height();
	
	// get margin
	double m = margin + lineWidth;
	
	// find x and y
	double x = 0.0, y = 0.0;
		
	switch( int(horizontalAlignment) )
	{
		case Left:
			x = 0.0;
			break;
		case Center:
			x = -w / 2;
			break;
		case Right:
			x = -w;
	}
	
	switch( int ( verticalAlignment ) )
	{
		case Top:
			y = m;
			break;
		case Cap:
			y = 0;
			break;
		case Middle:
			y = -h/2;
			break;
		case Baseline:
			y = -h;
			break;
		case Bottom:
			y = -h-m;
	}

	return QPointF( x, y );
}

}
