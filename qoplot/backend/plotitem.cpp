// plotitem.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#include "plotitem.h"
#include "axesitem.h"

namespace QOGraphics
{

// ============================================================================
// Constructor
PlotItem::PlotItem( double h, AxesItem* parent ): UIItem( h, parent->figure(), parent )
{
	Q_ASSERT( parent );
	_pAxes = parent;
	// NOTE this scheme will collapse once group is implemented.
}

// ============================================================================
// Destructor
PlotItem::~PlotItem()
{
	// nope
}

// ============================================================================
/// Returns axes plot box, in this item's coordinates.
QRectF PlotItem::plotBox() const
{
	return mapFromParent( _pAxes->plotBox() ).boundingRect();
}

// ============================================================================
// Handles property change
void PlotItem::propertiesChanged()
{
	UIItem::propertiesChanged();
	
	updatePositionToAxes();
	update();
}

// ============================================================================
// Updtes position
void PlotItem::updatePositionToAxes()
{
	base_properties* pProps = properties();
	
	if ( pProps->has_property("Position") )
	{
		Matrix pos = pProps->get_property("Position").get().matrix_value();
		
		double plotX = pos.elem(0);
		double plotY = pos.elem(1);
		
		QPointF p = axesItem()->plotToPixel( QPointF( plotX, plotY ) );
		//qDebug("plot: %g,%g, pixel: %g,%g", plotX, plotY, p.x(), p.y() );
		prepareGeometryChange();
		setPos( p );
	}
}

}
