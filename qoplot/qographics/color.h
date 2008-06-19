// color.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSCOLOR_H
#define QOGRAPHICSCOLOR_H

#include <QVariant>
#include <QColor>
#include "matrix.h"

namespace QOGraphics 
{

/**
Type used to store color values. It can be set using string color representation 
or RGB vector, and backend may access it's value as QColor.

QVariant is used as trnasport type for colors, as it can contain string or vector.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class Color
{
public:
	Color();
	Color( const QColor& color ){ _color = color; }
	Color( Qt::GlobalColor color ){ _color = color; }
	~Color();
	
	// converters
	
	void fromVector( const Matrix& vector );
	void fromString( const QString& string );
	void fromVariant( const QVariant& variant );
	

	operator QColor() const { return _color; }
	
	QColor color() const { return _color; }
	
	Matrix toMatrix() const;
	QVariant toVariant() const;
	
	

private:

	static void initializeNamedColors();

	QColor _color;
	static QMap< QString, QColor> _namedColors;
};

}

#endif // QOGRAPHICSCOLOR_H

// EOF


