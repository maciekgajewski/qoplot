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

#include "command.h"
#include "root.h"
#include "interpreter.h"
#include "exceptions.h"

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
	qDebug("interpeter command id: %d", cmd.id() );
	
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
		qDebug("getting property %s", qPrintable( propName ) );
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
		qDebug("set: handle = %d", h );
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
		cmd.retError("Text: first nd second arg should be matrix");
		return;
	}
	
	if( cmd.argin(1).userType() != QVariant::String )
	{
		cmd.retError("Text: second argument should be string");
	}
	
	Matrix position = cmd.arginAsMatrix( 0 );
	QString string = cmd.arginAsString( 1 );
	
	// get current axes
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

// EOF


