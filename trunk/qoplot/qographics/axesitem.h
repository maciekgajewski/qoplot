// axesitem.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSAXESITEM_H
#define QOGRAPHICSAXESITEM_H

#include <QGraphicsItem>

#include "color.h"
#include "enum.h"
#include "matrix.h"

namespace QOGraphics
{

/**
 @author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/

class AxesItem : public QGraphicsItem
{

public:
	AxesItem( QGraphicsItem * parent = NULL );
	virtual ~AxesItem();
	
	/// Item proeprties
	QSizeF size() const { return _size; }
	void setSize( const QSizeF& size );
	
	/// Paints item
	virtual void paint
		( QPainter *painter
		, const QStyleOptionGraphicsItem* option
		, QWidget * widget = NULL );
		
	/// Returns item bounding rectangle
	virtual QRectF boundingRect() const{ return QRectF( QPointF(0, 0), _size ); }
	
	void recalculateTicks();				///< Recalculates ticks
	
	// enums used in proeprties
	enum AutoManual { Auto, Manual };
	
	// properties (stored here, set in Axes )
	
	Color color;
	Enum box;
	Matrix xlim, ylim;
	Matrix xtick, ytick;
	Enum xtickMode, ytickMode;
	Color xcolor, ycolor;
	Enum xlimMode, ylimMode;
	
		
private:
	
	// utilities
	
	QRectF innerBox() const;						///< Finds coordinates of inner box
	double findSpacing( double len, double pixels, double minPixels );
	Matrix generateTicks( double min, double max, double spacing );
	
	QPointF plotToPixel( const QPointF& p ) const;	///< converts between plot and pixel space
	QPointF pixelToPlot( const QPointF& p ) const;	///< converts between plot and pixel space
	
	// drawing methods
	
	void drawBox( QPainter *painter );		///< Draws background box
	void drawXAxis( QPainter *painter );	///< Draws axis
	void drawYAxis( QPainter *painter );	///< Draws axis
	
	
	// data
	
	QSizeF _size;

};

}

#endif // QOGRAPHICSAXESITEM_H

// EOF


