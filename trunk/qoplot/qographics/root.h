// root.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef ROOT_H
#define ROOT_H

#include "object.h"
#include "matrix.h"

namespace QOGraphics
{

/**
The Root object. It is created at startup, always exists, maintains handle<->object
associations.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class Root : public Object
{
	Q_OBJECT
	
	// Exposed properties
	//Q_PROPERTY( QVariant CallbackObject READ getCallbackObject )
	Q_PROPERTY( QVariant CurrentFigure READ getCurrentFigure )
	Q_PROPERTY( Matrix PointerLocation READ getPointerLocation )
	Q_PROPERTY( Handle PointerWindow READ getPointerWindow )
	Q_PROPERTY( double ScreenDepth READ getScreenDepth )
	//Q_PROPERTY( Matrix ScreenSize READ getScreenSize )
	Q_PROPERTY( double ScreenPixelsPerInch READ getScreenPixelsPerInch )
	
public:
	
	// Construction / destruction
	
	Root( QObject* parent = 0 );
	virtual ~Root();
	
	// Objects
	Object* objectByHandle( Handle h );
	const Object* objectByHandle( Handle h ) const { return _objects.value( h, NULL ); }
	
	// figures
	
	/// Creates new figure
	Handle addFigure( Handle desiredHandle = InvalidHandle );
	
	
	/// Sets current figure
	void setCurrentFigure( Handle h );
	
	/// Returns handle to current figure
	Handle currentFigure() const { return _currentFigure; }
	
	/// Makes sure axes are created
	void makeSureAxesCreated();
	
	/// Returns handle to current axes
	Handle currentAxes() const;
	
	// Adding/creating object
	
	/// Creates object of givent type
	Handle createObject( const QString& type, Handle parent =  InvalidHandle );
	
	/// Adds already created object to tree
	Handle addObject( Object* pObject );
	
	// Properties getters/setters
	
	QVariant getCallbackObject() const { return QVariant(); }
	QVariant getCurrentFigure() const;
	Matrix getPointerLocation() const;
	Handle getPointerWindow() const;
	double getScreenDepth() const;
	Matrix getScreenSize() const;
	double getScreenPixelsPerInch() const;
	
	QString getType() const { return "root"; }
	
public slots:
	
	// Child object management
	
	void objectDestroyed( Handle handle );		///< Hanldes child object destruction (removes from list)

private:

	// Data

	QMap< Handle, Object* > _objects;			///< Main object<->handle database
	
	Handle	_currentFigure;						///< Current figure
	Handle	_firstFreeHandle;					///< First free handle, used to handle allocation
	
	static bool _graphicsInitialized;			///< Flag used to intilaize graphics
	bool	_beingDeleted;						///< Flag - is deleted already

};


}; // namespace

#endif // ROOT_H

// EOF


