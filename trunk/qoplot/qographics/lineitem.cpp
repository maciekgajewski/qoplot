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
#include <QPainterPath>

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
		pPainter->setPen( pen( color, pPainter->device() ) );
		
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
	
	QRectF r =  mapFromParent( axesRect ).boundingRect();
	return r;
}

// ============================================================================
/// Draws marker at specified location using item's marker settings
void LineItem::drawMarker( QPainter* pPainter, const QPointF& pos )
{
	// do nothing if no markers required
	if ( marker == None )
	{
		return;
	}
	
	double size = ptToPixel( markerSize, pPainter->device() );
	double half = size/2;
	
	pPainter->save();
	
	// set pen and brush
	QPen p = pen( markerEdgeColor, pPainter->device() );
	p.setStyle( Qt::SolidLine ); // forces solid line
	pPainter->setPen( p );
	pPainter->setBrush( QColor( markerFaceColor ) );
	
	QPainterPath path;
	switch( marker )
	{
		case Plus:
			path.moveTo( 0, -half );
			path.lineTo( 0, half ); // |
			
			path.moveTo( -half, 0 );
			path.lineTo( half, 0 );// --
			break;
			
		case Circle:
			path.addEllipse( -half, -half, size, size );
			break;
			
		case Asterix:
			path.moveTo( -half, 0 );
			path.lineTo( half, 0 ); //--
			
			path.moveTo( -half/2, -half );
			path.lineTo( half/2, half ); // /
			
			path.moveTo( -half/2, half );
			path.lineTo( half/2, -half ); // 
			break;
		
		default: // just use point as default
		case Point:
			path.addEllipse( -half/3, -half/3, size/3, size/3 ); // 1/3 of cicrcle
			break;
			
		case Cross:
			path.moveTo( -half, -half );
			path.lineTo( half, half ); // /
			
			path.moveTo( -half, half );
			path.lineTo( half, -half ); // 
			break;
			
		case Square:
			path.addRect( -half, -half, size, size );
			break;
			
		case Diamond:
			path.moveTo( 0, -half );
			path.lineTo( -half, 0 );
			path.lineTo( 0, half );
			path.lineTo( half, 0 );
			path.closeSubpath();
			break;
			
		case TriangleUp:
			path.moveTo( -half, -half );
			path.lineTo( 0, half );
			path.lineTo( half, -half );
			path.closeSubpath();
			break;
			
		case TriangleDown:
			path.moveTo( -half, half );
			path.lineTo( 0, -half );
			path.lineTo( half, half );
			path.closeSubpath();
			break;
			
		case TriangleLeft:
			path.moveTo( half, half );
			path.lineTo( half, -half );
			path.lineTo( -half, 0 );
			path.closeSubpath();
			break;
			
		case TriangleRight:
			path.moveTo( -half, half );
			path.lineTo( -half, -half );
			path.lineTo( half, 0 );
			path.closeSubpath();
			break;
			
		case Pentagram:
			// coordinates generated with octave :)
			
			path.moveTo( half *   -5.8779e-01, half *    8.0902e-01 );
			path.lineTo( half *   -3.8042e-01, half *    1.2361e-01 );
			path.lineTo( half *   -9.5106e-01, half *   -3.0902e-01 );
			path.lineTo( half *   -2.3511e-01, half *   -3.2361e-01 );
			path.lineTo( half *   -1.8369e-16, half *   -1.0000e+00 );
			path.lineTo( half *    2.3511e-01, half *   -3.2361e-01 );
			path.lineTo( half *    9.5106e-01, half *   -3.0902e-01 );
			path.lineTo( half *    3.8042e-01, half *    1.2361e-01 );
			path.lineTo( half *    5.8779e-01, half *    8.0902e-01 );
			path.lineTo( half *    1.2246e-16, half *    4.0000e-01 );
			path.closeSubpath();
			break;
			
		case Hexagram:
			path.moveTo( half * 8.6603e-01   , half * 5.0000e-01 );
			path.lineTo( half * 2.5000e-01   , half * 4.3301e-01 );
			path.lineTo( half * 6.1230e-17   , half * 1.0000e+00 );
			path.lineTo( half * -2.5000e-01   , half * 4.3301e-01 );
			path.lineTo( half * -8.6603e-01   , half * 5.0000e-01 );
			path.lineTo( half * -5.0000e-01   , half * 6.1230e-17 );
			path.lineTo( half * -8.6603e-01  , half * -5.0000e-01 );
			path.lineTo( half * -2.5000e-01  , half * -4.3301e-01 );
			path.lineTo( half * -1.8369e-16  , half * -1.0000e+00 );
			path.lineTo( half * 2.5000e-01  , half * -4.3301e-01 );
			path.lineTo( half * 8.6603e-01  , half * -5.0000e-01 );
			path.lineTo( half * 5.0000e-01  , half * -1.2246e-16 );
			path.closeSubpath();
			break;
	} // marker switch
	pPainter->translate( pos );
	pPainter->drawPath( path );
	pPainter->restore();
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

// ============================================================================
/// Draws line icon used in legend.
void LineItem::drawIcon( QPainter* pPainter, const QRectF& rect )
{
	QPen linePen = pen( color, pPainter->device() );
	
	pPainter->setPen( linePen );
	
	// draw line
	pPainter->drawLine( QPointF( rect.left(), rect.top() + rect.height()/2 ),
		 QPointF( rect.right(), rect.top() + rect.height()/2 ) );
		 
	// draw marker
	drawMarker( pPainter, QPointF( rect.left() + rect.width()/2, rect.top() + rect.height()/2 ) );
}

}
