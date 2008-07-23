// uiitem.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSUIITEM_H
#define QOGRAPHICSUIITEM_H

#include <QGraphicsItem>

#include "graphicsobject.h"

namespace QOGraphics
{
class FigureWindow;


/**
Common QGraphicsItem for all UI items.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class UIItem : public QGraphicsItem, public GraphicsObject
{
public:
	UIItem( double h, FigureWindow* figure, QGraphicsItem* parent = NULL );
	virtual ~UIItem();
	
	/// Returns pointer to figure
	FigureWindow* figure() const { return _pFigure; }
	
	/// Sets figure rectangle.
	void setFigureRect( const QRect& r ) { _figureRect = r; }
	QRect figureRect() const { return _figureRect; }
	
	/// Message from outer world - property changed
	virtual void propertyChanged( const QString& name );
	
	virtual void updateGeometry() {};	///< Message from parent: parent's geometry has changed
	
protected:
	
	virtual void propertiesChanged() {};
	
private:
	
	QRect _figureRect;						///< Parent figure rectangle to paint on (in pixels)
	FigureWindow*		_pFigure;			///< Parent figure
	double				_handle;			///< Item's handle
};

}

#endif // QOGRAPHICSUIITEM_H

// EOF


