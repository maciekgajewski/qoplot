// Copyright (C) 2003 Shai Ayal <shaiay@users.sourceforge.net>
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
// Qt port by Maciek Gajewski <maciej.gajewski0@gmail.com> 2008


#include <stdlib.h>
#include <QApplication>
#include "plotapp.h"

// ==============================================
// Debug output
void debug_output( QtMsgType, const char * msg)
{
	printf("%s\n", msg);
}


// ==============================================
// main
int main(int argc, char* argv[])
{
	if(argc<2) exit(1);
	
	qInstallMsgHandler( debug_output ); // put output string onto stdout
	
	PlotApp app( argc, argv );
	
	
	
	return app.exec();
}
