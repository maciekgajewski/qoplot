// lineitem.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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

#include <QPainter>

#include "lineitem.h"
#include "axesitem.h"

namespace QOGraphics
{

// ============================================================================
/// Constructor
LineItem::LineItem( QGraphicsItem* parent ): PlotItem( parent )
{
	// nope
}

// ============================================================================
/// Destructor
LineItem::~LineItem()
{
	// nope
}


// ============================================================================
/// Paints item
void LineItem::paint
	( QPainter *pPainter
	, const QStyleOptionGraphicsItem* /*option*/
	, QWidget * /*widget*/ /*= NULL*/ )
{
	AxesItem* pAxesItem = axesItem();
	Q_ASSERT( pAxesItem );
	
	// get numebr of points
	int points = qMin( xdata.vectorSize(), ydata.vectorSize() );
	
	if ( points == 0 )
	{
		return; // nothing to do
	}
	
	pPainter->save();
	
		// turn on clipping when appropriate
		if ( clipping == On )
		{
			pPainter->setClipRect( plotBox(), Qt::IntersectClip );
		}
		
		// set pen
		pPainter->setPen( pen( color ) );
		
		// first point
		int i = 0;
		double x = xdata.vectorValue( i+1 ); 
		double y = ydata.vectorValue( i+1); 
		QPointF point = mapFromParent( pAxesItem->plotToPixel( QPointF( x, y ) ) );
		
		drawMarker( pPainter, point ); // TODO make markers a child graphic items
		
		// further points and line segments
		for ( i++; i < points; i++)
		{
			double x = xdata.vectorValue( i+1 ); 
			double y = ydata.vectorValue( i+1 ); 
			QPointF nextPoint = mapFromParent( pAxesItem->plotToPixel( QPointF( x, y ) ) );
			
			
			// line segment
			pPainter->drawLine( point, nextPoint );
			
			drawMarker( pPainter, nextPoint );
			
			point = nextPoint;
		}
		
	pPainter->restore();
}
	
// ============================================================================
/// Returns item bounding rectangle
QRectF LineItem::boundingRect() const
{
	// be easy, return entire parent axes rectangle
	
	QRectF axesRect = axesItem()->boundingRect();
	
	return mapFromParent( axesRect ).boundingRect();
}

// ============================================================================
/// Draws marker at specified location using item's marker settings
void LineItem::drawMarker( QPainter* painter, const QPointF& pos )
{
	// TODO
}

// ============================================================================
/// Returns data bounding rect.
QRectF LineItem::dataBoundingRect() const
{
	int points = qMin( xdata.vectorSize(), ydata.vectorSize() );
	
	if ( points == 0 )
	{
		return QRectF();
	}
	
	double x = xdata.vectorValue( 1 );
	double y = ydata.vectorValue( 1 );
	double minx = x, maxx = x;
	double miny = y, maxy = y;
	
	for ( int i = 2; i < points + 1; i++ )
	{
		x = xdata.vectorValue( i );
		y = ydata.vectorValue( i );
		
		maxx = qMax( maxx, x );
		minx = qMin( minx, x );
		
		maxy = qMax( maxy, y );
		miny = qMin( miny, y );
	}
	
	return QRectF( minx, miny, maxx-minx, maxy-miny);
}

// ============================================================================
/// Informs axes thta data hase changed.
void LineItem::dataChanged()
{
	axesItem()->dataChanged();
}

}
