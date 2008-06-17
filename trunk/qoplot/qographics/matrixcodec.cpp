// matrixcodec.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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

// ============================================================================
// Initializes empty matrix
MatrixCodec::MatrixCodec( int rows, int cols )
{
	Q_ASSERT( rows >= 0 && cols >= 0 );
	
	_cols = cols;
	_rows = rows;
	
	if ( rows > 0 && cols > 0 )
	{
		_matrix.append( rows );
		_matrix.append( cols );
		
		// fill
		for ( int i = 0; i < rows * cols; i++ )
		{
			_matrix.append( QVariant() );
		}
	}
}

// ============================================================================
// Initializes on exisintg matrix
MatrixCodec::MatrixCodec( const QVariantList& matrix )
{
	_matrix = matrix;
	if ( _matrix.size() > 1 )
	{
		_rows = matrix[ 0 ].toInt();
		_cols = matrix[ 1 ].toInt();
		Q_ASSERT( _rows > 0 && _cols > 0 );
		Q_ASSERT( matrix.size() == 2 + _rows * _cols );
	}
	else
	{
		// null
		_rows = 0;
		_cols = 0;
	}
	
}

// ============================================================================
// Reads value from matrix
QVariant MatrixCodec::value( int row, int col ) const
{
	return _matrix.value( index( row, col ), QVariant() );
}

// ============================================================================
// Sets value
void MatrixCodec::setValue( int row, int col, const QVariant& value )
{
	_matrix[ index( row, col ) ] = value;
}

// ============================================================================
// Utility creating single-value matrix woth specified value
QVariantList MatrixCodec::scalar( const QVariant& value )
{
	QVariantList matrix;
	matrix << QVariant( 1 ) << QVariant( 1 ) << value;
	
	return matrix;
}

// ============================================================================
// Calculates list index of specified matrix element
int MatrixCodec::index( int row, int col ) const
{
	return 2 + (row-1) + (col-1)*_rows;
}

// EOF

