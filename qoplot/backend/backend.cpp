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
void Backend::redraw_figure (const graphics_handle& fh) const
{
	graphics_object fobj = gh_manager::get_object (fh);
	if (fobj &&  fobj.isa ("figure") )
	{
		// get properties
		figure::properties& fp = dynamic_cast<figure::properties&>( fobj.get_properties() );
			
		// send message
		PlotEvent* pEvent = new PlotEvent;
		
		pEvent->action = PlotEvent::Redraw;
		pEvent->figure = fh.value();
		pEvent->pProperties = &fp;
		
		_pManager->propertiesMutex.lock(); // this will wait until GUI thread finish previous copying
		QApplication::postEvent( _pManager, pEvent );
		
		// now wait for properties to be copied. Mutex is unlocked during waiting.
		_pManager->propertiesCopied.wait( & _pManager->propertiesMutex );
		
		// happy end, ready to handle next message
		_pManager->propertiesMutex.unlock();
	}
	else
	{
		qDebug("Backend::redraw_figure: not a figure handle.");
	}
}

// ============================================================================
/// Info form octave: figre should be closed.
void Backend::close_figure (const octave_value& ov) const
{
	qDebug("Close figure");
	if ( ov.is_matrix_type() )
	{
		Matrix figs = ov.matrix_value();
		
		for( int i = 0; i< figs.nelem(); i++ )
		{
			double fh = figs.elem( i );
			// send message
			PlotEvent* pEvent = new PlotEvent;
			
			pEvent->action = PlotEvent::Close;
			qDebug("close figure %f", fh );
			pEvent->figure = fh;
			pEvent->pProperties = NULL;
			
			QApplication::postEvent( _pManager, pEvent );
		}
	}
	else
	{
		qDebug("Backend::close_figure: unsupported param type");
	}
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


}
