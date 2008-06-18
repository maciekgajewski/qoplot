// matrix.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef MATRIX_H
#define MATRIX_H

#include <QVariant>
#include <QDataStream>

/**
This is a matrix class. It is used across the package to store matrix data.
Each matrix consist of QVariant cells arranged in rows and columns.

Matrix is registered in Qt's meta-type system, and can be stored in QVariant,
QdataStream etc.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class Matrix
{
public:

	// construction / destruction
	
	Matrix();						///< Creates null matrix
	Matrix( int rows, int cols );	///< Creates matrix of specified size
	Matrix( const Matrix& );		///< Copy
	virtual ~Matrix();				///< Destructor
	
	// properties
	
	int cols() const { return _cols; }	///< Columns
	int rows() const { return _rows; }	///< Rows
	bool isNull() { return _cols * _rows == 0; }
	
	void resize( int r, int v );		///< Resizes matrix
	
	// data access
	
	double value( int r, int c ) const;
	void setValue( int r, int c, double v );

	// utilities
	
	/// Creates 1x1 matrix with single value
	static Matrix scalar( double v );

private:

	int index( int r, int c ) const;
	void init();

	int _rows;
	int _cols;
	
	// TODO make use of imlicit sharing
	QList<double>	_data;
};

// serialization

QDataStream& operator<<( QDataStream& out, const Matrix& matrix );
QDataStream& operator>>( QDataStream& in, Matrix& matrix );

Q_DECLARE_METATYPE( Matrix );

#endif // MATRIX_H

// EOF


