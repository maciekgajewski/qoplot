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

namespace QOGraphics
{

/**
Item comon for all plot objects - objects placen on axes.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/

class PlotItem : public UIItem
{

public:
	PlotItem( QGraphicsItem* parent = NULL );
	virtual ~PlotItem();
	
	void setClippingRect( const QRectF& r ) { _clippingRect = r; }
	const QRectF& clippingRect() const { return _clippingRect; }
	
	// enums

	// properties
	Matrix position;			///< Position in plot coordinates
	Enum usePlotCoordinates;	///< If use above position
	Enum clipping;				///< Clip to plot box on|{off}
	
private:

	QRectF _clippingRect;		///< Clipping rectangle, usec to clip to plot area

};

}

#endif // QOGRAPHICSPLOTITEM_H

// EOF


