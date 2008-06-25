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

#include <QPrinter>
#include <QDesktopWidget>
#include <QSvgGenerator>

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
	
	// init paper type
	_paperType.addValue( QPrinter::A0, "A0" );
	_paperType.addValue( QPrinter::A1, "A1" );
	_paperType.addValue( QPrinter::A2, "A2" );
	_paperType.addValue( QPrinter::A3, "A3" );
	_paperType.addValue( QPrinter::A4, "A4", true ); // TODO get default from somwhere, or store last value in persistent storage
	_paperType.addValue( QPrinter::A5, "A5" );
	_paperType.addValue( QPrinter::A6, "A6" );
	_paperType.addValue( QPrinter::A7, "A7" );
	_paperType.addValue( QPrinter::A8, "A8" );
	_paperType.addValue( QPrinter::A9, "A9" );
	_paperType.addValue( QPrinter::B0, "B0" );
	_paperType.addValue( QPrinter::B1, "B1" );
	_paperType.addValue( QPrinter::B2, "B2" );
	_paperType.addValue( QPrinter::B3, "B3" );
	_paperType.addValue( QPrinter::B4, "B4" );
	_paperType.addValue( QPrinter::B5, "B5" );
	_paperType.addValue( QPrinter::B6, "B6" );
	_paperType.addValue( QPrinter::B7, "B7" );
	_paperType.addValue( QPrinter::B8, "B8" );
	_paperType.addValue( QPrinter::B9, "B9" );
	_paperType.addValue( QPrinter::B10, "B10" );
	_paperType.addValue( QPrinter::Letter, "usletter" );
	_paperType.addValue( QPrinter::Legal, "uslegal" );
	_paperType.addValue( QPrinter::Tabloid, "tabloid" );
	_paperType.addValue( QPrinter::Executive, "executive" );
	_paperType.addValue( QPrinter::Folio, "folio" );
	_paperType.addValue( QPrinter::Ledger, "ledger" );
	
	_paperOrientation.addValue( QPrinter::Portrait, "portrait", true );
	_paperOrientation.addValue( QPrinter::Landscape, "landscape" );
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
		
		map.setValue( i+1, 1, red );
		map.setValue( i+1, 2, green );
		map.setValue( i+1, 3, 0.0 ); // no blue
	}
	
	_colorMap = map;
}

// ============================================================================
/// Returns 1x1 matrix with current axis handle, or empty matrix if no current axes.
Matrix Figure::getCurrentAxes() const
{
	if ( _currentAxes != InvalidHandle )
	{
		return Matrix::scalar( _currentAxes );
	}
	else
	{
		return Matrix();
	}
}

// ============================================================================
/// Prints figure content to file, ussing specified format and resultion.
void Figure::print( const QString& fileName, int device, int resolution, QSize size /*= QSize()*/ )
{
	// for printign - set background to white
	_window.scene.setBackgroundBrush( Qt::white );

	try
	{
	if ( device == Jpeg )
	{
		printToPixmap( fileName, "jpeg", resolution, size );
	}
	else if ( device == Png )
	{
		printToPixmap( fileName, "png", resolution, size );
	}
	else if ( device == Pdf )
	{
		printToPrinter( fileName, QPrinter::PdfFormat );
	}
	else if ( device == Ps )
	{
		printToPrinter( fileName, QPrinter::PostScriptFormat, resolution );
	}
	else if ( device == Svg )
	{
		printToSvg( fileName );
	}
	else
	{
		qDebug("Sorry, EPS format not supported right now.");
	}
	
	}
	catch ( const Exception& e )
	{
		_window.scene.setBackgroundBrush( _backgroundColor.color() );
		throw e;
	}
	
	// restore background
	_window.scene.setBackgroundBrush( _backgroundColor.color() );
}

// ============================================================================
/// Prints figure content to pixmap. Saves pixmap to file usign specified format.
/// Uses supplied resolution, or screen resolution if 0.
/// If size is not specifiedm uses current figure size.
void Figure::printToPixmap( const QString& fileName, const char* format, int resolution /*= 0*/, QSize size /*= QSize()*/ )
{
	// get size
	QSize viewportSize = _window.view->viewport()->size();
	if ( ! size.isValid() )
	{
		size = _window.view->viewport()->size();
	}
	
	if ( size.isNull() || ! size.isValid() )
	{
		throw Exception("Ivalid printing area.");
	}
	
	// initialize image
	QImage image( size, QImage::Format_RGB32 );
	QRect targetRect = QRect( 0, 0, size.width(), size.height() );
	QRectF sourceRect = QRectF( 0, 0, viewportSize.width(), viewportSize.height() );
	
	// apply resolution
	if ( resolution != 0 )
	{
		const double ipm = 39.37; // inches per meter, courtesy of google calculator
		image.setDotsPerMeterX( int( resolution * ipm ) );
		image.setDotsPerMeterY( int( resolution * ipm ) );
	}
	
	// render
	QPainter painter( & image );
	_window.scene.render( &painter, targetRect, sourceRect, Qt::IgnoreAspectRatio );
	painter.end();
	
	// save image to file
	image.save( fileName, format );
}

// ============================================================================
/// Pritins figure to dfile using QPrinter facilities. Format is QPrinter::OutputFormat.
void Figure::printToPrinter( const QString& fileName, int format, int resolution /*= 0*/ )
{
	// get size
	QSize viewportSize = _window.view->viewport()->size();
	QRectF sourceRect = QRectF( 0, 0, viewportSize.width(), viewportSize.height() );
	
	// init printer
	QPrinter printer;
	
	printer.setPageSize( QPrinter::PageSize( int(_paperType) ) );
	printer.setOrientation( QPrinter::Orientation( int(_paperOrientation) ) );
	printer.setOutputFileName( fileName );
	printer.setOutputFormat( QPrinter::OutputFormat( format ) );
	
	// set resolution
	if ( resolution != 0 )
	{
		printer.setResolution( resolution );
	}
	
	// render
	QPainter painter( & printer );
	_window.scene.render( &painter, QRectF(), sourceRect, Qt::KeepAspectRatio );
	painter.end();
	
}

// ============================================================================
/// Prints figure to SVG
void Figure::printToSvg( const QString& fileName )
{
	// get size
	QSize viewportSize = _window.view->viewport()->size();
	QRectF sourceRect = QRectF( 0, 0, viewportSize.width(), viewportSize.height() );
	
	// init svg generator
	QSvgGenerator generator;
	generator.setFileName( fileName );
	generator.setSize( viewportSize );
	
	// render
	QPainter painter( & generator );
	_window.scene.render( &painter, QRectF(), sourceRect, Qt::KeepAspectRatio );
	painter.end();
	
}

}; // namespace

// EOF

