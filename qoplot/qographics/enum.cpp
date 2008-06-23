// enum.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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

#include "enum.h"
#include "exceptions.h"

namespace QOGraphics
{

// ============================================================================
/// Default constructor. Initializes uncofigured Enum with 0 as defautl value
Enum::Enum()
{
	_defaultValue = 0;
	_value = 0;
}

// ============================================================================
/// Copy constructor
Enum::Enum( const Enum& src )
{
	_values = src._values;
	_defaultValue = src._defaultValue;
	_value = src._value;
}

// ============================================================================
/// Destructor
Enum::~Enum()
{
	// nope
}

// ============================================================================
/// Converts Enum to string, returnig string representation of current value.
/// If multiple strings are associated with value, returns firs one.
Enum::operator QString() const
{
	QList<QString> keys = _values.keys( _value );
	
	Q_ASSERT( keys.size() );
	
	return keys.first();
	
}

// ============================================================================
/// Convets Enum to integer, returning its current numeric value.
Enum::operator int() const
{
	return _value;
}

// ============================================================================
/// Assigns value from string, searching among avilable values.
Enum& Enum::operator = ( const QString& str )
{
	if ( _values.contains( str ) )
	{
		_value = _values[ str ];
		return *this;
	}
	
	throw Exception
		( QString("Ivalid property value: %1. Valid values are: %2")
			.arg( str )
			.arg( definition() )
		);	
}

// ============================================================================
/// Assigns value from integer.
Enum& Enum::operator = ( int i )
{
	QList<QString> keys = _values.keys( i );
	if ( keys.size() )
	{
		_value = i;
		return *this;
	}
	
	throw Exception( QString("Unknown enum value: %1").arg( i ) );
}

// ============================================================================
/// Adds value to list of available values
void Enum::addValue( int i, const QString& str, bool def /*= false*/ )
{
	_values[ str ] = i;
	
	if ( def )
	{
		_defaultValue = i;
		_value = i;
	}
}

// ============================================================================
/// Creates and returns human readable list of possible values, with default value marhed.
/// Like: "yes | {no}"
QString Enum::definition() const
{
	QStringList valueNames;
	
	foreach( QString str, _values.keys() )
	{
		if ( _values[str] == _defaultValue )
		{
			valueNames.append( QString("{%1}").arg( str ) );
		}
		else
		{
			valueNames.append( str );
		}
	}
	
	return valueNames.join( " | " );

}

}; // namespace

// EOF

