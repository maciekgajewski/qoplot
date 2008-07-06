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

#include "uiitem.h"

namespace QOGraphics
{

/**
Gpahics item representingm and associated with Axes object.

 @author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/

class AxesItem : public UIItem
{

public:
	AxesItem( FigureWindow* figure, QGraphicsItem * parent = NULL );
	virtual ~AxesItem();
	
	// Item proeprties
	
	/// Paints item
	virtual void paint
		( QPainter *painter
		, const QStyleOptionGraphicsItem* option
		, QWidget * widget = NULL );
		
	/// Returns item bounding rectangle
	virtual QRectF boundingRect() const;
	
	/// Copies proeprties.
	virtual void copyProperties( const base_properties* pProps );
	
	/// Returns current properties.
	virtual axes::properties* properties() const { return _pProperties; }
	
	virtual void updateGeometry();					///< Message from parent: parent's geometry has changed
		
	QPointF plotToPixel( const QPointF& p ) const;	///< converts between plot and pixel space
	QPointF pixelToPlot( const QPointF& p ) const;	///< converts between plot and pixel space
	QRectF plotBox() const;							///< Returns coordinates of plot box
	
protected:

	virtual void propertiesChanged();				///< Updates item after properties change
	/// Creates item with provided property set.
	virtual UIItem* createItem( base_properties* pProps );
	
private:
	
	// drawing methods
	
	void drawBox( QPainter *painter );		///< Draws background box
	void drawXAxis( QPainter *painter );	///< Draws axis
	void drawYAxis( QPainter *painter );	///< Draws axis
	
	void updatePosition();					///< Updates position
 	void updateChildPositions();			///< Asks children to update position
	
	double tickLength();					///< Tick length, in pixels
	
	// data
	
	QSizeF _size;							///< Current pixel size
	axes::properties*	_pProperties;		///< Object properties.
};

}

#endif // QOGRAPHICSAXESITEM_H

// EOF


