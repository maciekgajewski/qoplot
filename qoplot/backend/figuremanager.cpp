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
#include "exceptions.h"

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
	try
	{
		gh_manager::autolock guard;
		
		
		// check object validity (object could be deleted by now)
		graphics_object go = gh_manager::get_object( h );
		if ( ! go )
		{
			qDebug("FigureManager::propertyChanged: object already deleted");
			return;
		}
		
		if ( _objects.contains( h ) )
		{
			_objects[h]->propertyChanged( name );
		}
		else
		{
			qWarning("property changed: unknown object %g", h );
		}
	}
	catch( const Exception& e )
	{
		qWarning("FigureManager::propertyChanged: h=%g, exception: %s", h, qPrintable( e.msg() ) );
	}
}

// ============================================================================
/// Handles message from main thread: object was created.
void FigureManager::objectCreated( double h )
{
	//qDebug("GUI object created: %g", h );
	try
	{
		gh_manager::autolock guard;
		
		graphics_object go = gh_manager::get_object( h );
		if ( ! go )
		{
			qDebug("FigureManager::objectCreated: object %g already deleted", h );
			return;
		}
		base_properties& props = go.get_properties();
		
		std::string type = props.get_type();
		
		if ( type == "figure" )
		{
			// create new figure
			FigureWindow* pFig = new FigureWindow( h );
			_objects[h] = pFig;
			pFig->show();
		}
		else
		{
			double parent = props.get_parent().value();
			if ( _objects.contains( parent ) && !isnan(parent) )
			{
				_objects[h] = _objects[parent]->childAdded( h );
			}
			else
			{
				qWarning("Object %g (%s) created with unknonw parent %g",
					h, type.c_str(), parent );
			}
		}
	}
	catch ( const Exception& e )
	{
		qWarning("Excepton in FigureManager::objectCreated:  h=%g, %s", h, qPrintable( e.msg() ) );
	}
}

// ============================================================================
/// Handles message from main thread: object was destroyed.
void FigureManager::objectDestroyed( double h )
{
	//qDebug("GUI object destroyed: %g", h );
	gh_manager::autolock guard;
	
	try
	{
		if ( _objects.contains( h ) && !isnan(h) )
		{
			// notify parent
			double ph = _objects[h]->properties()->get_parent().value();
			
			if( _objects.contains( ph ) && !isnan(h) )
			{
				_objects[ph]->childRemoved( h );
			}
		
			delete _objects[h];
			_objects.remove( h );
		}
		else
		{
			qDebug("GUI object destroyed:  unknown object %g", h );
			// this is the case when object was destroyed before create event reached UI thread.
		}
	}
	catch ( const Exception& e )
	{
		qWarning("Excepton in FigureManager::objectDestroyed:  h=%g, %s", h, qPrintable( e.msg() ) );
	}
}

} // nmspc

// EOF

