// plotapp.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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


#include <QSocketNotifier>
#include "plotapp.h"
#include "command.h"
#include "interpreter.h"


// ============================================================================
// Constructor
PlotApp::PlotApp( int& argc, char** argv ): QApplication( argc, argv )
{
	// obtain file descriptor
	#ifndef HAVE_WINSOCK2_H
	int fd = atoi(argv[1]);
	#else
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);
	
	int port = atoi(argv[1]);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sock_in;
	
	sock_in.sin_family = AF_INET;
	sock_in.sin_port = port;
	sock_in.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	
	if (::connect(sock, (struct sockaddr*)&sock_in, sizeof(sock_in)) < 0)
	{
		fprintf(stderr, "Could not connect to server: %08x\n", WSAGetLastError());
		closesocket(sock);
		exit (1);
	}
	
	int fd = sock;
	#endif

	// intialize command listener
	QSocketNotifier* pNotifier = new QSocketNotifier( fd, QSocketNotifier::Read, this );
	connect( pNotifier, SIGNAL(activated( int ) ), SLOT( socketReadable(int) ) );
	
}

// ============================================================================
// Destructor
PlotApp::~PlotApp()
{
	// nope
}

// ============================================================================
/// Slot called when comm socket is readable (incoming command)
void PlotApp::socketReadable( int fd )
{
	// use ocpl::command to handle request
	Command command(fd);
	
	Interpreter i;
	i.interpret( command, _root );
	
}

// EOF

