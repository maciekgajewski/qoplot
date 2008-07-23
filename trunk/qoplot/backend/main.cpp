#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include <QApplication>
#include <QMutex>
#include <QWaitCondition>

#include "octave/oct.h"
#include "octave/graphics.h"

#include "backend.h"
#include "figuremanager.h"
#include "systeminfo.h"

// Statics
static bool backend_registered = false;
static pthread_t tid;	// thread id of GUI thread
static QWaitCondition guiThreadCreated;
static QOGraphics::FigureManager* pFigureManager = NULL;

// ---------------------------------------------------------------------------
/// GUI thread routine.
/// Creates Qt application object and starts it's event loop.
static void* threadRoutine( void* )
{
	// emulate main, create application
	int argc = 1;
	const char* argv[] = { "octave" };
	QApplication app( argc, const_cast<char**>( argv ) );
	app.setQuitOnLastWindowClosed( false );
	
	// Create figure manager
	QOGraphics::FigureManager manager;
	pFigureManager = &manager;
	
	// no need to hurry, we are in synchornized thread, so let's acquire some system info
	QOGraphics::SystemInfo::acquireInfo();
	
	// announce that thread was completely created.
	guiThreadCreated.wakeAll();
	
	int res = app.exec();
	
	qDebug("oplot exits with code %d", res);
	
	return NULL;
}


// ---------------------------------------------------------------------------
/// Starts gui thread.
static void startGuiThread()
{
	QMutex mutex;
	mutex.lock();
	pthread_create( &tid, NULL, threadRoutine, NULL );
	
	// wait for thread to complete creation
	guiThreadCreated.wait( &mutex );
	
	mutex.unlock();
}

// ---------------------------------------------------------------------------
/// Function exported to octave Initializes backend.
DEFUN_DLD (qobackend, , , "")
{
	if ( ! backend_registered )
	{
		startGuiThread();
		graphics_backend::register_backend (new QOGraphics::Backend( pFigureManager ) );
		// set this backend as default
		graphics_object root = gh_manager::get_object( 0 );
		root.set( "DefaultFigure__backend__", "qoplot" );
		
		backend_registered = true;
	}
	
	octave_value retval;
	return retval;
}

// EOF
