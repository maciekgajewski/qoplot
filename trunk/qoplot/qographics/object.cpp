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

namespace QOGraphics
{

// ============================================================================
// Constructor
Object::Object( Root* pRoot, Handle handle, QObject* parent ): QObject( parent )
{
	_handle = handle;
	// TODO I'm not sure about this... mybe this should be called explicitily in Root
/*	if ( pRoot )
	{
		// introduce to root
		_handle = pRoot->objectCreated( this );
	}*/
	
	_pRoot = pRoot;
	
	// init params
	_visible.addValue( 0, "no" );
	_visible.addValue( 1, "yes", true );
	
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
	prepareCaseMap();
	QString propName = _caseMap[ name.toLower() ];
	
	qDebug("setting property %s, type: %d", qPrintable( propName ), value.userType() );
	QObject::setProperty( propName.toUtf8().data(), value );
}

// ============================================================================
/// Gets property value
QVariant Object::getProperty( const QString& name )
{
	prepareCaseMap();
	QString propName = _caseMap[ name.toLower() ];
	
	return property( propName.toUtf8().data() );
}

// ============================================================================
// Returns matrix with parent handle, or empty matrix.
QVariant Object::getParent() const
{
	// TODO
	return QVariant();
}

// ============================================================================
// Returns vector of child object handles
Matrix Object::getChildren() const
{
	QList<Object*> children = findChildren<Object*>();
	
	Matrix matrix( 1, children.size() ); // row vector
	
	for( int i = 0; i < children.size(); i++ )
	{
		matrix.setValue( 1, i+1, children[ i ]->handle() );
	}
	
	return matrix;
}

// ============================================================================
/// This method prepares _CaseMap - a mapping between lower case property nmes and actual names.
/// This is required, becouse octave assumes propery names are not case sensitive, and Qt id case sensitive.
/// The map is prepared only once. Subsequent calls does nothing.
void Object::prepareCaseMap()
{
	if ( _caseMap.isEmpty() )
	{
		QStringList names = properties();
		
		foreach( QString name, names )
		{
			_caseMap[ name.toLower() ] = name;
		}
	}
}

}; // namespace

// EOF

