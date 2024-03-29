// interpreter.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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

#include <QStringList>
#include <QApplication>

#include "command.h"
#include "root.h"
#include "interpreter.h"
#include "exceptions.h"
#include "axes.h"
#include "figure.h"

using namespace QOGraphics;

// ============================================================================
// Constructor
Interpreter::Interpreter()
{
	// nope
}

// ============================================================================
// Destructor
Interpreter::~Interpreter()
{
	// nada
}

// ============================================================================
/// Main command interpreter interface. Interprets command, performs action on graphics objects,
/// feeds command back with return values
void Interpreter::interpret( Command& cmd, Root& root )
{
	try
	{
	// interpret commands
	switch( cmd.id() )
	{
		// Get
		case ocpl::get:
		{
			get( cmd, root );
			break;
		}
		
		// Set
		case ocpl::set:
		{
			set( cmd, root );
			break;
		}
		
		// Figure
		case ocpl::figure:
		{
			figure( cmd, root );
			break;
		}
		
		// Axes
		case ocpl::axes:
		{
			axes( cmd, root );
			break;
		}
		
		// Text
		case ocpl::text:
		{
			text( cmd, root );
			break;
		}
		
		// Line
		case ocpl::line:
		{
			line( cmd, root );
			break;
		}
		
		// Cla
		case ocpl::cla:
		{
			cla( cmd, root );
			break;
		}
		
		// Delete:
		case ocpl::del:
		{
			del( cmd, root );
			break;
		}
		
		// Clf
		case ocpl::clf:
		{
			clf( cmd, root );
			break;
		}
		
		// Redraw
		case ocpl::redraw:
		{
			redraw( cmd, root );
			break;
		}
		
		// Ishnd
		case ocpl::ishnd:
		{
			ishnd( cmd, root );
			break;
		}
		
		// Iamge
		case ocpl::image:
		{
			image( cmd, root );
			break;
		}
		
		// Print
		case ocpl::print:
		{
			print( cmd, root );
			break;
		}
		
		// Patch
		case ocpl::patch:
		{
			patch( cmd, root );
			break;
		}
		
		default:
			; // nope
	}
	if( ! cmd.parsed() )
	{
		cmd.retError("Unknown command");
		qDebug("Unknown command %d", cmd.id() );
	}
	}
	catch( const Exception& e )
	{
		cmd.retError( e.msg() );
	}
	cmd.ret();
}

// ============================================================================
// 'get' implementation
void Interpreter::get( Command& cmd, Root& root )
{
	//qDebug("interpreter::get"); 
	// test input params
	if( cmd.nargin() < 1 || cmd.nargin() > 2 )
	{
		cmd.retError("Get: accepts 1 or 2 args");
		return;
	}
	else if( cmd.argin(0).userType() != qMetaTypeId<Matrix>() )
	{
		cmd.retError("Get: first arg should be handle");
		return;
	}
	else if( cmd.nargin() > 1 && cmd.argin(1).type() != QVariant::String )
	{
		cmd.retError("Get: second arg should be property name");
		return;
	}
	
	// check if object exists
	Handle h = Handle( cmd.arginAsMatrix(0).toScalar() );
	Object* pObject = root.objectByHandle( h );
	
	if ( ! pObject )
	{
		cmd.retError("No such object");
		return;
	}
	
	// one param - get all properties
	if ( cmd.nargin() == 1 )
	{
		// TODO there is no way to return structure. Add it!
		// TODO and maybe tis is not neded and should be handled by oget.m?
		QStringList properties = pObject->properties();
		int c = properties.size();
		cmd.setArgoutNum( c );
		if ( c > 0 )
		{
			for ( int i = 0; i < c; i++ )
			{
				cmd.addStringArgout( i, properties[ i ] );
			}
		}
		else
		{
			cmd.setArgoutNum( 0 );
		}
	}
	else
	{
		QString propName = cmd.argin(1).toString();
		QVariant value = pObject->getProperty( propName );
		//qDebug("getting property %s", qPrintable( propName ) );
		cmd.addArgout( 0, value );
	}
}

// ============================================================================
// 'set' implementation
void Interpreter::set( Command& cmd, Root& root )
{
	if(cmd.nargin()!=3)
	{
		cmd.retError("Set: accepts 3 arguments");
	}
	else if( cmd.argin(0).userType() != qMetaTypeId<Matrix>() )
	{
		cmd.retError("Set: first arg should be handle");
	}
	else if( cmd.argin(1).userType() != QVariant::String )
	{
		cmd.retError("Set: second arg should be property name");
	}
	else
	{
		// check if object exists
		Handle h = Handle( cmd.arginAsMatrix(0).toScalar() );
		Object* pObject = root.objectByHandle( h );
		if ( ! pObject )
		{
			cmd.retError("No such object");
			return;
		}
	
		QString propName = cmd.argin(1).toString();
		pObject->setProperty( propName, cmd.argin(2) );
		cmd.setArgoutNum( 0 );
	}
}

// ============================================================================
/// 'figure' command implementation.
void Interpreter::figure( Command& cmd, Root& root )
{
	// This command has possible behaviors:
	// 1 - passed w/o args - creates new figure, allocates hanlde, returns allocated hanlde
	// 2 - passed with existing figure handle - makes the figure current
	// 3 - passed with unused handle - creates new figure ans assings it specified handle
	// 4 - passed with handle of existing object wich isn't figure - return error
	
	if( cmd.nargin()>1 )
	{
		cmd.retError("figure accepts 0 or 1 arguments");
		return;
	}
	
	Handle h = Object::InvalidHandle;
	
	if( cmd.nargin() == 1 )
	{
		Handle fig = Handle(cmd.arginAsMatrix(0).toScalar());
		
		// get bject with this hanlde
		Object* pObject = root.objectByHandle( fig );
		if ( ! pObject )
		{
			// handle is free, may be used as new figure handle (case 3)
			h = root.addFigure( fig );
		}
		else
		{
			// if objects is a figure
			if ( pObject->getType() == "figure" )
			{
				// make figure current (case 2 )
				root.setCurrentFigure( fig );
				h = fig;
			}
			// objects is not a figure - error (case 4 )
			else
			{
				cmd.retError( "Object is not a figure");
				return;
			}
		}
	}
	else
	{
		// create new figure, allocate handle (case 1 )
		h = root.addFigure();
	}
	
	//return handle
	cmd.addDoubleArgout( 0, h );
}

// ============================================================================
/// Creates axes and current figure. If there is no figure - creates figure too.
void Interpreter::axes( Command& cmd, Root& root )
{
	Handle fig = root.currentFigure();
	
	// create figure if doesn't exists
	if ( fig == Object::InvalidHandle )
	{
		fig = root.addFigure();
	}
	
	Handle axes = root.createObject( "axes", fig );
	
	cmd.setArgoutNum( 1 );
	cmd.addDoubleArgout( 0, axes );
}

// ============================================================================
/// Creates text object on current axes
void Interpreter::text( Command& cmd, Root& root )
{
	// check params
	if ( cmd.nargin() < 2 )
	{
		cmd.retError("Text requires 2 arguments.");
		return;
	}
	
	if( cmd.argin(0).userType() != qMetaTypeId<Matrix>() )
	{
		cmd.retError("Text: first argument should be matrix");
		return;
	}
	
	if( cmd.argin(1).userType() != QVariant::String )
	{
		cmd.retError("Text: second argument should be string");
	}
	
	Matrix position = cmd.arginAsMatrix( 0 );
	QString string = cmd.arginAsString( 1 );
	
	// create text object
	root.makeSureAxesCreated();
	Handle h = root.createObject( "text" );
	
	Object* pObject = root.objectByHandle( h );
	
	if ( pObject )
	{
		pObject->setProperty( "String", string );
		Matrix position3( 1, 3 );
		position3.setVectorValue( 1, position.vectorValue( 1 ) );
		position3.setVectorValue( 2, position.vectorValue( 2 ) );
		pObject->setProperty( "Position", qVariantFromValue<Matrix>( position3 ) );
		
		cmd.setArgoutNum( 1 );
		cmd.addDoubleArgout( 0, h );
	}
	else
	{
		cmd.retError( "Can't create text object" );
	}
}

// ============================================================================
/// Creates line object on current axes
void Interpreter::line( Command& cmd, Root& root )
{
	// check params
	if ( cmd.nargin() < 2 )
	{
		cmd.retError("Line requires 2 arguments.");
		return;
	}
	
	if( cmd.argin(0).userType() != qMetaTypeId<Matrix>() || cmd.argin(1).userType() != qMetaTypeId<Matrix>() )
	{
		cmd.retError("Text: first and second arguments should be matrices");
		return;
	}
	
	Matrix x = cmd.arginAsMatrix( 0 );
	Matrix y = cmd.arginAsMatrix( 1 );
	
	// create object
	root.makeSureAxesCreated();
	Handle h = root.createObject( "line" );
	
	Object* pObject = root.objectByHandle( h );
	
	if ( pObject )
	{
		pObject->setProperty( "XData", qVariantFromValue<Matrix>( x ) );
		pObject->setProperty( "YData", qVariantFromValue<Matrix>( y ) );
		
		cmd.setArgoutNum( 1 );
		cmd.addDoubleArgout( 0, h );
	}
	else
	{
		cmd.retError( "Can't create line object" );
	}
}

// ============================================================================
/// clears current axes
void Interpreter::cla( Command& cmd, Root& root )
{
	root.makeSureAxesCreated();
	Handle h = root.currentAxes();
	
	Axes* pAxes = qobject_cast<Axes*>( root.objectByHandle( h ) );
	
	if ( pAxes )
	{
		pAxes->clear();
		pAxes->reset();
		cmd.setArgoutNum( 0 );
	}
	else
	{
		cmd.retError("Couldn't get current axes");
	}
}

// ============================================================================
/// Deletes object
void Interpreter::del( Command& cmd, Root& root )
{
	// check params
	if ( cmd.nargin() < 1 )
	{
		cmd.retError("Delete requires argument.");
		return;
	}
	
	Handle h = Handle(cmd.arginAsMatrix(0).toScalar());
	
	// special case - if root deleted - exit
	if ( h == Object::RootHandle )
	{
		cmd.setArgoutNum( 0 );
		root.free();
		qApp->quit();
		return;
	}
	else
	{
		Object* pObject = root.objectByHandle( h );
		if ( pObject )
		{
			delete pObject;
			cmd.setArgoutNum( 0 );
		}
		else
		{
			cmd.retError("Ivalid handle: no such object.");
		}
	}
}

// ============================================================================
/// Redraws current figure
void Interpreter::redraw( Command& cmd, Root& root )
{
	Figure* pFig = qobject_cast<Figure*>( root.objectByHandle( root.currentFigure() ) );
	
	if ( pFig )
	{
		pFig->redraw();
	}
	
	cmd.setArgoutNum( 0 );
}

// ============================================================================
/// clears current figure
void Interpreter::clf( Command& cmd, Root& root )
{
	Figure* pFig = qobject_cast<Figure*>( root.objectByHandle( root.currentFigure() ) );
	
	if ( pFig )
	{
		pFig->clear(); // create existing figure
	}
	else
	{
		root.addFigure(); // or add a new one
	}
	
	cmd.setArgoutNum( 0 );
}

// ============================================================================
/// checks param is a handle. Returns 0 ar 1.
void Interpreter::ishnd( Command& cmd, Root& root )
{
	// check params
	if ( cmd.nargin() < 1 )
	{
		cmd.retError("ishnd expects argument.");
		return;
	}
	
	Handle h = Handle(cmd.arginAsMatrix(0).toScalar());
	
	cmd.setArgoutNum( 1 );
	
	cmd.addDoubleArgout( 0, root.objectByHandle( h ) != NULL );
}

// ============================================================================
/// Creates image object
void Interpreter::image( Command& cmd, Root& root )
{
	// check params
	if ( cmd.nargin() < 1 )
	{
		cmd.retError("image expects argument.");
		return;
	}
	
		
	Handle h = root.createObject( "image" );
	Object* pImage = root.objectByHandle( h ); 
	
	if ( ! pImage )
	{
		cmd.retError( "Couldn't create image");
		return;
	}
	
	cmd.setArgoutNum( 1 );
	
	// 3 param version?
	if ( cmd.nargin() >= 3 )
	{
		// create RGB image
		Matrix r = cmd.arginAsMatrix( 0 );
		Matrix g = cmd.arginAsMatrix( 1 );
		Matrix b = cmd.arginAsMatrix( 2 );
		
		pImage->setProperty( "Mode", "rgb" );
		pImage->setProperty( "CDataR", qVariantFromValue<Matrix>( r ) );
		pImage->setProperty( "CDataG", qVariantFromValue<Matrix>( g ) );
		pImage->setProperty( "CDataB", qVariantFromValue<Matrix>( b ) );
		
	}
	else
	{
		// Create colormap image
		Matrix cdata = cmd.arginAsMatrix( 0 );
		pImage->setProperty( "Mode", "colormap" );
		pImage->setProperty( "CData", qVariantFromValue<Matrix>( cdata ) );
	}
	
	cmd.addDoubleArgout( 0, h );

}

// ============================================================================
/// Prints current figure. Paramd: file name, device, resolution, bitmap size.
void Interpreter::print( Command& cmd, Root& root )
{
	// check params
	if ( cmd.nargin() < 4 )
	{
		cmd.retError("print expects 4 arguments.");
		return;
	}
	
	// parse params
	
	//  - file name
	QString fileName = cmd.arginAsString( 0 );
	if ( fileName.isEmpty() )
	{
		cmd.retError("print: file name can not be empty.");
		return;
	}
	
	// - device 
	Enum device;
	device.addValue( Figure::Ps, "ps" );
	device.addValue( Figure::Ps, "ps2" );
	device.addValue( Figure::Ps, "psc" );
	device.addValue( Figure::Ps, "psc2" );
	device.addValue( Figure::Eps, "eps" );
	device.addValue( Figure::Eps, "eps2" );
	device.addValue( Figure::Eps, "epsc" );
	device.addValue( Figure::Eps, "epsc2" );
	device.addValue( Figure::Pdf, "pdf" );
	device.addValue( Figure::Png, "png" );
	device.addValue( Figure::Jpeg, "jpg" );
	device.addValue( Figure::Svg, "svg" );
	
	device = cmd.arginAsString( 1 ); // thios will throw exception if wrong format string used

	// - resolution
	bool ok;
	int resolution = cmd.arginAsString( 2 ).toInt( &ok );
	if ( !ok || resolution < 0 )
	{
		cmd.retError( "print: resultion must be non-negative integer" );
		return;
	}
	
	// - size
	QSize size;
	QString sizeStr = cmd.arginAsString( 3 );
	if ( ! sizeStr.isEmpty() )
	{
		QRegExp rx( "(\\d+)x(\\d+)", Qt::CaseInsensitive );
		
		if ( ! rx.exactMatch( sizeStr ) )
		{
			cmd.retError( "print: size has to be in following form: WIDTHxHEIGHT." );
		}
		
		size.setWidth( rx.cap( 1 ).toInt() );
		size.setHeight( rx.cap( 2 ).toInt() );
		
	}
	
	// get current figure
	Figure* pFigure =  qobject_cast<Figure*>( root.objectByHandle( root.currentFigure() ) );

	if ( pFigure )
	{
		pFigure->print( fileName, device, resolution, size );
		cmd.setArgoutNum( 0 ); // happy end
	}
	else
	{
		cmd.retError( "print: no figure to print." );
	}

}

// ============================================================================
// Creates patch on current axes. Params: xdata, ydata
void Interpreter::patch( Command& cmd, Root& root )
{
	// check params
	if ( cmd.nargin() < 2 )
	{
		cmd.retError( "Patch expects 2 argments." );
		return;
	}
	if( cmd.argin(0).userType() != qMetaTypeId<Matrix>() || cmd.argin(1).userType() != qMetaTypeId<Matrix>() )
	{
		cmd.retError("Patch: arguments should be matrices.");
		return;
	}
	
	// get data
	Matrix xdata = cmd.arginAsMatrix( 0 );
	Matrix ydata = cmd.arginAsMatrix( 1 );
	
	// create object
	root.makeSureAxesCreated();
	Handle h = root.createObject( "patch" );
	
	Object* pObject = root.objectByHandle( h );
	
	if ( pObject )
	{
		pObject->setProperty( "XData", qVariantFromValue<Matrix>( xdata ) );
		pObject->setProperty( "YData", qVariantFromValue<Matrix>( ydata ) );
		
		cmd.setArgoutNum( 1 );
		cmd.addDoubleArgout( 0, h );
	}
	else
	{
		cmd.retError( "Can't create patch object." );
	}
	
}

// EOF


