// legenditem.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#include <QApplication>
#include <QDesktopWidget>

#include "legenditem.h"
#include "axesitem.h"

namespace QOGraphics
{

// constants
static const double MARGIN	= 4;		// Margin between entries and box [pt]
static const double ICON_WIDTH = 20;	// Icon width [pt]
static const double AXES_MARGIN = 10;	// MArgin between legend and axes [pt]



// ============================================================================
// Constructor
LegendItem::LegendItem ( QGraphicsItem* parent ) : PlotItem ( parent )
{
	// nothing
}

// ============================================================================
// Destructor
LegendItem::~LegendItem()
{
	// nothing
}

// ============================================================================
/// Paints item
void LegendItem::paint
	( QPainter *pPainter
	, const QStyleOptionGraphicsItem* /*option*/
	, QWidget * /*widget*/ /*= NULL*/ )
{
	QFont f = font();
	QFontMetricsF metrics( f, pPainter->device() );
	
	double margin		= ptToPixel( MARGIN, QApplication::desktop() ); // uses desktop as paint device by default
	double iconWidth	= ptToPixel( ICON_WIDTH, QApplication::desktop()  );
	QSizeF size			= findSize();
	double textWidth	= size.width() - 2*margin - iconWidth;
	
	// draw box
	pPainter->setFont( f );
	pPainter->setPen( pen( QColor( edgeColor ), pPainter->device() ) );
	pPainter->setBrush( QColor( color ) );
	pPainter->drawRect( QRectF( QPointF( 0, 0 ), size ) );
	
	// draw items
	double y = margin;
	foreach( PlotItem* pItem, items )
	{
		// draw icon (let item do it itself)
		QRectF iconRect( margin, y, iconWidth, metrics.lineSpacing() );
		pItem->drawIcon( pPainter, iconRect );
		
		// draw text
		QRectF textRect( margin+iconWidth, y, textWidth, metrics.lineSpacing() );
		pPainter->drawText( textRect, Qt::AlignVCenter | Qt::AlignLeft, pItem->displayName );
	}
}
	
// ============================================================================
/// Returns item bounding rectangle
QRectF LegendItem::boundingRect() const
{
	// be easy, return entire parent axes rectangle
	/// TODO cut if optimization needed
	
	QRectF axesRect = axesItem()->boundingRect();
	
	return mapFromParent( axesRect ).boundingRect();
}

// ============================================================================
/// Finds size of the item. The size depends on current font setting, item number
/// and item textlenghts.
QSizeF LegendItem::findSize()
{
	QFontMetricsF metrics( font() );
	
	// find text width
	
	double textWidth = 0.0;
	foreach ( PlotItem* pItem, items )
	{
		Q_ASSERT( pItem );
		
		double w = metrics.boundingRect( pItem->displayName ).width();
		if ( w > textWidth )
		{
			textWidth = w;
		}
	}
	
	// now get margin and icon width in pixels
	double margin		= ptToPixel( MARGIN, QApplication::desktop() ); // uses desktop as paint device by default
	double iconWidth	= ptToPixel( ICON_WIDTH, QApplication::desktop()  );
	
	// ok, assembly size
	return QSizeF( margin*2 + iconWidth + textWidth, margin*2 + metrics.lineSpacing()*items.size() );
}

// ============================================================================
/// Extends base class method by updating position.
void LegendItem::setPlotBox( const QRectF& r )
{
	PlotItem::setPlotBox( r );
	positionChanged();
}

// ============================================================================
/// Handles positon property change / axes sizechange
void LegendItem::positionChanged()
{
	QSizeF size = findSize();
	QRectF box = axesItem()->plotBox(); // plot box in paren coorindates, as we are goint to set pos in parent space
	double axesMargin = ptToPixel( AXES_MARGIN, QApplication::desktop() ); 
	
	switch ( int(position) )
	{
		case North:
			setPos( box.left() + ( box.width() - size.width() )/2, box.top() + axesMargin );
			break;
			
		case West:
			setPos( box.left() + axesMargin, box.top() + ( box.height() - size.height() )/2 );
			break;
			
		case East:
			setPos( box.right() - axesMargin - size.width(), box.top() + ( box.height() - size.height() )/2 );
			break;
			
		case South:
			setPos( box.left() + ( box.width() - size.width() )/2, box.bottom() - axesMargin - size.height() );
			break;
			
		case NorthEast:
			setPos( box.right() - axesMargin - size.width(), box.top() + axesMargin );
			break;
			
		case NorthWest:
			setPos( box.left() + axesMargin, box.top() + axesMargin );
			break;
			
		case SouthEast:
			setPos( box.right() - axesMargin - size.width(), box.bottom() - axesMargin - size.height() );
			break;
			
		case SouthWest:
			setPos( box.left() + axesMargin, box.bottom() - axesMargin - size.height() );
	}
	
}

}
