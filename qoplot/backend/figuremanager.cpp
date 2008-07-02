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
			if ( pPlotEvent->action == PlotEvent::Redraw )
			{
				redrawFigure( pPlotEvent->figure, pPlotEvent->pProperties );
			}
			else if ( pPlotEvent->action == PlotEvent::Close )
			{
				closeFigure( pPlotEvent->figure );
			}
			else qDebug("FigureManager::even: unknown action requested");
		}
	}
	// TODO
	return false;
}

// ============================================================================
/// Redraws figure, if exists, or creates new one with specified handle.
/// The figure is provided with new set of properies, and asked to copy and apply them.
/// Properties copying is synchronized with main octave thread.
void FigureManager::redrawFigure( double h, const figure::properties* pProps )
{
	FigureWindow* pFigure = NULL;
	if ( _figures.contains( h ) )
	{
		pFigure = _figures[ h ];
		// TODO redraw here
	}
	else
	{
		// create
		pFigure = new FigureWindow();
		_figures[ h ] = pFigure;
	}
	
	Q_ASSERT( pFigure );
	Q_ASSERT( pProps );
	
	// copy properties
	propertiesMutex.lock(); // this will wait until backend enters wait state
	
	pFigure->copyProperties( pProps );
	
	propertiesMutex.unlock(); // this allow backend to wake up, and/or to post another event.
	propertiesCopied.wakeAll();
		
	pFigure->show(); // show, if closed or hidden
}

// ============================================================================
/// Destroys figure with specified handle.
void FigureManager::closeFigure( double h )
{
	if ( _figures.contains( h ) )
	{
		FigureWindow* pFigure = _figures[ h ];
 		_figures.remove( h );
 		delete pFigure;
	}
}

} // nmspc

// EOF

