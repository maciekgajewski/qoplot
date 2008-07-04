// converters.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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

#include "converters.h"
namespace QOGraphics
{

// ============================================================================
/// Converts octave value into color. Color can be RGB triplet or string name.
QColor colorFromOctave( const octave_value& value )
{
	if ( value.is_string() )
	{
		return Qt::transparent;
	}
	if ( value.is_real_matrix() )
	{
		Matrix m = value.matrix_value();
		if ( m.nelem() < 3 )
		{
			return QColor( Qt::transparent ); // null color
		}
		
		QColor color;
		color.setRgbF( m.elem(0), m.elem(1), m.elem(2) );
		return color;
	}
	else
	{
		return Qt::transparent; 
	}
}

// ============================================================================
/// Converts style name into pen style.
Qt::PenStyle styleFromOctave( const std::string& name )
{
	if ( name == "none" )	return Qt::NoPen;
	if ( name == "-" )		return Qt::SolidLine;
	if ( name == ":" )		return Qt::DotLine;
	if ( name == "--" )		return Qt::DashLine;
	if ( name == "-." )		return Qt::DashDotLine;
	
	qWarning("Unknwon pen specification: %s", name.c_str() );
	
	return Qt::SolidLine;
	
}

// ============================================================================
/// Converts font weight name to QFont::Weight
QFont::Weight weightFromOctave( const std::string& name )
{
	if( name == "light" )	return QFont::Light;
	if( name == "normal" )	return QFont::Normal;
	if( name == "demi" )	return QFont::DemiBold;
	if( name == "bold" )	return QFont::Bold;
	
	qWarning("Unknwon font weight: %s", name.c_str() );
	
	return QFont::Normal;
}

// ============================================================================
/// Converts font style name to QFont::Style
QFont::Style fontStyleFromOctave( const std::string& name )
{
	if ( name == "normal" )		return QFont::StyleNormal;
	if ( name == "italic" )		return QFont::StyleItalic; 
	if ( name == "oblique" )	return QFont::StyleOblique;
	
	qWarning("Unknwon font style: %s", name.c_str() );
	
	return QFont::StyleNormal;
}

} // namespace

// EOF


