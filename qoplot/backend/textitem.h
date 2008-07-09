// textitem.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSTEXTITEM_H
#define QOGRAPHICSTEXTITEM_H

#include "plotitem.h"

namespace QOGraphics 
{

/**
Graphics item associated with Text object.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class TextItem : public PlotItem
{
public:
	TextItem( double h, AxesItem* parent );
	virtual ~TextItem();

	/// Returns current properties.
	virtual text::properties* properties() const { return dynamic_cast<text::properties*>( PlotItem::properties()); }
	
	/// Paints item
	virtual void paint
		( QPainter *painter
		, const QStyleOptionGraphicsItem* option
		, QWidget * widget = NULL );
		
	/// Returns item bounding rectangle
	virtual QRectF boundingRect() const;
	
protected:

	virtual void propertiesChanged();		///< Updates item after properties change
	
private:

	QRectF textExtent() const;			///< Calculates text extent rectange
	QPointF alignTranlsation() const;	///< Fids translation caused by alignment
	
};

}

#endif // QOGRAPHICSTEXTITEM_H

// EOF


