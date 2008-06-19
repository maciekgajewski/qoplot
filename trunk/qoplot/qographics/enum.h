// enum.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSENUM_H
#define QOGRAPHICSENUM_H

#include <QString>
#include <QMetaType>
#include <QMap>

namespace QOGraphics {

/**
Object used to store values of octave-style enumerations.
Value is stored as integer, and backed may convenientyl use integer representation.

QString is used as transport type to communicate with octave.

Exmaple: property 'Visible' has avialbel values "yes" and "no",
with corresponding numerical values 1 and 0.

Usage:

\code
Enum visible;

visible.addValue( 0, "no" );
visible.addValue( 1, "yes", true );

visible = "yes"

if ( visible )
{
	printf("this text is visible\n");
}

\endcode

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class Enum
{
public:

	// constructors

	Enum();
	Enum( const Enum& value );
	~Enum();

	// typecast

	operator QString() const;
	operator int() const;
	
	Enum& operator = ( const QString& str );
	Enum& operator = ( int i );
	
	// configuration
	
	void addValue( int i, const QString& str, bool def = false );
	int defaultValue() const { return _defaultValue; }

	QString definition() const;		///< Returns human-readable values definiot

private:

	QMap< int, QString > _values;	///< Possible values
	int _defaultValue;				///< Default value
	int _value;						///< Current value
};

}

//Q_DECLARE_METATYPE( QOGraphics::Enum ); TODO not needed?

#endif // QOGRAPHICSENUM_H

// EOF


