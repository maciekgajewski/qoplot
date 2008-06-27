// color.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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

#include "exceptions.h"
#include "color.h"

namespace QOGraphics {

QMap< QString, QColor> Color::_namedColors;

// ============================================================================
/// Constructor. Initializes color with white.
Color::Color()
{
	if ( _namedColors.isEmpty() )
	{
		initializeNamedColors();
	}
	_color = Qt::white;
}

// ============================================================================
// Destructor
Color::~Color()
{
	// none
}

// ============================================================================
/// Sets color from vector. Vector should be 1x3 RGB
void Color::fromVector( const Matrix& vector )
{
	if ( vector.vectorSize() < 3 )
	{
		throw Exception( "Color should be described by 3-element vector" );
	}
	
	_color = QColor
		( int(vector.vectorValue( 1 ) * 255 )
		, int(vector.vectorValue( 2 ) * 255 )
		, int(vector.vectorValue( 3 ) * 255 )
		);
		
	// apply alpha if available
	if ( vector.vectorSize() > 3 )
	{
		_color.setAlphaF( vector.vectorValue( 4 ) );
	}
}

// ============================================================================
/// Sets color from string
void Color::fromString( const QString& string )
{
	_color = _namedColors.value( string.toLower(), _color ); // sue current color if name invalid
}

// ============================================================================
/// Initializes named colors map. Called once.
void Color::initializeNamedColors()
{
	_namedColors["yellow"]	= Qt::yellow;
	_namedColors["y"]		= Qt::yellow;
	_namedColors["magenta"]	= Qt::magenta;
	_namedColors["m"]		= Qt::magenta;
	_namedColors["cyan"]	= Qt::cyan;
	_namedColors["c"]		= Qt::cyan;
	_namedColors["red"]		= Qt::red;
	_namedColors["r"]		= Qt::red;
	_namedColors["green"]	= Qt::green;
	_namedColors["g"]		= Qt::green;
	_namedColors["blue"]	= Qt::blue;
	_namedColors["b"]		= Qt::blue;
	_namedColors["white"]	= Qt::white;
	_namedColors["w"]		= Qt::white;
	_namedColors["black"]	= Qt::black;
	_namedColors["k"]		= Qt::black;
	
	// and few my extras
	_namedColors["gray"]	= Qt::gray;
	
}

// ============================================================================
/// Sets color from variant. Variant should contain color, string or matrix.
void Color::fromVariant( const QVariant& variant )
{
	if( variant.userType() == qMetaTypeId<Matrix>() )
	{
		fromVector( variant.value<Matrix>() );
	}
	else switch( variant.type() )
	{
		case QVariant::String:
			fromString( variant.toString() );
			break;
			
		case QVariant::Color:
			_color = variant.value<QColor>();
			break;
			
		default:
			qDebug("Can not set color from variant type %s", QVariant::typeToName(variant.type() ) );
			break; 
	}
}

// ============================================================================
/// Creates RGB 3x1 vector from color.
Matrix Color::toMatrix() const
{
	Matrix m(1, 4 );
	
	m.setVectorValue( 1 , _color.redF() );
	m.setVectorValue( 2 , _color.greenF() );
	m.setVectorValue( 3 , _color.blueF() );
	m.setVectorValue( 4 , _color.alphaF() );

	return m;
}

// ============================================================================
/// Returns color as vector, wrapped with QVariant
QVariant Color::toVariant() const
{
	return qVariantFromValue< Matrix >( toMatrix() );
}

}
