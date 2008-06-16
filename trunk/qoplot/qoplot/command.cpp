// command.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#include "command.h"

// ===========================================================================
/// Constructor
Command::Command( int fd ) : _command( fd )
{
	// nope
}

// ===========================================================================
/// Destructor
Command::~Command()
{
	// nope
}

// ===========================================================================
/// Returns input argument. In case of error returns invalid QVariant
QVariant Command::argin( int i ) const
{
	const ocpl::parameter* pArg = _command.argin( i );
	
	if ( ! pArg )
	{
		return QVariant();
	}
	
	// determine type
	switch( pArg->id )
	{
		case ocpl::real:
			return QVariant( double( * pArg->real_data() ) );
		
		case ocpl::str:
			return QVariant( QString( pArg->str_data() ) );
		
		default:
			qDebug("Command::argin: Unknown argument type: %d", pArg->id );
			return QVariant();
	}
}

// ===========================================================================
void Command::addDoubleArgout( int index, long row, long col, double value )
{
	// TODO i don't like this allocation
	double* pData = new double( value );
	_command.argout( index, ocpl::real, row, col, reinterpret_cast<char*>(pData), true );
}

// ===========================================================================
void Command::addStringArgout( int index, long row, long col, const QString& value )
{
	// TODO i don't like this allocation
	QByteArray array = value.toUtf8();
	char* pData = new char[ array.size() ];
	qstrcpy( pData, array.data() );
	
	_command.argout( index, ocpl::str, row, col, pData, true );
}

// ===========================================================================
void Command::retError( const QString& msg )
{
	ocpl::ret_error( _command, msg.toUtf8().data() );
}

// ===========================================================================
void Command::retWarning( const QString& msg )
{
	ocpl::ret_warning( _command, msg.toUtf8().data() );
}

// EOF



