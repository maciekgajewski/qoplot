// figurewindow.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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

#include <QCloseEvent>

#include "figurewindow.h"

namespace QOGraphics
{

// ============================================================================
/// Constructor
FigureWindow::FigureWindow( QWidget* parent, Qt::WindowFlags flags )
	: QMainWindow( parent, flags )
{
	setupUi( this );
	
	view->setScene( & scene );
	
}

// ============================================================================
/// Destructor
FigureWindow::~FigureWindow()
{
	// nope
}

// ============================================================================
/// Widow close handle. Emits closed() signal.
void FigureWindow::closeEvent( QCloseEvent* pEvent )
{
	if ( pEvent->spontaneous() )
	{
		emit closed();
	}
}

// ============================================================================
/// Emits 'resized()' ingla when window is resized.
void FigureWindow::resizeEvent( QResizeEvent* /*event*/ )
{
	view->setSceneRect( view->rect() );
	QPointF sz = view->mapToScene( QPoint(0, 0 ));
	//qDebug("scene at 0,0: %f,%f", sz.x(), sz.y() );
	emit resized();
}

}; // namespace
// EOF


