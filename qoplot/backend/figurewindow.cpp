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
#include <QDesktopWidget>

#include "figurewindow.h"
#include "converters.h"
#include "axesitem.h"

namespace QOGraphics
{

// ============================================================================
/// Constructor
FigureWindow::FigureWindow( QWidget* parent, Qt::WindowFlags flags )
	: QMainWindow( parent, flags )
{
	_pProperties = NULL;
	setupUi( this );
	
	view->setScene( & _scene );
	
}

// ============================================================================
/// Destructor
FigureWindow::~FigureWindow()
{
	if ( _pProperties )
	{
		delete _pProperties;
		_pProperties = NULL;
	}
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
/// Makes copy of provided property set.
void FigureWindow::copyProperties( const figure::properties* pProperties )
{
	if ( _pProperties )
	{
		delete _pProperties;
	}
	
	_pProperties = new figure::properties( *pProperties );
	propertiesChanged();
}

// ============================================================================
/// Called when properties are changed. Updates figure state to it's properties.
void FigureWindow::propertiesChanged()
{
	Q_ASSERT( _pProperties );
	
	// color 
	_scene.setBackgroundBrush( colorFromOctave( _pProperties->get_color() ) );
	
	// position
	updatePosition();
	
	// resize
	statusBar()->setSizeGripEnabled( _pProperties->get_resize() == "on" );
	// TODO really block resising here
	
	// update children
	updateChildren();
}

// ============================================================================
/// Updates window position to position property.
void FigureWindow::updatePosition()
{
	std::string units = _pProperties->get_units();
	Matrix pos = _pProperties->get_position().matrix_value();
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
}

// ============================================================================
/// Updates childre. Adds and removes children as they are appearing on/disappearing from
/// children list, and propagates properties to them
void FigureWindow::updateChildren()
{
	Matrix cm = _pProperties->get_children();
	
	int count = cm.nelem();
	QMap<double, UIItem*> newMap;
	
	for( int i = 0; i < count; i++ )
	{
		double h = cm.elem(i);
		base_properties* pProps = NULL;
		
		graphics_object obj = gh_manager::get_object (h);
		if ( obj )
		{
			// get properties
			pProps = &obj.get_properties();
		}
		
		// 1 - do we have this child already?
		if ( ! _children.contains( h ) )
		{
			// no, we don't
			// create object
			newMap.insert( h, createItem( pProps ) );
		}
		else
		{
			// yes, we have it
			// 2. is it the same type?
			if ( _children[h]->properties()->get_type() == pProps->get_type() )
			{
				// just update
				_children[h]->copyProperties( pProps );
				newMap.insert( h, _children[h] );
				_children.remove( h ); // remove from old map
			}
			else
			{
				// type changed - re-create
				// TODO
				qDebug("re-creation not implemented");
			}
		}
	}
	
	// now items that left on old map should be removed
	foreach( double h, _children.keys() )
	{
		delete  _children[h];
	}
	
	// flip tables
	_children = newMap;
}

// ============================================================================
/// Creates item, basing on value returned by proeprties get_type(). Initialies item with new properties.
UIItem* FigureWindow::createItem( base_properties* pProps )
{
	Q_ASSERT( pProps );
	
	// axes
	if ( pProps->get_type() == "axes" )
	{
		AxesItem* pAxes = new AxesItem( this );
		pAxes->setFigureRect( view->rect() );
		pAxes->copyProperties( pProps );
		_scene.addItem( pAxes );
		return pAxes;
	}
	else
	{
		qDebug("FigureWindow::createItem: unsupported item type: %s", pProps->get_type().c_str() );
	}
		
	return NULL;
}

}; // namespace
// EOF


