// figuremanager.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSFIGUREMANAGER_H
#define QOGRAPHICSFIGUREMANAGER_H

#include <QObject>
#include <QMap>
#include <QMutex>
#include <QWaitCondition>

#include <octave/oct.h>
#include <octave/graphics.h>


namespace QOGraphics
{

class FigureWindow;
class UIItem;

/**
Figure manager. Lives in GUI thread, receives plot events from backend (in octave thread).
Manages figure creation, destruction and redrawing.

This object is also enpoint in inter-thread communication with main octave thread.
It receives events from backend, and sycnhronizes property copying.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/

class FigureManager : public QObject
{
	Q_OBJECT

public:
	FigureManager ( QObject *parent = 0 );
	~FigureManager();

	/// Handles incoming events
	virtual bool event ( QEvent* pEvent );
	
	// synchronization facilities
	QMutex propertiesMutex;            ///< Mutex used to guard figure properties while they are being copied
	QWaitCondition propertiesCopied;   ///< Signalizes end of copy operation
	
private:

	void propertyChanged( double h, const QString& name );
	void objectCreated( double h );
	void objectDestroyed( double h );
	
	// data
	// TODO o hsave this gut feeleing that having common base class for figures and items
	// would be a good thing. But I have also a second gut feeling that using multiple ingeritance
	// would be paint in the ass.
	QMap< double, FigureWindow* > _figures;	///< Figures database
	QMap< double, UIItem* > _items;			///< Items database
};

}

#endif // QOGRAPHICSFIGUREMANAGER_H

// EOF


