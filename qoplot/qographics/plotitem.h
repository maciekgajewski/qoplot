// plotitem.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSPLOTITEM_H
#define QOGRAPHICSPLOTITEM_H

#include "uiitem.h"
#include "enum.h"
#include "figure.h"

namespace QOGraphics
{

class AxesItem;

/**
Item comon for all plot objects - objects placen on axes.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/

class PlotItem : public UIItem
{

public:
	PlotItem( QGraphicsItem* parent = NULL );
	virtual ~PlotItem();
	
	virtual void setPlotBox( const QRectF& r ) { _plotBox = r; }
	const QRectF& plotBox() const { return _plotBox; }
	AxesItem* axesItem() const; ///< Returns parent axes item
	Figure* figure() const;
	
	/// Draws icon used to represent object in legend
	virtual void drawIcon( QPainter* painter, const QRectF& rect );
	
	// enums

	// properties
	Matrix position;			///< Position in plot coordinates
	Enum usePlotCoordinates;	///< If use above position
	Enum clipping;				///< Clip to plot box on|{off}
	Enum annotation;			///< Annotation (object visible in legend) on|{off}
	QString	displayName;		///< Name used by legend
	
private:

	QRectF _plotBox;			///< Axes plot box, in this item coordinates

};

}

#endif // QOGRAPHICSPLOTITEM_H

// EOF


