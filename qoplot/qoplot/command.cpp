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
#include "matrix.h"

// ===========================================================================
/// Constructor
Command::Command( int fd ) : _command( fd )
{
	_fd = fd;
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
/// Adds scalar doble argoment to output
void Command::addDoubleArgout( int index, double value )
{
	// TODO i don't like this allocation
	double* pData = new double( value );
	_command.argout( index, ocpl::real, 1, 1, reinterpret_cast<char*>(pData), true );
}

// ===========================================================================
/// Adds scalar string value to output
void Command::addStringArgout( int index, const QString& value )
{
	// TODO i don't like this allocation
	QByteArray array = value.toUtf8();
	char* pData = new char[ array.size() + 1 ];
	qstrcpy( pData, array.data() );
	
	_command.argout( index, ocpl::str, array.size()+1, 1, pData, true );
}


// ===========================================================================
/// Returns command with error
void Command::retError( const QString& msg )
{
	ocpl::ret_error( _command, msg.toUtf8().data() );
}

// ===========================================================================
/// Returns command with warning
void Command::retWarning( const QString& msg )
{
	ocpl::ret_warning( _command, msg.toUtf8().data() );
}

// ============================================================================
// Adds output arg of any type.
void Command::addArgout( int index, const QVariant& value )
{
	// string
	if ( value.type() == QVariant::String )
	{
		addStringArgout( index, value.toString() );
	}
	// number
	else if ( value.canConvert( QVariant::Double ) )
	{
		addDoubleArgout( index, value.toDouble() );
	}
	// null
	if ( value.type() == QVariant::Invalid )
	{
		// return explicit null
		_command.argout( index, ocpl::real, 0, 0, NULL, true );
	}
	// matrix
	// TODO obsolete
	/*
	else if ( value.type() == QVariant::List )
	{
		// TODO for now assume that all matrixes are filled with doubles
		MatrixCodec codec( value.toList() );
		
		double* pData = new double[ codec.rows() * codec.cols() ];
		// lay out data columnwise
		// TODO mayb integrate this in MatrixCodec
		for ( int r = 0; r < codec.rows(); r++ )
		{
			for ( int c = 0; c < codec.cols(); c++ )
			{
				pData[ r + c * codec.rows() ] = codec.value( r+1, c+1 ).toDouble();
			}
		}
		
		_command.argout
			( index, ocpl::real, codec.rows(), codec.cols()
			, reinterpret_cast<char*>(pData), true );
		
	}
	*/
	else if ( value.userType() == qMetaTypeId<Matrix>() )
	{
		Matrix matrix = qvariant_cast< Matrix >( value );
		
		double* pData = new double[ matrix.rows() * matrix.cols() ];
		for ( int r = 0; r < matrix.rows(); r++ )
		{
			for ( int c = 0; c < matrix.cols(); c++ )
			{
				pData[ r + c * matrix.rows() ] = matrix.value( r+1, c+1 ).toDouble();
			}
		}
		
		_command.argout
			( index, ocpl::real, matrix.rows(), matrix.cols()
			, reinterpret_cast<char*>(pData), true );
		
	}
	else
	{
		// TODO add matrix here
		qDebug("Command::addArgout: unknown value type: %s", QVariant::typeToName( value.type() ) );
		// add null argument
		_command.argout( index, ocpl::real, 0, 0, NULL, true );
	}
}

// EOF



