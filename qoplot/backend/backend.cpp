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

// ============================================================================
/// Info from Octave - some property of figure or one of it's
/// children were changedm and figure and it's children needs to be redrawn.
void Backend::redraw_figure (const graphics_handle& fh) const
{
	// send message
	PlotEvent* pEvent = new PlotEvent;
	
	pEvent->action = PlotEvent::Redraw;
	pEvent->figure = fh.value();
	
	QApplication::postEvent( _pManager, pEvent );
	
	
	// TODO copy data somehow, synchronize
}

// ============================================================================
/// Info form octave: figre should be closed.
void Backend::close_figure (const octave_value& ov) const
{
	qDebug("close figure");
	// TODO
	if (ov.is_string ())
	{
		std::string v = ov.string_value();
		qDebug("Backend::close_figure, ov=%s", v.c_str() );
	}
	else if ( ov.is_scalar_type() )
	{
		qDebug("is scalar");
	}
	if ( ov.is_real_type() )
	{
		qDebug("is real");
	}
	if ( ov.is_matrix_type() )
	{
		qDebug("is matrix");
	}
//      figure_manager::Instance ().delete_window (ov.string_value ());
}

}