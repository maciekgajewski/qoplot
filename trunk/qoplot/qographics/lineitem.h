// lineitem.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSLINEITEM_H
#define QOGRAPHICSLINEITEM_H

#include "plotitem.h"
#include "enum.h"
#include "matrix.h"

namespace QOGraphics
{

/**
Graphics item used to paint line object. Associated with Line object.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/

class LineItem : public PlotItem
{

public:
	LineItem( QGraphicsItem* parent = NULL );
	virtual ~LineItem();
	
	/// Paints item
	virtual void paint
		( QPainter *painter
		, const QStyleOptionGraphicsItem* option
		, QWidget * widget = NULL );
		
	/// Returns item bounding rectangle
	virtual QRectF boundingRect() const;
	
	void dataChanged();
	QRectF dataBoundingRect() const;	///< Returns data boundary
	
	// enums
	enum MarkerType { None, Plus, Circle, Asterix, Point, Cross, Square, Diamond, TriangleUp,
		TriangleDown, TriangleLeft, TriangleRight, Pentagram, Hexagram };
	
	// properties
	
	Enum marker;
	Color markerEdgeColor;
	Color markerFaceColor;
	double markerSize;		///< Marker size, in points (1/72 inch)
	Matrix xdata, ydata;	///< Data
	
private:

	void drawMarker( QPainter* painter, const QPointF& pos ); ///< Draws marker
};

}

#endif // QOGRAPHICSLINEITEM_H

// EOF


