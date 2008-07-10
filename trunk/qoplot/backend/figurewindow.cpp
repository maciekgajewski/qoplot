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
#include <QResizeEvent>
#include <QMoveEvent>
#include <QDesktopWidget>

#include "figurewindow.h"
#include "converters.h"
#include "axesitem.h"

namespace QOGraphics
{

static int POSITION_PROTECTION_PERIOD	= 2000;	// Protection perios for position set by octave. [ms]


// ============================================================================
/// Constructor
FigureWindow::FigureWindow( double handle )
	: QMainWindow( NULL )
{
	_handle = handle;
	setupUi( this );
	
	view->setScene( & _scene );
	
}

// ============================================================================
/// Destructor
FigureWindow::~FigureWindow()
{
	//
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
void FigureWindow::resizeEvent( QResizeEvent* pEvent )
{
	view->setSceneRect( view->rect() );

	// update position
	if ( pEvent->spontaneous() )
	{
		updatePositionToActual();
	}
	// udpate child's scene rect
	updateChildrenSizes();
}

// ============================================================================
/// Show event handler. Updates children sizes befor showing window.
void FigureWindow::showEvent( QShowEvent* /*event*/ )
{
	updateChildrenSizes();
}

// ============================================================================
/// Updates children elements sizes.
void FigureWindow::updateChildrenSizes()
{
	foreach( UIItem* pChild, _children.values() )
	{
		pChild->setFigureRect( view->rect() );
		pChild->updateGeometry();
	}
}

// ============================================================================
/// Called when properties are changed. Updates figure state to it's properties.
void FigureWindow::propertiesChanged()
{
	gh_manager::lock_guard guard;
	
	figure::properties* pProps = properties();
	Q_ASSERT( pProps );
	
	// color 
	_scene.setBackgroundBrush( colorFromOctave( pProps->get_color() ) );
	// resize
	statusBar()->setSizeGripEnabled( pProps->get_resize() == "on" );
	// TODO really block resising here
	
}

// ============================================================================
/// Updates window position to position property.
void FigureWindow::updateActualToPosition()
{
	gh_manager::lock_guard guard;
	
	figure::properties* pProps = properties();
	std::string units = pProps->get_units();
	Matrix pos = pProps->get_position().matrix_value();
	int screenHeight = QApplication::desktop()->height();
	
	if ( units == "pixels" )
	{
		QRect g;
		g.setY( int( screenHeight - pos.elem(1) - pos.elem(3) ) );
		g.setX( int( pos.elem(0) ) );
		
		g.setWidth( int( pos.elem(2) ) );
		g.setHeight( int( pos.elem(3) ) );
		
		setGeometry( g );
	}
	else
	{
		qDebug("Position units other than pixels not supported currently");
	}
	_lastPositionPropertyChange = QDateTime::currentDateTime(); // we did it now
}

// ============================================================================
/// Updates position property to actual window position.
void FigureWindow::updatePositionToActual()
{
	// cance laction if position was just changed as reaction to property change
	if ( _lastPositionPropertyChange.addMSecs( POSITION_PROTECTION_PERIOD )
		> QDateTime::currentDateTime() )
	{
		return;
	}
	
	gh_manager::lock_guard guard;
	
	figure::properties* pProps = properties();
	std::string units = pProps->get_units();
	
	Matrix pos( 1, 4 ); // left, bottom, width, height
	int screenHeight = QApplication::desktop()->height();
	
	if ( units == "pixels" )
	{
		QRect g = geometry();
		
		pos.elem( 0 ) = g.left();
		pos.elem( 1 ) = screenHeight - g.bottom();
		pos.elem( 2 ) = g.width();
		pos.elem( 3 ) = g.height();
		
		pProps->set_position( pos );
	}
	else
	{
		qDebug("Position units other than pixels not supported currently");
	}
	
}

// ============================================================================
/// Creates item, basing on value returned by proeprties get_type(). Initialies item with new properties.
UIItem* FigureWindow::createItem( double h, base_properties* pProps )
{
	Q_ASSERT( pProps );
	
	// axes
	if ( pProps->get_type() == "axes" )
	{
		AxesItem* pAxes = new AxesItem( h, this );
		pAxes->setFigureRect( view->rect() );
		_scene.addItem( pAxes );
		return pAxes;
	}
	else
	{
		qDebug("FigureWindow::createItem: unsupported item type: %s", pProps->get_type().c_str() );
	}
		
	return NULL;
}
// ============================================================================
/// Returns object properties, extracted from associated grpahics_object.
///\warning Always call this with gh_manager locked!
figure::properties* FigureWindow::properties() const
{
	graphics_object go = gh_manager::get_object( _handle );
	if ( go )
	{
		return (figure::properties*) &go.get_properties();
	}
	else
	{
		// TODO throwe exception here
		qWarning("Figure with handle %g is invalid!", _handle);
		return NULL;
	}
}

// ============================================================================
/// Message from octave: child object was created.
/// Visual object will be created using createItem().
UIItem* FigureWindow::addChild( double h )
{
	gh_manager::lock_guard guard;
	
	graphics_object go = gh_manager::get_object( h );
	base_properties& props = go.get_properties();
	
	UIItem* pChild = createItem( h, &props );
	_children.insert( h, pChild );
	pChild->updateGeometry();
	
	
	show(); // show if hidden
	return pChild;
}

// ============================================================================
/// Message from octave: property has changed.
void FigureWindow::propertyChanged( const QString& name )
{
	
	// position
	if ( name == "position" )
	{
		updateActualToPosition();
	}
	else
	{
		// all others
		propertiesChanged();
	}
}

// ============================================================================
/// Handles fingure move. Updates octave's 'position' property.
void FigureWindow::moveEvent( QMoveEvent * pEvent )
{
	// update position
	if ( pEvent->spontaneous() )
	{
		updatePositionToActual();
	}
}

}; // namespace
// EOF


