// root.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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

#include "root.h"
#include "exceptions.h"
#include "figure.h"
#include "axes.h"

namespace QOGraphics
{

bool Root::_graphicsInitialized = false;

// ============================================================================
// Constructor
Root::Root( QObject* parent ): Object( NULL, RootHandle, parent )
{
	_beingDeleted = false;
	// init library
	if ( ! _graphicsInitialized )
	{
		// Register matrix type
		int mid = qRegisterMetaType< Matrix >();
		qDebug("matrix type id: %d", mid );
		//qRegisterMetaType< Enum >( "Enum" ); TODO not needed?
		
		_graphicsInitialized = true;
	}
	
	// init instance
	
	_currentFigure = InvalidHandle;
	// add self to database
	_objects[ RootHandle ] = this;
	_firstFreeHandle = 1;
}

// ============================================================================
// Destructor
Root::~Root()
{
	_beingDeleted = true;
}

// ============================================================================
// Object destroyed
void Root::objectDestroyed( Handle handle )
{
	if ( _beingDeleted ) return;
	
	Q_ASSERT( _objects.contains( handle ) );


	_objects.remove( handle );
	
	if ( _currentFigure == handle )
	{
		_currentFigure = InvalidHandle;
	}
}

// ============================================================================
/// Returns object identified by handle, or NULL if no such object.
Object* Root::objectByHandle( Handle h )
{
	if ( _objects.contains( h ) )
	{
		return _objects[ h ];
	}
	
	return NULL;
}

// ============================================================================
// Returns current figure handle, or empty matrix if none.
QVariant Root::getCurrentFigure() const
{
	QVariant v;
	
	if ( _currentFigure != InvalidHandle )
	{
		v = _currentFigure;
	}
	// otherwise - stay null
	
	return v;
}

// ============================================================================
/// Returns mouse pointer location, in screen coordinates
Matrix Root::getPointerLocation() const
{
	// TODO test
	qDebug("Root::getPointerLocation()");
	Matrix c( 2, 2 );
	c.setValue( 1, 1, 11 );
	c.setValue( 1, 2, 12 );
	c.setValue( 2, 1, 21 );
	c.setValue( 2, 2, 22 );
	
	return c;
}

// ============================================================================
// Returns handle to window over whichj mouse poitner is now
Handle Root::getPointerWindow() const
{
	// TODO
	return RootHandle;
}

// ============================================================================
// Returns screne depth, in bpp
double Root::getScreenDepth() const
{
	// TODO
	return 32;
}

// ============================================================================
// Returns screen size
Matrix Root::getScreenSize() const
{
	// TODO 
	return Matrix();
}

// ============================================================================
// Returns screen DPI
double Root::getScreenPixelsPerInch() const
{
	// TODO
	return 90;
}

// ============================================================================
// Creates new figure, makes it the current one. IF desired handle is specifed, tries to 
// use it.
Handle Root::addFigure( Handle desiredHandle /*= InvalidHandle*/ )
{
	Handle h = InvalidHandle;
	if ( desiredHandle != InvalidHandle )
	{
		// check ih desired handle available
		if ( _objects.contains( desiredHandle ) )
		{
			throw Exception( "Handle used" );
		}
		
		h = desiredHandle;
		
	}
	else
	{
		h = _firstFreeHandle;
	}
		
	// increment handle pointer if needed
	if ( h >= _firstFreeHandle )
	{
		_firstFreeHandle = h + 1;
	}
	
	// create figure
	Figure* pFigure = new Figure( this, h, this );
	
	_objects.insert( h, pFigure );
	
	// make the new figure current
	_currentFigure = h;
	
	return h;
}

// ============================================================================
// Sets current figure.
void Root::setCurrentFigure( Handle h )
{
	Figure* pFigure = qobject_cast<Figure*>( objectByHandle( h ) );
	
	if ( ! pFigure )
	{
		throw Exception( "Not a figure" );
	}
	_currentFigure = h;
	pFigure->raise();
}

// ============================================================================
/// Creates UI object  to figure. If no parent handle spoecified - adds to current figure/axes (depending on type)
/// Returns handle to created object
Handle Root::createObject( const QString& type, Handle parent /*= InvalidHandle*/ )
{
	// allocate handle
	Handle h = _firstFreeHandle++;
	
	// TODO move factory to figure
	if ( type == "axes" )
	{
		// get figure handle
		Handle p = parent == InvalidHandle ? _currentFigure : parent;
		Figure* pFigure = qobject_cast<Figure*>( objectByHandle( p ) );
		
		if ( ! pFigure )
		{
			throw Exception("No such figure");
		}
		Axes* pAxes = pFigure->createAxes( h );
		_objects[ h ] = (Object*)pAxes;
	}
	else
	{
		// get current axes
		Handle a = parent == InvalidHandle ? currentAxes() : parent;
		Axes* pAxes = qobject_cast<Axes*>( objectByHandle( a ) );
		
		if ( ! pAxes )
		{
			throw Exception( "No axes" );
		}
		
		Object* pObject = pAxes->createPlotObject( type, h );
		_objects[ h ]  = pObject;
	}
	
	return h;
}

// ============================================================================
/// Adds alredy created object to system
Handle Root::addObject( Object* pObject )
{
	Q_ASSERT( pObject );
	
	// TODO check if object isn't alredy added to system.
	
	Handle h = _firstFreeHandle++;
	pObject->setHandle( h );
	
	_objects[ h ] = pObject;
	
	return h;
	
}

// ============================================================================
/// Returns handle to current axes. If no axes exists-  InvalidHandle is returned
Handle Root::currentAxes() const
{
	const Figure* pFigure = qobject_cast<const Figure*>( objectByHandle( _currentFigure ) );
	if ( pFigure )
	{
		return pFigure->currentAxes();
	}
	
	return InvalidHandle;
}

// ============================================================================
/// Makes sure axes are created. Does nothing if axes are created, but if they aren't, creates them.
void Root::makeSureAxesCreated()
{
	const Figure* pFigure = qobject_cast<const Figure*>( objectByHandle( _currentFigure ) );
	if ( pFigure )
	{
		if ( pFigure->currentAxes() == InvalidHandle )
		{
			createObject( "axes", _currentFigure );
		}
	}
	else
	{
		Handle fig = addFigure();
		createObject( "axes", fig );
	}
}

}; // namespace

// EOF


