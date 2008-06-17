// object.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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

#include <QStringList>
#include <QMetaProperty>

#include "object.h"
#include "root.h"
#include "matrixcodec.h"

// ============================================================================
// Constructor
Object::Object( Root* pRoot, QObject* parent ): QObject( parent )
{
	_handle = InvalidHandle;
	if ( pRoot )
	{
		// introduce to root
		_handle = pRoot->objectCreated( this );
	}
	
	_pRoot = pRoot;
}

// ============================================================================
// Destructor
Object::~Object()
{
	if ( _pRoot )
	{
		// NOTE weird issues may surface when calluing somethinf from destructor.
		// Emitting signal could be better option.
		_pRoot->objectDestroyed( _handle );
	}
}

// ============================================================================
/// Returns list of all object's property names
QStringList Object::properties() const
{
	QStringList properties;
	int count = metaObject()->propertyCount();
	
	for ( int i = 0; i < count; i++ )
	{
		properties.append( metaObject()->property( i ).name() );
	}
	
	return properties;
}

// ============================================================================
/// Sets property value
void Object::setProperty( const QString& name, const QVariant& value )
{
	QObject::setProperty( name.toUtf8().data(), value );
}

// ============================================================================
/// Gets property value
QVariant Object::getProperty( const QString& name )
{
	return property( name.toUtf8().data() );
}

// ============================================================================
// Returns matrix with parent handle, or empty matrix.
QVariantList Object::getParent() const
{
	// TODO
	return QVariantList();
}

// ============================================================================
// Returns vector of child object handles
QVariantList Object::getChildren() const
{
	QList<Object*> children = findChildren<Object*>();
	
	MatrixCodec codec( children.size(), 1 );
	
	for( int i = 0; i < children.size(); i++ )
	{
		codec.setValue( 1, i, children[ i ]->handle() );
	}
	
	return codec.matrix();
}

// EOF

