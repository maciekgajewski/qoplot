// command.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef COMMAND_H
#define COMMAND_H

#include <QVariant>
#include "op_com.h"

/**
	@author Maciek Gajewski <maciej.gajewski0@gmail.com>
	Qt wrapper around command object
*/
class Command
{
public:
	Command( int fd );
	~Command();
	
	// type query
	
	/// Command id (type)
	int id() const { return int( _command.id() ); }
	/// Number of input arguments
	int nargin() const { return _command.nargin(); }
	/// Number of output arguments
	int nargout() const { return _command.nargout(); }
	
	/// Returns input argin identified by number
	QVariant argin( int i ) const;
	
	// state query
	bool parsed() const { return _command.parsed(); }
	
	// return values
	
	/// Accept command without parameters
	void accept() { _command.init_argout(0); }
	
	/// Add double output param, accept command
	void addDoubleArgout( int index, long row, long col, double value );

	/// Add string output param, accept command
	void addStringArgout( int index, long row, long col, const QString& value );
	
	/// Returns result to Octave
	void ret( int fd ) { _command.ret( fd ); }

	/// Returns error
	void retError( const QString& msg );
	
	/// Returns warning 
	void retWarning( const QString& msg );

private:

	ocpl::command _command;
};

#endif // COMMAND_H

// EOF


