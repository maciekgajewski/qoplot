// plotobject.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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

#include "exceptions.h"
#include "axes.h"
#include "plotobject.h"

namespace QOGraphics
{

// ============================================================================
// Constructor
PlotObject::PlotObject( Root* root, Handle handle, QObject* parent ): UIObject( root, handle, parent )
{
	_pAxes = qobject_cast<Axes*>( parent );
	
	if ( ! _pAxes )
	{
		throw Exception("Plot object can be added only to axes");
	}
}

// ============================================================================
// Destructor
PlotObject::~PlotObject()
{
	// nothing
}

// ============================================================================
/// Intializes properties
void PlotObject::initProperties()
{
	UIObject::initProperties();
	
	PlotItem* pItem = (PlotItem*)item();
	
	pItem->usePlotCoordinates.addValue( PlotItem::On, "on", true );
	pItem->usePlotCoordinates.addValue( PlotItem::Off, "off");
	
	pItem->position	= Matrix( 3, 1 );
	
	pItem->clipping.addValue( PlotItem::On, "on" );
	pItem->clipping.addValue( PlotItem::Off, "off", true );
}

// ============================================================================
/// Sends message to axes taht child size haschanged.
void PlotObject::sizeChanged()
{
	_pAxes->childSizeChanged();
}

}
