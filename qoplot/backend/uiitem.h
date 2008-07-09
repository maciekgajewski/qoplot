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
#include <QPen>
#include <QFont>

#include <octave/oct.h>
#include <octave/graphics.h>

namespace QOGraphics
{
class FigureWindow;


/**
Common QGraphicsItem for all UI items.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/

class UIItem : public QGraphicsItem
{
public:
	UIItem( double handle, FigureWindow* figure, QGraphicsItem* parent = NULL );
	virtual ~UIItem();
	
	/// Returns pointer to figure
	FigureWindow* figure() const { return _pFigure; }
	
	/// Returns current properties.
	virtual base_properties* properties() const;
	
	/// Message from outer world - child added
	virtual UIItem* addChild( double h );
	
	/// Message from outer world - property changed
	virtual void propertyChanged( const QString& name );
	
	/// Returns handle
	double handle() const { return _handle; }
	
	void setFigureRect( const QRect& r ) { _figureRect = r; }
	QRect figureRect() const { return _figureRect; }
	
	virtual void updateGeometry() {};	///< Message from parent: parent's geometry has changed
	
protected:

	/// Pen created from properties
	QPen	pen( const QColor& color, const QPaintDevice* pDevice   ) const;
	QFont	font() const;						///< Font created from properties
	
	/// Converts points to pixels
	double ptToPixel( double pt, const QPaintDevice* device ) const;
	
	virtual void propertiesChanged();		///< Updates item after properties change
	
	/// Creates item with provided property set.
	virtual UIItem* createItem( double h, base_properties* pProps );
	
	QList<UIItem*> children() const { return _children.values(); }
	
private:
	
	QRect _figureRect;						///< Parent figure rectangle to paint on (in pixels)
	QMap< double, UIItem* > _children;		///< Child elements
	FigureWindow*		_pFigure;			///< Pointer to figure
	double				_handle;			///< Item's handle
};

}

#endif // QOGRAPHICSUIITEM_H

// EOF

