// axesitem.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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

namespace QOGraphics
{

// constants
static double TICK_TO_LABELS_MARGIN	= 3; ///< Margin between ticks and labels [px]


// ============================================================================
/// Constructor
AxesItem::AxesItem( QGraphicsItem * parent /*= NULL*/ ) : QGraphicsItem(parent)
{
	_size = QSize( 100, 100 );
}

// ============================================================================
/// Destructor
AxesItem::~AxesItem()
{
	// nope
}

// ============================================================================
/// Sets axes size
void AxesItem::setSize( const QSizeF& size )
{
	_size = size;
	recalculateTicks();
	prepareGeometryChange();
}

// ============================================================================
/// Paints item on scene
void AxesItem::paint
	( QPainter *pPainter
	, const QStyleOptionGraphicsItem* /*pOption*/
	, QWidget * /*pWidget*/ /*= NULL*/ )
{
	pPainter->setRenderHint( QPainter::Antialiasing, true );
	
	drawBox( pPainter );
	drawXAxis( pPainter );
	drawYAxis( pPainter );
}

// ============================================================================
/// Finds position of the inner box, an which data are painted
QRectF AxesItem::innerBox() const
{
	// simple impelemtation, just leaves 10% margins around box
	
	double margin = 0.1;
	
	return QRectF( _size.width() * margin, _size.height() * margin,
		_size.width() * (1-2*margin), _size.height() * (1-2*margin) );
}

// ============================================================================
/// Draws axes background box.
void AxesItem::drawBox( QPainter *pPainter )
{
	if ( box )
	{
		pPainter->setPen( QPen( Qt::black, 1 ) );
	}
	else
	{
		pPainter->setPen( Qt::NoPen );
	}
	pPainter->setBrush( color.color() );
	
	pPainter->drawRect( innerBox() );
}

// ============================================================================
/// Reclaculates ticks, if in auto mode.
void AxesItem::recalculateTicks()
{
	QRectF boxRect = innerBox();
	double minSpacing = 30.0; // min tick spacing [px] // TODO deduce from font size
	
	if ( xtickMode == Auto )
	{
		double axisLengthPx = boxRect.width(); // axis length in pixels
		double axisLength = xlim.vectorValue( 2 ) - xlim.vectorValue( 1 );
		double spacing = findSpacing( axisLength, axisLengthPx, minSpacing );
		
		xtick = generateTicks( xlim.vectorValue( 1 ), xlim.vectorValue( 2 ), spacing );
	}
	
	if ( ytickMode == Auto )
	{
		double axisLengthPx = boxRect.height(); // axis length in pixels
		double axisLength = ylim.vectorValue( 2 ) - ylim.vectorValue( 1 );
		double spacing = findSpacing( axisLength, axisLengthPx, minSpacing );
		
		ytick = generateTicks( ylim.vectorValue( 1 ), ylim.vectorValue( 2 ), spacing );
	}
}

// ============================================================================
/// Finds optimal spacing between ticks
/// len - axis len (in units)
/// pixels - axis len in pixels
/// minPixels - min allowed spacing
///\returns optimal spacing, in units
double AxesItem::findSpacing( double len, double pixels, double minPixels )
{
	double pixelsPerUnit = pixels / len;
	
	double rough = minPixels / pixelsPerUnit;
	
	// find lowerbound
	double rounded = pow( 10, floor( log10( rough ) ) );
	
	// 1 -> 2
	if ( ( rounded * pixelsPerUnit ) < minPixels )
	{
		rounded *= 2.0;
	}
	
	// 2->5
	if ( ( rounded * pixelsPerUnit ) < minPixels )
	{
		rounded *= 2.5;
	}
	
	// 5->10
	if ( ( rounded * pixelsPerUnit ) < minPixels )
	{
		rounded *= 2;
	}
	
	return rounded;
}

// ============================================================================
//. Generates vector with ticks for axis defined by min and max, and with specified spacing
Matrix AxesItem::generateTicks( double min, double max, double spacing )
{
	QList<double> ticks;
	
	// find first
	double minMinusDelta = min - (max-min)*0.0001;
	double first = ceil( minMinusDelta / spacing ) * spacing;
	double tick = first;
	
	double maxPlusDelta = min + (max-min)*1.0001; // sometimes last ticks runs away
	while( tick <= maxPlusDelta  )
	{
		ticks.append( tick );
		tick += spacing;
	}
	
	Matrix v( 1, ticks.size() );
	
	for ( int i = 0; i < ticks.size(); i++ )
	{
		v.setVectorValue( i+1, ticks[i] );
	}
	
	return v;
}

// ============================================================================
/// Draws X axis, with ticks and label
void AxesItem::drawXAxis( QPainter *pPainter )
{
	QRectF box = innerBox();
	
	QColor c = xcolor;
	pPainter->setPen( QPen( c, 1 ) );
	
	// draw at the bottom of the box TODO add top|bottom property
	
	// line
	pPainter->drawLine( QLineF( box.left(), box.bottom(), box.right(), box.bottom() ) );
		
	// draw ticks
	double tickLength = 5.0; // [px] TODO calculate from property
	
	for ( int i = 0; i < xtick.vectorSize(); i++ )
	{
		double tickPos = xtick.vectorValue( i + 1 );
		
		QPointF pixelPos(  box.left() + plotToPixel( QPointF( tickPos, 0 ) ).x()
			, box.bottom() );
		
		// draw tick
		pPainter->drawLine( pixelPos, pixelPos + QPointF( 0, tickLength ) );
		
		// draw text
		QString label;
		label.sprintf("%g", tickPos );
		double maxTextWidth = 100;
		double maxTextHeight = 50;
		
		QRectF textRect( pixelPos.x() - maxTextWidth / 2
			, pixelPos.y() + tickLength + TICK_TO_LABELS_MARGIN, maxTextWidth, maxTextHeight );
			
		pPainter->drawText( textRect, Qt::AlignHCenter|Qt::AlignTop, label );
		
	}
}

// ============================================================================
/// Draws Y axis, with ticks and label
void AxesItem::drawYAxis( QPainter *pPainter )
{
	QRectF box = innerBox();
	
	QColor c = ycolor;
	pPainter->setPen( QPen( c, 1 ) );
	
	// draw at the bottom of the box TODO add top|bottom property
	
	// line
	pPainter->drawLine( QLineF( box.left(), box.bottom(), box.left(), box.top() ) );
		
	// draw ticks
	double tickLength = 5.0; // [px] TODO calculate from property
	
	for ( int i = 0; i < ytick.vectorSize(); i++ )
	{
		double tickPos = ytick.vectorValue( i + 1 );
		
		QPointF pixelPos(  box.left(), box.top() + plotToPixel( QPointF( 0, tickPos ) ).y() );;
		
		// draw tick
		pPainter->drawLine( pixelPos, pixelPos + QPointF( -tickLength, 0 ) );
		
		// draw text
		QString label;
		label.sprintf("%g", tickPos );
		double maxTextWidth = 100;
		double maxTextHeight = 50;
		
		QRectF textRect( pixelPos.x() - maxTextWidth - tickLength - TICK_TO_LABELS_MARGIN,
			pixelPos.y() - maxTextHeight/ 2, maxTextWidth, maxTextHeight );
			
		pPainter->drawText( textRect, Qt::AlignRight|Qt::AlignVCenter, label );
		
	}
}

// ============================================================================
/// Converts plot point to pixel. Pixel is relative to inner box's top left corner
QPointF AxesItem::plotToPixel( const QPointF& p ) const
{
	double xmin = xlim.vectorValue( 1 );
	double xmax = xlim.vectorValue( 2 );
	double ymin = ylim.vectorValue( 1 );
	double ymax = ylim.vectorValue( 2 );
	
	QRectF box = innerBox();
	
	double xPixelsPerUnit = box.width() / ( xmax - xmin );
	double yPixelsPerUnit = box.height() / ( ymax - ymin );

	return QPointF( ( p.x() - xmin ) * xPixelsPerUnit, box.height() - ( p.y() - ymin ) * yPixelsPerUnit ); // TODO use YDir, XDir properties
}

// ============================================================================
/// Converts pixel pos to plot position coordinates.
QPointF AxesItem::pixelToPlot( const QPointF& ) const
{
	// TODO
	return QPointF();
}

} // namespace
