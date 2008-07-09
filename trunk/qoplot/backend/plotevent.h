// plotevent.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSPLOTEVENT_H
#define QOGRAPHICSPLOTEVENT_H

#include <QEvent>
#include <QString>

#include <octave/oct.h>
#include <octave/graphics.h>

namespace QOGraphics {

/**
Event used to communicate between octave's main thread and Qt GUI thread.
This event is send when backend's 'object_created', 'object_destroyed'or 'property_changed' methods
are called. It holds figures handle and requested action type.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class PlotEvent : public QEvent
{
public:
	
	enum ActionType { Created, Destroyed, PropertyChanged };
	
	PlotEvent();
	virtual ~PlotEvent();
	
	
	ActionType	action;		///< Requested action
	double		handle;		///< Object in question
	QString		name;		///< Property name
	
};

}

#endif // QOGRAPHICSPLOTEVENT_H

// EOF


