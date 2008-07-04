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

namespace QOGraphics
{

/**
Graphics item associated with Line object.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/

class LineItem : public PlotItem
{

public:
	LineItem( AxesItem* parent );
	virtual ~LineItem();
	
	/// Copies properties
	virtual void copyProperties( const base_properties* pProps );
	
	/// Returns current properties.
	virtual line::properties* properties() const { return _pProperties; }
	
	/// Paints item
	virtual void paint
		( QPainter *painter
		, const QStyleOptionGraphicsItem* option
		, QWidget * widget = NULL );
		
	/// Returns item bounding rectangle
	virtual QRectF boundingRect() const;
	
private:

	void drawMarker( QPainter* painter, const QPointF& pos ); ///< Draws marker
	
	line::properties* _pProperties;
};

}

#endif // QOGRAPHICSLINEITEM_H

// EOF


