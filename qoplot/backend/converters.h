// converters.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef CONVERTERS_H
#define CONVERTERS_H

#include <QColor>
#include <QFont>

#include <octave/oct.h>

///\file converters.h contains definition of function converting internal octave data into
/// types taht could be directly used by Qt.

namespace QOGraphics
{

/// Converts octave value into QColor.
QColor colorFromOctave( const octave_value& value );

/// Convers style name into Qt pen style
Qt::PenStyle styleFromOctave( const std::string& name );

/// Converts font weight name to QFont::Weight
QFont::Weight weightFromOctave( const std::string& name );

/// Converts font style name to QFont::Style
QFont::Style fontStyleFromOctave( const std::string& name );

} // namespace


#endif // CONVERTERS_H

// EOF

