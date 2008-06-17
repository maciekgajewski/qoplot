// matrixcodec.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef MATRIXCODEC_H
#define MATRIXCODEC_H

#include <QVariant>

/**
Matrix coded is a tool thatr allows for squeziing matrix of QVariant values into QVariantList
(and vice-versa). As all property valeus has to be passed as QVariants, matrix is 
defined as QVariant vector (also convertible to QVariant itelf), \see Object::Matrix .

This tool allows for converting between matrix-like structure and QvariantList, both ways.

Use like this:

to encode matrix:
\code
MatrixCodec m( 3, 3 );
m.setValue( 1, 1, value11 );
...
m.setValue( 3, 3, value33 );
return m.matrix();
\endcode
to decode matrix:
\code
MatrixCodec m(matrix);
value11 = m.value( 1, 1 );
...
\endcode


@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class MatrixCodec
{
public:
	
	/// Initializes empty matrix with defined size
	MatrixCodec( int rows, int cols );
	/// Initializes basing on existing matrix
	MatrixCodec( const QVariantList& matrix );
	
	/// Returns value
	QVariant value( int row, int col ) const;
	
	/// Sets value
	void setValue( int row, int col, const QVariant& value );
	
	/// Rows count
	int rows() const { return _rows; }
	
	/// Cols count
	int cols() const { return _cols; }
	
	/// Matrix
	QVariantList matrix() const { return _matrix; }
	
	/// Creates single  value matrix
	static QVariantList scalar( const QVariant& value );

private:

	/// Calculates list index of matrix element
	int index( int row, int col ) const;

	int _rows, _cols;
	QVariantList _matrix;	///< Actual matrix
};

#endif // MATRIXCODEC_H

// EOF


