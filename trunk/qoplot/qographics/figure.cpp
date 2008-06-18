// figure.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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

#include <QDesktopWidget>

#include "exceptions.h"
#include "figure.h"

namespace QOGraphics
{

// ============================================================================
// Constructor
Figure::Figure( Root* root, Handle handle, QObject* parent ) : Object( root, handle, parent )
{
	_window.show();
	
	connect( &_window, SIGNAL(closed()), SLOT(windowClosed()) );
}

// ============================================================================
// Destructor
Figure::~Figure()
{
	// nope
}

// ============================================================================
/// Handles window closing. Destroys object.
void Figure::windowClosed()
{
	deleteLater();
}

// ============================================================================
/// Returns window positon as vector [left bottom width height]
Matrix Figure::getPosition() const
{
	Matrix pos( 1, 4 );
	
	int screenHeight = QApplication::desktop()->height();
	QRect g = _window.geometry();
	int bottom = screenHeight - g.y() - g.height();
	qDebug("screen height: %d, geom y %d, geom h %d", screenHeight,  g.y(), g.height() );
	
	pos.setValue( 1, 1, g.x() ); // left
	pos.setValue( 1, 2, bottom ); // bottom
	pos.setValue( 1, 3, g.width() );
	pos.setValue( 1, 4, g.height() );
	
	return pos;
	
}

// ============================================================================
/// Sets window sie and postion as vector [left bottom width height]
void Figure::setPosition( const Matrix& pos )
{
	if ( pos.cols() < 4 || pos.rows() < 1 )
	{
		throw Exception("Figure postion must be a 4x1 vector");
	}
	
	int screenHeight = QApplication::desktop()->height();
	QRect g;
	g.setY( screenHeight - pos.value( 1, 2 ) - pos.value( 1, 4 ) );
	g.setX( pos.value( 1, 1 ) );
	
	g.setWidth( pos.value( 1, 3 ) );
	g.setHeight( pos.value( 1, 4 ) );
	
	qDebug("setting geometry: %d,%d %dx%d", g.x(), g.y(), g.width(), g.height() );
	
	_window.setGeometry( g );
}

}; // namespace

// EOF

