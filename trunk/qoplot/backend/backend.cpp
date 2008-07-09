// backend.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#include <QApplication>

#include "backend.h"
#include "figuremanager.h"
#include "plotevent.h"
#include "systeminfo.h"



namespace QOGraphics
{

// ============================================================================
// Constructor
Backend::Backend( FigureManager* pManager ) : base_graphics_backend("qoplot")
{
	Q_ASSERT( pManager );
	_pManager = pManager;
	_motherThread = pthread_self();
}

// ============================================================================
// Destructor
Backend::~Backend()
{
	// nope
}

double getms()
{
	struct timeval tv;
	gettimeofday( &tv, NULL );
	
	return tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
	
}

// ============================================================================
/// Info from Octave - some property of figure or one of it's
/// children were changedm and figure and it's children needs to be redrawn.
void Backend::redraw_figure (const graphics_handle& ) const
{
	// ignore this hapilly
}

// ============================================================================
/// Info form octave: figre should be closed.
void Backend::close_figure (const octave_value& ov) const
{
	// nope :)
}

// ============================================================================
/// Returns two-element vector with screen size.
Matrix Backend::get_screen_size(void) const
{
	QSize size = SystemInfo::screenSize();
	Matrix sz (1, 2, 0.0);
	sz(0) = size.width();
	sz(1) = size.height();
	return sz;
}

// ============================================================================
/// Returns screen DPI.
double Backend::get_screen_resolution (void) const
{
	return SystemInfo::screenDpi();
}

// ============================================================================
// Property changed.
void Backend::property_changed (const graphics_handle& h, const std::string& name )
{
	//qDebug("Backend::property_changed: h=%g, prop=%s", h.value(), name.c_str() );
	
	// ignore "__modified__"
	if ( name == "__modified__" )
	{
		// do nothing
		return;
	}
	
	// ignore messages from other thread, as they may come from GUI thread.
	if ( ! pthread_equal( _motherThread, pthread_self() ) )
	{
		return;
	}
	
	// TODO check thread
	
	// send message
	PlotEvent* pEvent = new PlotEvent;
	
	pEvent->action = PlotEvent::PropertyChanged;
	pEvent->handle = h.value();
	pEvent->name = name.c_str();
	
	QApplication::postEvent( _pManager, pEvent );
}

// ============================================================================
// Object created.
void Backend::object_created (const graphics_handle& h)
{
	qDebug("Backend::object_created: h=%g", h.value() );
	
	// send message
	PlotEvent* pEvent = new PlotEvent;
	
	pEvent->action = PlotEvent::Created;
	pEvent->handle = h.value();
	
	QApplication::postEvent( _pManager, pEvent );
}

// ============================================================================
// Object destrioyed
void Backend::object_destroyed (const graphics_handle& h)
{
	qDebug("Backend::object_destroyed: h=%g", h.value() );
	
	// send message
	PlotEvent* pEvent = new PlotEvent;
	
	pEvent->action = PlotEvent::Destroyed;
	pEvent->handle = h.value();
	
	QApplication::postEvent( _pManager, pEvent );
}

}
