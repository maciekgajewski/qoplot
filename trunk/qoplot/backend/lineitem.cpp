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
#include "converters.h"

namespace QOGraphics
{

// ============================================================================
/// Constructor
LineItem::LineItem( AxesItem* parent ): PlotItem( parent )
{
	_pProperties = NULL;
	setZValue( 0.5 ); // above axes
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
	line::properties* pProps = properties();
	// do nathing if called before properties provided
	if ( ! pProps ) return;
	
	Matrix xdata = pProps->get_xdata().matrix_value();
	Matrix ydata = pProps->get_ydata().matrix_value();
	QColor color = colorFromOctave( pProps->get_color_rgb() );
	std::string clipping = pProps->get_clipping();

	AxesItem* pAxesItem = axesItem();
	Q_ASSERT( pAxesItem );
	
	// get numebr of points
	int points = qMin( xdata.nelem(), ydata.nelem() );
	
	if ( points == 0 )
	{
		return; // nothing to do
	}
	
	pPainter->save();
	
		// turn on clipping when appropriate
		if ( clipping == "on" )
		{
			pPainter->setClipRect( plotBox(), Qt::IntersectClip );
		}
		
		// set pen
		pPainter->setPen( pen( color, pPainter->device() ) );
		
		// first point
		int i = 0;
		double x = xdata.elem( i ); 
		double y = ydata.elem( i); 
		QPointF point = mapFromParent( pAxesItem->plotToPixel( QPointF( x, y ) ) );
		
		drawMarker( pPainter, point ); // TODO make markers a child graphic items
		
		// further points and line segments
		for ( i++; i < points; i++)
		{
			double x = xdata.elem( i ); 
			double y = ydata.elem( i ); 
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
	line::properties* pProps = properties();
	
	std::string marker = pProps->get_marker();
	double markerSize = pProps->get_markersize();
	QColor markerFaceColor = colorFromOctave( pProps->get_markerfacecolor() );
	
	// edge color
	QColor markerEdgeColor;
	if ( pProps->get_markeredgecolor().is_string() )
	{
		std::string mec = pProps->get_markeredgecolor().string_value();
		if ( mec == "auto" )
		{
			markerEdgeColor = colorFromOctave( pProps->get_color_rgb() );
		}
		else
		{
			markerEdgeColor = Qt::transparent;
		}
	}
	else
	{
		markerEdgeColor = colorFromOctave( pProps->get_markeredgecolor_rgb() );
	}
	
	// do nothing if no markers required
	if ( marker == "none" )
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
	pPainter->setBrush( markerFaceColor );
	
	QPainterPath path;
	if ( marker == "+" )
	{
		path.moveTo( 0, -half );
		path.lineTo( 0, half ); // |
		
		path.moveTo( -half, 0 );
		path.lineTo( half, 0 );// --
	}
	else if ( marker == "o" )
	{		
		path.addEllipse( -half, -half, size, size );
	}		
	else if ( marker == "*" )
	{
		path.moveTo( -half, 0 );
		path.lineTo( half, 0 ); //--
		
		path.moveTo( -half/2, -half );
		path.lineTo( half/2, half ); // /
		
		path.moveTo( -half/2, half );
		path.lineTo( half/2, -half ); // 
	}
	else if ( marker == "." )
	{
		path.addEllipse( -half/3, -half/3, size/3, size/3 ); // 1/3 of cicrcle
	}
	else if ( marker == "x" )
	{	
		path.moveTo( -half, -half );
		path.lineTo( half, half ); // /
		
		path.moveTo( -half, half );
		path.lineTo( half, -half ); // 
	}
	else if ( marker == "s" || marker == "square" )
	{
		path.addRect( -half, -half, size, size );
	}
	else if ( marker == "d" || marker == "diamond" )
	{		
		path.moveTo( 0, -half );
		path.lineTo( -half, 0 );
		path.lineTo( 0, half );
		path.lineTo( half, 0 );
		path.closeSubpath();
	}
	else if ( marker == "^" )
	{
		path.moveTo( -half, -half );
		path.lineTo( 0, half );
		path.lineTo( half, -half );
		path.closeSubpath();
	}
	else if ( marker == "v" )
	{
		path.moveTo( -half, half );
		path.lineTo( 0, -half );
		path.lineTo( half, half );
		path.closeSubpath();
	}
	else if ( marker == "<" )
	{
		path.moveTo( half, half );
		path.lineTo( half, -half );
		path.lineTo( -half, 0 );
		path.closeSubpath();
	}
	else if ( marker == ">" )
	{
		path.moveTo( -half, half );
		path.lineTo( -half, -half );
		path.lineTo( half, 0 );
		path.closeSubpath();
	}
	else if ( marker == "p" || marker == "pentagram" )
	{		
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
	}
	else if ( marker == "h" || marker == "hexagram" )
	{		
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
	} // marker switch
	
	pPainter->translate( pos );
	pPainter->drawPath( path );
	pPainter->restore();
}

// ============================================================================
// Copies porperties.
void LineItem::copyProperties( const base_properties* pProps )
{
	if ( _pProperties )
	{
		delete _pProperties;
	}
	
	_pProperties = new line::properties( *dynamic_cast<const line::properties*>( pProps ) );
	propertiesChanged();
}

}
