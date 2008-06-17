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

#include "matrixcodec.h"

#include "root.h"



// ============================================================================
// Constructor
Root::Root( QObject* parent ): Object( NULL, parent )
{
	_currentFigure = InvalidHandle;
	// add self to database
	_objects[ RootHandle ] = this;
}

// ============================================================================
// Destructor
Root::~Root()
{
	// nope
}

// ============================================================================
// Object destroyed
void Root::objectDestroyed( Handle handle )
{
	Q_ASSERT( _objects.contains( handle ) );

	_objects.remove( handle );
}

// ============================================================================
// Object created
/// Adds newly created object to database, allocating handle for it. Returns allocated handle.
Object::Handle Root::objectCreated( Object* pObject )
{
	Q_ASSERT( pObject );
	
	// allocate handle, store object
	Handle h = _objects.size();
	_objects.insert( h, pObject );
	
	return h;
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
QVariantList Root::getCurrentFigure() const
{
	// TODO
	return QVariantList();
}

// ============================================================================
/// Returns mouse pointer location, in screen coordinates
QVariantList Root::getPointerLocation() const
{
	// TODO test
	qDebug("Root::getPointerLocation()");
	MatrixCodec c( 2, 2 );
	c.setValue( 1, 1, 11 );
	c.setValue( 1, 2, 12 );
	c.setValue( 2, 1, 21 );
	c.setValue( 2, 2, 22 );
	
	return c.matrix();
}

// ============================================================================
// Returns handle to window over whichj mouse poitner is now
Object::Handle Root::getPointerWindow() const
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
QVariantList Root::getScreenSize() const
{
	// TODO 
	return QVariantList();
}

// ============================================================================
// Returns screen DPI
double Root::getScreenPixelsPerInch() const
{
	// TODO
	return 90;
}


// EOF


