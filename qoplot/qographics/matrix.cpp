// matrix.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#include "matrix.h"

// ============================================================================
/// Default constructor, creates empty matrix;
Matrix::Matrix()
{
	_rows = 0;
	_cols = 0;
}

// ============================================================================
/// Creates matrix of specified size
Matrix::Matrix( int rows, int cols )
{
	Q_ASSERT( rows >= 0 && cols >= 0 );
	
	_rows = rows;
	_cols = cols;
	init();
}

// ============================================================================
/// Copy constructor
Matrix::Matrix( const Matrix& src )
{
	_rows = src._rows;
	_cols = src._cols;
	
	_data = src._data;
}

// ============================================================================
/// Destructor
Matrix::~Matrix()
{
	// nope ;)
}

// ============================================================================
/// Changexs matrix size. All data is lost.
void Matrix::resize( int r, int c )
{
	Q_ASSERT( c >= 0 && r >= 0 );
	
	_rows = r;
	_cols = c;
	init();
}

// ============================================================================
/// Retuens data from specific cell.
///\note row nad column index are 1-based!
double Matrix::value( int r, int c ) const
{
	// TODO add full index checking
	return _data.value( index( r, c ), 0.0 );
}

// ============================================================================
/// Sets data in specific cell.
///\note row nad column index are 1-based!
void Matrix::setValue( int r, int c, double v )
{
	// TODO add full index checking
	//qDebug("Matrix::setValue: setting value at %d,%d, index=%d", r, c, index(r,c) );
	_data[ index( r, c ) ] = v;
}

// ============================================================================
/// Initializes matrix with empty values
void Matrix::init()
{
	_data.clear();
	
	for ( int i = 0; i < _rows * _cols; i++ )
	{
		_data.append( 0.0 );
	}
}

// ============================================================================
/// Calculates list index from row and column
int Matrix::index( int r, int c ) const
{
	// stroe data in rows
	return (c-1) + _cols*(r-1);
}

// ============================================================================
/// Creates calar - 1x1 matrix with single value.
Matrix Matrix::scalar( double v )
{
	Matrix m(1, 1);
	m.setValue( 1, 1, v );
	
	return m;
}

// ============================================================================
/// Streaming operator. Stores matrix into data stream.
QDataStream& operator<<( QDataStream& out, const Matrix& /*matrix*/ )
{
	// TODO
	return out;
}

// ============================================================================
/// Streaming operator. Reads matrix from data stream. 
QDataStream& operator>>( QDataStream& in, Matrix& /*matrix*/ )
{
	// TODO
	return in;
}

// EOF

