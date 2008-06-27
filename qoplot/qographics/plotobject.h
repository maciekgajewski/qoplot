// plotobject.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSPLOTOBJECT_H
#define QOGRAPHICSPLOTOBJECT_H

#include "uiobject.h"
#include "plotitem.h"

namespace QOGraphics
{

class Axes;

/**
Common base for objects whcih are plot elements position on axes.

	@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/

class PlotObject : public UIObject
{
	Q_OBJECT
	Q_PROPERTY( QOGraphics::Matrix Position READ getPosition WRITE setPosition );
	Q_PROPERTY( QString UsePlotCoordinates READ getUsePlotCoordinates WRITE setUsePlotCoordinates );
	Q_PROPERTY( QString Clipping READ getClipping WRITE setClipping );
	Q_PROPERTY( QString Annotation READ getAnnotation WRITE setAnnotation );
	
	///\brief Name displayed in legend.
	///
	/// This string is used by Legend to display object.
	Q_PROPERTY( QString DisplayName READ getDisplayName WRITE setDisplayName );


public:
	PlotObject( Root* root, Handle handle, QObject* parent );
	virtual ~PlotObject();

	
	Axes* axes() const { return _pAxes; }
	virtual void sizeChanged();  ///< Send message to axes that object sise haschanged
	
	// properties
	
	Matrix getPosition() const { return ((PlotItem*)item())->position; }
	void setPosition( const Matrix& m ) { ((PlotItem*)item())->geometryWillChange(); ((PlotItem*)item())->position = m; propertyChanged(); sizeChanged(); }
	
	virtual QString getUsePlotCoordinates() const { return ((PlotItem*)item())->usePlotCoordinates; }
	virtual void setUsePlotCoordinates( const QString& s ) { ((PlotItem*)item())->usePlotCoordinates = s; propertyChanged(); }

	QString getClipping() const { return ((PlotItem*)item())->clipping; }
	void setClipping( const QString& s ) { ((PlotItem*)item())->clipping = s; propertyChanged(); }

	QString getAnnotation() const { return ((PlotItem*)item())->annotation; }
	void setAnnotation( const QString& s );

	QString getDisplayName() const { return ((PlotItem*)item())->displayName; }
	void setDisplayName( const QString& s );

protected:

	virtual void initProperties();
	
private:

	Axes*	_pAxes;						//!< Parent axes

};

}

#endif // QOGRAPHICSPLOTOBJECT_H

// EOF


