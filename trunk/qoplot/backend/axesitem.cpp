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
#include "converters.h"
#include "textitem.h"
#include "lineitem.h"
#include "imageitem.h"

namespace QOGraphics
{

// constants
static const double TICK_TO_LABELS_SPACING	= 3; ///< Margin between ticks and labels [px]
static const double TICK_TO_AXIS_LABEL_SPACING = 20; ///< Spacing from ticks to axis label
static const double X_LABELS_MARGIN		= 30;	///< Margin reserved for x axis labels
static const double Y_LABELS_MARGIN		= 50;	///< Margin reserved for y axis labels


// ============================================================================
/// Constructor
AxesItem::AxesItem( double h, FigureWindow* figure, QGraphicsItem * parent /*= NULL*/ )
	: UIItem( h, figure, parent)
{
	_size = QSize( 100, 100 ); //dumb guess
	
	propertiesChanged();
}

// ============================================================================
/// Destructor
AxesItem::~AxesItem()
{
	// nope
}

// ============================================================================
/// Paints item on scene
void AxesItem::paint
	( QPainter *pPainter
	, const QStyleOptionGraphicsItem* /*pOption*/
	, QWidget * /*pWidget*/ /*= NULL*/ )
{
	gh_manager::lock_guard guard;
	
	drawBox( pPainter );
	drawXAxis( pPainter );
	drawYAxis( pPainter );
}

// ============================================================================
/// Finds position of the inner box, an which data are painted
QRectF AxesItem::plotBox() const
{
	// plot box is described by _size and positioned at item orgin.
	return QRectF( 0, 0, _size.width(), _size.height() );
}

// ============================================================================
/// Draws axes background box.
void AxesItem::drawBox( QPainter *pPainter )
{
	axes::properties* pProps = properties();
	
	if ( pProps->get_box() == "on" )
	{
		pPainter->setPen( QPen( Qt::black, 1 ) );
	}
	else
	{
		pPainter->setPen( Qt::NoPen );
	}
	pPainter->setBrush( colorFromOctave( pProps->get_color() ) );
	
	pPainter->drawRect( plotBox() );
}


// ============================================================================
/// Draws X axis, with ticks and label
void AxesItem::drawXAxis( QPainter *pPainter )
{
	axes::properties* pProps = properties(); // in preparation for thread safe props :)
	
	QRectF box = plotBox();
	
	QColor c = colorFromOctave( pProps->get_xcolor() );
	QPen linePen = pen( c, pPainter->device() );
	pPainter->setPen( linePen );
	QPen gridPen = linePen;
	gridPen.setStyle( styleFromOctave( pProps->get_gridlinestyle() ) );
	pPainter->setFont( font() );
	
	Matrix xtick = pProps->get_xtick().matrix_value();
	
	// draw at the bottom of the box TODO add top|bottom property
	
	// line
	pPainter->drawLine( QLineF( box.left(), box.bottom(), box.right(), box.bottom() ) );
		
	// draw ticks
	
	for ( int i = 0; i < xtick.nelem(); i++ )
	{
		double tickPos = xtick.elem( i );
		
		QPointF pixelPos( plotToPixel( QPointF( tickPos, 0 ) ).x()
			, box.bottom() );
		
		// draw tick
		pPainter->setPen( linePen );
		pPainter->drawLine( pixelPos, pixelPos + QPointF( 0, tickLength() ) );
		
		// draw text
		QString label;
		label.sprintf("%g", tickPos );
		double maxTextWidth = 100;
		double maxTextHeight = 50;
		
		QRectF textRect( pixelPos.x() - maxTextWidth / 2
			, pixelPos.y() + tickLength() + TICK_TO_LABELS_SPACING, maxTextWidth, maxTextHeight );
			
		pPainter->drawText( textRect, Qt::AlignHCenter|Qt::AlignTop, label );
		
		// draw grid line
		pPainter->setPen( gridPen );
		pPainter->drawLine( pixelPos, pixelPos + QPointF( 0, -box.height() ) );
	}
}

// ============================================================================
/// Draws Y axis, with ticks and label
void AxesItem::drawYAxis( QPainter *pPainter )
{
	axes::properties* pProps = properties(); // in preparation for thread safe props :)
	
	QRectF box = plotBox();
	
	QColor c = colorFromOctave( pProps->get_ycolor() );
	QPen linePen = pen( c, pPainter->device() );
	pPainter->setPen( linePen );
	QPen gridPen = linePen;
	gridPen.setStyle( styleFromOctave( pProps->get_gridlinestyle() ) );
	
	Matrix ytick = pProps->get_ytick().matrix_value();
	
	// draw at the bottom of the box TODO add top|bottom property
	
	// line
	pPainter->drawLine( QLineF( box.left(), box.bottom(), box.left(), box.top() ) );
		
	for ( int i = 0; i < ytick.nelem(); i++ )
	{
		double tickPos = ytick.elem( i );
		
		QPointF pixelPos(  box.left(), plotToPixel( QPointF( 0, tickPos ) ).y() );
		
		// draw tick
		pPainter->setPen( linePen );
		pPainter->drawLine( pixelPos, pixelPos + QPointF( -tickLength(), 0 ) );
		
		// draw text
		QString label;
		label.sprintf("%g", tickPos);
		double maxTextWidth = 100;
		double maxTextHeight = 50;
		
		QRectF textRect( pixelPos.x() - maxTextWidth - tickLength() - TICK_TO_LABELS_SPACING,
			pixelPos.y() - maxTextHeight/ 2, maxTextWidth, maxTextHeight );
			
		pPainter->drawText( textRect, Qt::AlignRight|Qt::AlignVCenter, label );
		
		// draw grid line
		pPainter->setPen( gridPen );
		pPainter->drawLine( pixelPos, pixelPos + QPointF( box.width(), 0 ) );
	}
}

// ============================================================================
/// Converts plot point to pixel.
QPointF AxesItem::plotToPixel( const QPointF& p ) const
{
	gh_manager::lock_guard guard;
	axes::properties* pProps = properties();
	
	Matrix xlim = pProps->get_xlim().matrix_value();
	Matrix ylim = pProps->get_ylim().matrix_value();
	
	double xmin = xlim.elem(0);
	double xmax = xlim.elem(1);
	double ymin = ylim.elem(0);
	double ymax = ylim.elem(1);
	
	// find coordinates relative to plot box
	QRectF box = plotBox();
	double xPixelsPerUnit = box.width() / ( xmax - xmin );
	double yPixelsPerUnit = box.height() / ( ymax - ymin );
	
	
	double x = pProps->get_xdir() == "normal" 
		? ( p.x() - xmin ) * xPixelsPerUnit
		: box.width() - ( p.x() - xmin ) * xPixelsPerUnit;
		
	double y = pProps->get_ydir() == "normal" 
		? box.height() - ( p.y() - ymin ) * yPixelsPerUnit
		: ( p.y() - ymin ) * yPixelsPerUnit;

	// return plot box coorindates trnalsated to axes coordinates
	return QPointF( x, y ) + box.topLeft();
}

// ============================================================================
/// Converts pixel pos to plot position coordinates.
QPointF AxesItem::pixelToPlot( const QPointF& pixel ) const
{
	gh_manager::lock_guard guard;
	axes::properties* pProps = properties();
	
	Matrix xlim = pProps->get_xlim().matrix_value();
	Matrix ylim = pProps->get_ylim().matrix_value();
	
	double xmin = xlim.elem(0);
	double xmax = xlim.elem(1);
	double ymin = ylim.elem(0);
	double ymax = ylim.elem(1);
	
	// get coordinates relative to plot box
	QRectF box = plotBox();
	QPointF p = pixel - box.topLeft(); // pixel relative t plot box;
	double xPixelsPerUnit = box.width() / ( xmax - xmin );
	double yPixelsPerUnit = box.height() / ( ymax - ymin );
	
	double x = pProps->get_xdir() == "normal"
		? xmin + p.x() / xPixelsPerUnit
		: xmax - p.x() / xPixelsPerUnit;
	
	double y =  pProps->get_ydir() == "normal"
		? ymax - p.y() / yPixelsPerUnit
		: ymin + p.y() / yPixelsPerUnit;
	
	return QPointF( x, y );
}


// ============================================================================
/// Axes bounding rectangle. Adds margins to plot box
QRectF AxesItem::boundingRect() const
{
	double  m = 30.0 ; // TODO some random margin, com our with reasonable value.
	return  QRectF( -m, -m, _size.width() + 2*m, _size.height() + 2*m );
}

// ============================================================================
/// Called when properties has changed. Updates axes state to properties.
void AxesItem::propertiesChanged()
{
	updatePosition(); // update position before childs are updates, so then can see new position
	UIItem::propertiesChanged();
	
	update();
}

// ============================================================================
/// Updates item postion and size basing on 'position' and 'units' properties.
void AxesItem::updatePosition()
{
	gh_manager::lock_guard guard;
	axes::properties* pProps = properties();
	Matrix pos = pProps->get_position().matrix_value();
	
	// octave position, in variant units
	double posLeft		= pos.elem( 0 );
	double posBottom	= pos.elem( 1 );
	double posWidth		= pos.elem( 2 );
	double posHeight	= pos.elem( 3 );
	
	QRect figure = figureRect();
	
	// pixel positions
	double left, bottom, width, height;
	
	if ( pProps->get_units() == "normalized" )
	{
		left	= figure.left() + figure.width() * posLeft;
		bottom	= figure.bottom() - figure.height() * posBottom;
		width	= figure.width() * posWidth;
		height	= figure.height() * posHeight;
		
	}
	else if ( pProps->get_units() == "pixels" )
	{
		qWarning("As for now, octave does not supprot pixel units");
		return; // TODO ublock when fixed
		left	= posLeft;
		bottom	= posBottom;
		width	= posWidth;
		height	= posHeight;
		
	}
	else
	{
		qWarning("Units other than normalized and pixel not supported currently");
		return;
	}
	
	setPos( left, bottom - height );
	_size = QSizeF( width, height );
	
	prepareGeometryChange();
	updateChildPositions();

	update();
}

// ============================================================================
/// Updates axes geometry, when figure size changes.
void AxesItem::updateGeometry()
{
	updatePosition();
	
	// Update child elements here (probably not)
	
	update();
}

// ============================================================================
/// Caluclates tick legth from properties. Returns length in pixels.
double AxesItem::tickLength()
{
	// TODO
	return 5.0;
}

// ============================================================================
/// Creates item with provided property set. Item type is deduced from "type" property.
UIItem* AxesItem::createItem( double h, base_properties* pProps )
{
	Q_ASSERT( pProps );
	
	
	std::string type = pProps->get_type();
	
	// Text
	if ( type == "text" )
	{
		TextItem* pText = new TextItem( h, this );
		return pText;
	}
	// Line
	if ( type == "line" )
	{
		LineItem* pLine = new LineItem( h, this );
		return pLine;
	}
	
	// Image
	if ( type == "image" )
	{
		ImageItem* pImage = new ImageItem( h, this );
		return pImage;
	}
	return NULL;
}

// ============================================================================
/// Updates child psoition to axes posotion.
void AxesItem::updateChildPositions()
{
	// TODO this shouldn't be needed
	foreach( UIItem* pItem, children() )
	{
		dynamic_cast<PlotItem*>( pItem )->updatePositionToAxes();
	}
}

} // namespace
