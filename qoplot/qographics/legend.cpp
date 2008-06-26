// legend.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#include "legend.h"
#include "axes.h"
#include "root.h"

namespace QOGraphics {

// ============================================================================
// Constructor
Legend::Legend( Root* root, Handle handle, QObject* parent )
	: PlotObject( root, handle, parent )
{
	_pItem = new LegendItem();
	addToParent();
	initProperties();
}

// ============================================================================
// Destructor
Legend::~Legend()
{
	// nope
}

// ============================================================================
// Initializes item properties
void Legend::initProperties()
{
	PlotObject::initProperties();
	
	_pItem->box.addValue( LegendItem::On, "on", true );
	_pItem->box.addValue( LegendItem::Off, "off" );
	
	_pItem->position.addValue( LegendItem::North, "North" );
	_pItem->position.addValue( LegendItem::South, "South" );
	_pItem->position.addValue( LegendItem::West, "West" );
	_pItem->position.addValue( LegendItem::East, "East" );
	_pItem->position.addValue( LegendItem::NorthWest, "NorthWest" );
	_pItem->position.addValue( LegendItem::NorthEast, "NorthEast", true );
	_pItem->position.addValue( LegendItem::SouthWest, "SouthWest" );
	_pItem->position.addValue( LegendItem::SouthEast, "SouthEast" );
	
	_pItem->color = QApplication::palette().color( QPalette::ButtonText );
}

// ============================================================================
/// Updates list of plot objects displayed in legend, extracting them from axes children list.
void Legend::updateLegend()
{
	Axes* pAxes = axes();
	Q_ASSERT( pAxes );
	
	// TODO maybe axes shoudl just return list of plot objects (like QList<PlotObject*>) instead?
	Matrix ch = pAxes->getChildren();
	
	_pItem->items.clear();
	
	for( int i = 0; i < ch.vectorSize(); i++ )
	{
		Handle h = Handle( ch.vectorValue( i ) );
		
		PlotObject* pPlotObject = qobject_cast<PlotObject*>( root()->objectByHandle( h ) );
		if ( pPlotObject )
		{
			if ( pPlotObject->getAnnotation() == "on" )
			{
				_pItem->items.append( (PlotItem*)pPlotObject->item() );
			}
		}
	}
	
	_pItem->update();
}


}
