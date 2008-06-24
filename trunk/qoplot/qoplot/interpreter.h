// interpreter.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef INTERPRETER_H
#define INTERPRETER_H


using namespace QOGraphics;
class QOGraphics::Root;
class Command;

/**
Command interpreter. Intepretes command and perrforms appropriate action on graphics
objects.

Use interpret() method.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class Interpreter
{
public:
	Interpreter();
	~Interpreter();
	
	void interpret( Command& cmd, Root& root );
	
private:

	// specific commands interpretation
	
	void get( Command& cmd, Root& root );
	void set( Command& cmd, Root& root );
	void figure( Command& cmd, Root& root );
	void axes( Command& cmd, Root& root );
	void text( Command& cmd, Root& root );
	void line( Command& cmd, Root& root );
	void cla( Command& cmd, Root& root );
	void clf( Command& cmd, Root& root );
	void del( Command& cmd, Root& root );
	void redraw( Command& cmd, Root& root );
	void ishnd( Command& cmd, Root& root );
	void image( Command& cmd, Root& root );

};

#endif // INTERPRETER_H

// EOF


