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
	// emulate main
	int argc = 1;
	char* argv[] = { "octave" };
	QApplication app( argc, argv );
	app.setQuitOnLastWindowClosed( false );
	
	QOGraphics::FigureManager manager;
	pFigureManager = &manager;
	
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
		backend_registered = true;
	}
	
	octave_value retval;
	return retval;
}

// EOF
