// figuremanager.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#include "figuremanager.h"
#include "plotevent.h"
#include "eventtypes.h"
#include "figurewindow.h"

namespace QOGraphics
{

// ============================================================================
// Constructor
FigureManager::FigureManager ( QObject *parent )
		: QObject ( parent )
{
	// nothing
}

// ============================================================================
// Destructor
FigureManager::~FigureManager()
{
	// nothing
}

// ============================================================================
/// Handles incoming events. Returns \b true if event was recognized and processed.
bool FigureManager::event ( QEvent* pEvent )
{
	if ( pEvent && pEvent->type() == EventTypePlot )
	{
		PlotEvent* pPlotEvent = dynamic_cast<PlotEvent*>( pEvent );
		if ( pPlotEvent )
		{
			switch( pPlotEvent->action )
			{
				case PlotEvent::PropertyChanged:
					propertyChanged( pPlotEvent->handle, pPlotEvent->name );
					break;
					
				case PlotEvent::Created:
					objectCreated( pPlotEvent->handle );
					break;
					
				case PlotEvent::Destroyed:
					objectDestroyed( pPlotEvent->handle );
					break;
					
				default:
					qWarning("FigureManager::event: unknown action requested");
			}
		}
	}
	// TODO
	return false;
}

// ============================================================================
/// Handles message from main thread: property has changed.
void FigureManager::propertyChanged( double h, const QString& name )
{
	gh_manager::lock_guard guard;
	
	// check object validity (object could be deleted by now)
	if ( ! gh_manager::get_object( h ) )
	{
		return;
	}
	
	if ( _items.contains( h ) )
	{
		_items[h]->propertyChanged( name );
	}
	else if ( _figures.contains( h ) )
	{
		_figures[h]->propertyChanged( name );
	}
	else
	{
		qWarning("property changed: unknown object %g", h );
	}
}

// ============================================================================
/// Handles message from main thread: object was created.
void FigureManager::objectCreated( double h )
{
	gh_manager::lock_guard guard;
	
	graphics_object go = gh_manager::get_object( h );
	base_properties& props = go.get_properties();
	
	std::string type = props.get_type();
	
	if ( type == "figure" )
	{
		// create new figure
		FigureWindow* pFig = new FigureWindow( h );
		_figures[h] = pFig;
		pFig->show();
	}
	else
	{
		double parent = props.get_parent().value();
		if ( _items.contains( parent ) )
		{
			_items[h] = _items[parent]->addChild( h );
		}
		else if ( _figures.contains( parent ) )
		{
			_items[ h ] = _figures[parent]->addChild( h );
		}
		else
		{
			qWarning("Object %g (%s) created with unknonw parent %g",
				h, type.c_str(), parent );
		}
	}
}

// ============================================================================
/// Handles message from main thread: object was destroyed.
void FigureManager::objectDestroyed( double h )
{
	gh_manager::lock_guard guard;
	
	if ( _items.contains( h ) )
	{
		delete _items[h];
		_items.remove( h );
	}
	else if ( _figures.contains( h ) )
	{
		delete _figures[h];
		_figures.remove( h );
	}
	else
	{
		qWarning("object destroyed: unknown object %g", h );
	}
}

} // nmspc

// EOF

