// legenditem.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSLEGENDITEM_H
#define QOGRAPHICSLEGENDITEM_H

#include "plotitem.h"
#include "enum.h"

namespace QOGraphics
{

/**
LegendItem, used to draw legend
@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/

class LegendItem : public PlotItem
{

public:
	LegendItem ( QGraphicsItem* parent = NULL );
	virtual ~LegendItem();
	
	/// Paints item
	virtual void paint
		( QPainter *painter
		, const QStyleOptionGraphicsItem* option
		, QWidget * widget = NULL );
		
	/// Returns item bounding rectangle
	virtual QRectF boundingRect() const;
	
	void updateLegend(); ///< Updates list of plot objects.
	
	void locationChanged();	///< Handle positoon property change / axes size change
	
	virtual void setPlotBox( const QRectF& r );
	
	// enums used in properties
	enum LegendLocation { North, West, East, South, NorthEast, NorthWest, SouthEast, SouthWest };
	
	// properties
	
	Enum location;		///< Legend position within the plot box
	Enum box;			///< If box should be painted
	Color edgeColor;	///< Frame edge color
	Color faceColor;	///< Face color
	double faceAlpha;	///< Face alpha (opacity)

	QList<PlotItem*> items;		///< Plot items displayed in legend

private:

	QSizeF findSize();				///< Finds size of legend
};

}

#endif // QOGRAPHICSLEGENDITEM_H

// EOF


