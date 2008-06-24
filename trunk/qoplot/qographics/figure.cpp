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
#include "axes.h"

namespace QOGraphics
{

// ============================================================================
// Constructor
Figure::Figure( Root* root, Handle handle, QObject* parent ) : Object( root, handle, parent )
{
	_window.show();
	
	connect( &_window, SIGNAL(closed()), SLOT(windowClosed()) );
	connect( &_window, SIGNAL(resized()), SLOT(windowResized()) );
	
	// default color
	_backgroundColor = QApplication::palette().color( QPalette::Button );
	_window.scene.setBackgroundBrush( _backgroundColor.color() );
	_currentAxes = InvalidHandle;
	
	// init colormap
	initColorMap();
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
	g.setY( int( screenHeight - pos.value( 1, 2 ) - pos.value( 1, 4 ) ) );
	g.setX( int( pos.value( 1, 1 ) ) );
	
	g.setWidth( int( pos.value( 1, 3 ) ) );
	g.setHeight( int( pos.value( 1, 4 ) ) );
	
	//qDebug("setting geometry: %d,%d %dx%d", g.x(), g.y(), g.width(), g.height() );
	
	_window.setGeometry( g );
}

// ============================================================================
/// Sets figure background color.
void Figure::setColor( const QVariant& color )
{
	_backgroundColor.fromVariant( color );
	_window.scene.setBackgroundBrush( _backgroundColor.color() );
}

// ============================================================================
/// Sets current axes.
void Figure::setCurrentAxes( const Matrix& m )
{
	_currentAxes = Handle( m.toScalar() );
}

// ============================================================================
/// Creates axes with specifed handle. If axes already exists for specified sublot area, they are removed
Axes* Figure::createAxes( Handle h )
{
	Axes* pAxes = new Axes( root(), h, this );
	connect( pAxes, SIGNAL(destroyed( QObject* )), SLOT(axesDeleted(QObject*) ) );
	
	_currentAxes = h;
	
	windowResized(); // To let axes knwo about our position
	
	return pAxes;
}

// ============================================================================
/// Handles window resize event. Repositons axes on figure.
void Figure::windowResized()
{
	QList<Axes*> axes = findChildren<Axes*>();
	foreach( Axes* a, axes )
	{
		a->setFigureRect( _window.view->rect() );
		a->sizeChanged();
	}
}

// ============================================================================
/// Forces scene repaint
void Figure::redraw()
{
	_window.scene.update();
}

// ============================================================================
/// Removes all axes form figure
void Figure::clear()
{
	QList<Axes*> axes = findChildren<Axes*>();
	
	foreach( Axes* a, axes )
	{
		disconnect( a, NULL, this, NULL );
		a->free();
		delete a;
	}
	
	_currentAxes = InvalidHandle;
}

// ============================================================================
/// Handles axes deletion. If axes are current, invalidates current axes handle
void Figure::axesDeleted( QObject* pAxes )
{
	Axes* a = qobject_cast<Axes*>( pAxes );
	if ( a && a->handle() == _currentAxes )
	{
		_currentAxes = InvalidHandle;
	}
}

// ============================================================================
/// Initialzies color map with nice 64 green-to-red color.
void Figure::initColorMap()
{
	const int colors = 64;
	Matrix map( colors, 3 );
	
	for( int i = 0; i < colors; i++ )
	{
		double green	= double( colors - i ) / colors;
		double red		= double(i) / colors;
		
		
		qDebug("red: %f, green: %f", red, green ); // TODOD remove
		map.setValue( i+1, 1, red );
		map.setValue( i+1, 2, green );
		map.setValue( i+1, 3, 0.0 ); // no blue
	}
	
	_colorMap = map;
}


}; // namespace

// EOF

