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
#include "plotitem.h"
#include "lineitem.h"

namespace QOGraphics
{

// constants
static const double TICK_TO_LABELS_SPACING	= 3; ///< Margin between ticks and labels [px]
static const double TICK_TO_AXIS_LABEL_SPACING = 20; ///< Spacing from ticks to axis label
static const double X_LABELS_MARGIN		= 30;	///< Margin reserved for x axis labels
static const double Y_LABELS_MARGIN		= 50;	///< Margin reserved for y axis labels


// ============================================================================
/// Constructor
AxesItem::AxesItem( Figure* pFigure,  QGraphicsItem * parent /*= NULL*/ )
	: UIItem(parent), _pFigure( pFigure )
{
	_size = QSize( 100, 100 );
	
	// intialize pointer proerties
	pLabelX = NULL;
	pLabelY = NULL;
	pTitle = NULL;
}

// ============================================================================
/// Destructor
AxesItem::~AxesItem()
{
	// nope
}

// ============================================================================
/// Sets axes size
/*
void AxesItem::setSize( const QSizeF& size )
{
	_size = size;
	recalculateTicks();
	prepareGeometryChange();
}
*/

// ============================================================================
/// Paints item on scene
void AxesItem::paint
	( QPainter *pPainter
	, const QStyleOptionGraphicsItem* /*pOption*/
	, QWidget * /*pWidget*/ /*= NULL*/ )
{
	drawBox( pPainter );
	drawXAxis( pPainter );
	drawYAxis( pPainter );
}

// ============================================================================
/// Finds position of the inner box, an which data are painted
QRectF AxesItem::plotBox() const
{
	/* TODO remove
	double margin = 0.1; // default margin as size fraction
	
	// calculate minimal allowed margins
	
	// Top - title and X labels when X axis on top
	double topMargin = _size.height() * margin;
	
	topMargin = qMax( topMargin, pTitle->item()->boundingRect().height() );
	
	// Bottom - X labels
	double bottomMargin =  _size.height() * margin;
	
	bottomMargin = qMax( bottomMargin, X_LABELS_MARGIN + pLabelX->item()->boundingRect().height() );
	
	
	// Left - y labels
	
	double leftMargin = _size.width() * margin;
	leftMargin = qMax( leftMargin, Y_LABELS_MARGIN + pLabelY->item()->boundingRect().width() );
	
	// Right - y labels
	double rightMargin = _size.width() * margin;
	
	
	// create rectangle
	
	return QRectF( leftMargin, topMargin, 
		_size.width() - leftMargin - rightMargin, _size.height() - bottomMargin - topMargin );
	*/
	
	// plot box is described by _size and positioned at item orgin now.
	return QRectF( 0, 0, _size.width(), _size.height() );
	
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
	
	pPainter->drawRect( plotBox() );
}

// ============================================================================
/// Reclaculates ticks, if in auto mode.
void AxesItem::recalculateTicks()
{
	QRectF boxRect = plotBox();
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
	QRectF box = plotBox();
	
	QColor c = xcolor;
	pPainter->setPen( pen( c, pPainter->device() ) );
	pPainter->setFont( font() );
	
	// draw at the bottom of the box TODO add top|bottom property
	
	// line
	pPainter->drawLine( QLineF( box.left(), box.bottom(), box.right(), box.bottom() ) );
		
	// draw ticks
	
	for ( int i = 0; i < xtick.vectorSize(); i++ )
	{
		double tickPos = xtick.vectorValue( i + 1 );
		
		QPointF pixelPos( plotToPixel( QPointF( tickPos, 0 ) ).x()
			, box.bottom() );
		
		// draw tick
		pPainter->drawLine( pixelPos, pixelPos + QPointF( 0, tickLength() ) );
		
		// draw text
		QString label;
		label.sprintf("%.4g", tickPos );
		double maxTextWidth = 100;
		double maxTextHeight = 50;
		
		QRectF textRect( pixelPos.x() - maxTextWidth / 2
			, pixelPos.y() + tickLength() + TICK_TO_LABELS_SPACING, maxTextWidth, maxTextHeight );
			
		pPainter->drawText( textRect, Qt::AlignHCenter|Qt::AlignTop, label );
		
	}
	
}

// ============================================================================
/// Draws Y axis, with ticks and label
void AxesItem::drawYAxis( QPainter *pPainter )
{
	QRectF box = plotBox();
	
	QColor c = ycolor;
	pPainter->setPen( pen( c, pPainter->device() ) );
	
	// draw at the bottom of the box TODO add top|bottom property
	
	// line
	pPainter->drawLine( QLineF( box.left(), box.bottom(), box.left(), box.top() ) );
		
	for ( int i = 0; i < ytick.vectorSize(); i++ )
	{
		double tickPos = ytick.vectorValue( i + 1 );
		
		QPointF pixelPos(  box.left(), plotToPixel( QPointF( 0, tickPos ) ).y() );
		
		// draw tick
		pPainter->drawLine( pixelPos, pixelPos + QPointF( -tickLength(), 0 ) );
		
		// draw text
		QString label;
		label.sprintf("%.4g", tickPos );
		double maxTextWidth = 100;
		double maxTextHeight = 50;
		
		QRectF textRect( pixelPos.x() - maxTextWidth - tickLength() - TICK_TO_LABELS_SPACING,
			pixelPos.y() - maxTextHeight/ 2, maxTextWidth, maxTextHeight );
			
		pPainter->drawText( textRect, Qt::AlignRight|Qt::AlignVCenter, label );
		
	}
	
}

// ============================================================================
/// Converts plot point to pixel.
QPointF AxesItem::plotToPixel( const QPointF& p ) const
{
	double xmin = xlim.vectorValue( 1 );
	double xmax = xlim.vectorValue( 2 );
	double ymin = ylim.vectorValue( 1 );
	double ymax = ylim.vectorValue( 2 );
	
	// find coordinates relative to plot box
	QRectF box = plotBox();
	double xPixelsPerUnit = box.width() / ( xmax - xmin );
	double yPixelsPerUnit = box.height() / ( ymax - ymin );
	
	
	double x = xdir == Normal 
		? ( p.x() - xmin ) * xPixelsPerUnit
		: box.width() - ( p.x() - xmin ) * xPixelsPerUnit;
		
	double y = ydir == Normal
		? box.height() - ( p.y() - ymin ) * yPixelsPerUnit
		: ( p.y() - ymin ) * yPixelsPerUnit;

	// return plot box coorindates trnalsated to axes coordinates
	return QPointF( x, y ) + box.topLeft();
}

// ============================================================================
/// Converts pixel pos to plot position coordinates.
QPointF AxesItem::pixelToPlot( const QPointF& pixel ) const
{
	double xmin = xlim.vectorValue( 1 );
	double xmax = xlim.vectorValue( 2 );
	double ymin = ylim.vectorValue( 1 );
	double ymax = ylim.vectorValue( 2 );
	
	// get coordinates relative to plot box
	QRectF box = plotBox();
	QPointF p = pixel - box.topLeft(); // pixel relative t plot box;
	double xPixelsPerUnit = box.width() / ( xmax - xmin );
	double yPixelsPerUnit = box.height() / ( ymax - ymin );
	
	double x = xdir == Normal
		? xmin + p.x() / xPixelsPerUnit
		: xmax - p.x() / xPixelsPerUnit;
	
	double y = ydir == Normal
		? ymax - p.y() / yPixelsPerUnit
		: ymin + p.y() / yPixelsPerUnit;
	
	return QPointF( x, y );
}

// ============================================================================
/// Updates child element position after own (or they) geometry change.
void AxesItem::updateChildPositions()
{
	QRectF box = plotBox();
	
	// first - update position of constant elements
	
	setPixelPositon( (PlotItem*)pLabelX->item(), QPointF( box.left() + box.width()/2, box.bottom() + TICK_TO_AXIS_LABEL_SPACING ) );
	setPixelPositon( (PlotItem*)pLabelY->item(), QPointF( box.left() - Y_LABELS_MARGIN, box.top() + box.height() / 2 ) );
	setPixelPositon( (PlotItem*)pTitle->item(), QPointF( box.left() +  box.width()/2, box.top() ) );
	// then - all others
	
	QList<QGraphicsItem *> items = children();
	
	foreach( QGraphicsItem* pItem, items )
	{
		PlotItem* pPlotItem = dynamic_cast<PlotItem*>( pItem );
		if ( pPlotItem )
		{
			// update position
			if ( pPlotItem->usePlotCoordinates == On )
			{
				double x = pPlotItem->position.vectorValue( 1 );
				double y = pPlotItem->position.vectorValue( 2 );
				
				QPointF pixel = plotToPixel( QPointF(x, y) );
				
				pPlotItem->setPos( pixel );
			}
			// set clipping rectangle
			pPlotItem->setPlotBox( pPlotItem->mapFromParent( box ).boundingRect() );
		}
	}
}

// ============================================================================
/// Sets plot item position expresed in pixels insted of plot coords.
/// It also sets item's 'position' property to appropriate plot position coords.
/// Does not change postion of items whcih 'usePlotCoordinates' was turned on.
void AxesItem::setPixelPositon( PlotItem* pItem, QPointF pos )
{
	if ( pItem->usePlotCoordinates == Off )
	{
		pItem->setPos( pos );
		
		QPointF plotPos = pixelToPlot( pos );
		
		pItem->position.setVectorValue( 1, plotPos.x() );
		pItem->position.setVectorValue( 2, plotPos.y() );
		pItem->position.setVectorValue( 3, 0.0 );
	}
}

// ============================================================================
/// Updatex XLim/YLim if in automatic mode
void AxesItem::dataChanged()
{
	// find data boundary from lines
	
	QList<QGraphicsItem *> items = children();
	int linesFound = 0;
	QRectF dataBoundingRect;
	
	foreach( QGraphicsItem* pItem, items )
	{
		LineItem* pLineItem = dynamic_cast<LineItem*>( pItem );
		if ( pLineItem )
		{
			if ( linesFound == 0 )
			{
				dataBoundingRect = pLineItem->dataBoundingRect();
			}
			else
			{
				dataBoundingRect |= pLineItem->dataBoundingRect();
			}
			linesFound++;
		}
	}
	
	// apply to axes
	if ( linesFound > 0 )
	{
		dataBoundingRect = dataBoundingRect.normalized();
		if ( xlimMode == Auto )
		{
			xlim.setVectorValue( 1, dataBoundingRect.left() );
			xlim.setVectorValue( 2, dataBoundingRect.right() );
		}
		if ( ylimMode == Auto )
		{
			ylim.setVectorValue( 1, dataBoundingRect.top() );
			ylim.setVectorValue( 2, dataBoundingRect.bottom() );
		}
		
		recalculateTicks();
	}

}

// ============================================================================
/// Updates size to fiogure size and positioin/units properties
void AxesItem::updateSize()
{
	Q_ASSERT( position.vectorSize() >= 4 );
	
	double left, bottom, width, height;
	
	if ( units == Normalized )
	{
		left	= _figureRect.left() + _figureRect.width() * position.vectorValue( 1 );
		bottom	= _figureRect.bottom() - _figureRect.height() * position.vectorValue( 2 );
		width	= _figureRect.width() * position.vectorValue( 3 );
		height	= _figureRect.height() * position.vectorValue( 4 );
		
		/*qDebug("left: %f (%f of %d), bottom: %f (%f of %d), height: %f (%f of %d)", left, position.vectorValue( 1 ),_figureRect.width(),
			 bottom, position.vectorValue( 2 ), _figureRect.height(),
			 height, position.vectorValue( 4 ), _figureRect.height()
			 );*/
	}
	else if ( units == Pixels )
	{
		left	= _figureRect.left() + position.vectorValue( 1 );
		bottom	= _figureRect.bottom() - position.vectorValue( 2 );
		width	= position.vectorValue( 3 );
		height	= position.vectorValue( 4 );
		
	}
	else
	{
		qWarning("Units other than normalized and pixel not supported currently");
		return;
	}
	
	setPos( left, bottom - height );
	_size = QSizeF( width, height );
	recalculateTicks();
	prepareGeometryChange();
	updateChildPositions();

	update();
}

// ============================================================================
/// Axes bounding rectangle. Adds margins to plot box
QRectF AxesItem::boundingRect() const
{
	
	// Top - title and X labels when X axis on top
	double topMargin = X_LABELS_MARGIN + pTitle->item()->boundingRect().height();
	
	// Bottom - X labels
	double bottomMargin = X_LABELS_MARGIN + pLabelX->item()->boundingRect().height();
	
	
	// Left - y labels
	double leftMargin = Y_LABELS_MARGIN + pLabelY->item()->boundingRect().width();
	
	// Right - y labels
	double rightMargin = Y_LABELS_MARGIN;
	
	
	// create rectangle
	
	return QRectF( -leftMargin, -topMargin, 
		_size.width() + leftMargin + rightMargin, _size.height() + bottomMargin + topMargin );
	

}

} // namespace
