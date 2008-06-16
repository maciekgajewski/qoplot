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
#include "mainwindow.h"


/// Constructor
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
	
	// create main window
	_pMainWindow = new MainWindow();
}

/// Destructor
PlotApp::~PlotApp()
{
	// nope
}

/// Slot called when comm socket is readable (incoming command)
void PlotApp::socketReadable( int fd )
{
	// use ocpl::command to handle request
	Command command(fd);
	
	qDebug("PlotApp::socketReadable: command id: %d", command.id() );
	
	// TODO temporary quick'n'dirty command handling
	switch( command.id() )
	{
		// Get
		case ocpl::get:
		{
			qDebug("PlotApp::socketReadable: get");
			
			if( command.nargin() < 1 || command.nargin() > 2 ) {
				command.retError("Get: accepts 1 or 2 args");
			}
			else if( command.argin(0).type() != QVariant::Double ) {
				command.retError("Get: first arg should be handle");
			}
			else if(command.nargin() > 1 && command.argin(1).type() != QVariant::String ) {
				command.retError("Get: second arg should be property name");
			}
			else {
				// actual get goes here
				//double* hnd = new double(static_cast<double>( 0 /* TODO prop value */ ));
				//command.argout(0,ocpl::real,1,1,reinterpret_cast<char*>(hnd),true);
				command.addDoubleArgout( 0, 1, 1, 0.0 );
			}
			break;
		}
		
		// Set
		case ocpl::set:
		{
			if(command.nargin()!=3) {
				command.retError("Set: accepts 3");
			}
			else if( command.argin(0).type() != QVariant::Double ) {
				command.retError("Set: first arg should be handle");
			}
			else if( command.argin(1).type() != QVariant::String ) {
				command.retError("Set: second arg should be property name");
			}
			else {
				qDebug("PlotApp::socketReadable: set, handle: %d, property: %s",
					command.argin(0).toInt(), qPrintable( command.argin(1).toString() ) );
			
				// TODO actual set here
				command.accept();
			}
		
			break;
		}
		
		
		// Axes
		case ocpl::axes:
		{
			qDebug("PlotApp::socketReadable: axes");
			
			//return handle
			// TODO this is nightmare! add method for easy arg passing
			//double* hnd = new double(static_cast<double>( 0 /* TODO axes handle here */ ));
			//command.argout(0,ocpl::real,1,1,reinterpret_cast<char*>(hnd),true);
			command.addDoubleArgout( 0, 1, 1, 0.0 );
			break;
		}
			
		default:
			; // nope
	}
	
	if( ! command.parsed() )
	{
		command.retError("Unknown command");
	}
	command.ret( fd );
}

// EOF

