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

// ============================================================================
// Constructor
Interpreter::Interpreter()
{
}

// ============================================================================
// Destructor
Interpreter::~Interpreter()
{
}

// ============================================================================
/// Main command interpreter interface. Interprets command, performs action on graphics objects,
/// feeds command back with return values
void Interpreter::interpret( Command& cmd, Root& root )
{
	qDebug("interpeter command id: %d", cmd.id() );
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
		
		
		// Axes
		case ocpl::axes:
		{
			//return handle
			cmd.addDoubleArgout( 0, 0.0 );
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
	else if( cmd.argin(0).type() != QVariant::Double )
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
	Object::Handle h = cmd.argin(0).toInt();
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
	else if( cmd.argin(0).type() != QVariant::Double )
	{
		cmd.retError("Set: first arg should be handle");
	}
	else if( cmd.argin(1).type() != QVariant::String )
	{
		cmd.retError("Set: second arg should be property name");
	}
	else
	{
		// check if object exists
		Object::Handle h = cmd.argin(0).toInt();
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

// EOF


