// object.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef OBJECT_H
#define OBJECT_H


#include <QObject>
#include <QVariant>

#include "matrix.h"
#include "enum.h"

namespace QOGraphics
{

typedef int Handle;				//!< Handle type

class Root;

/**
Common base for all graphics objects.
It uses Qt property system to facilitation object properties.
Qt properties marked as scriptable are exposed.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class Object : public QObject
{
	Q_OBJECT
	
	// Exposded properties
	
	Q_PROPERTY( QVariant Parent	READ getParent )
	Q_PROPERTY( QString Type	READ getType )
	
	Q_PROPERTY( QOGraphics::Matrix UserData	READ getUserData	WRITE setUserData )
	Q_PROPERTY( QString Visible	READ getVisible		WRITE setVisible )
	Q_PROPERTY( QString Selected READ getSelected WRITE setSelected )
	Q_PROPERTY( QString Tag READ getTag WRITE setTag )
	Q_PROPERTY( QOGraphics::Matrix Children READ getChildren )
	
public:

	// Types
	
	enum PredefinedHandles			//! Predefined handle values
	{
		InvalidHandle	= -1,		//!< Invalid handle
		RootHandle		= 0			//!< Handle of root object
	};

	// Createtion/destruction
	
	Object( Root* root, Handle handle, QObject* parent = 0 );
	virtual ~Object();
	
	
	// Basic info
	Handle handle() const { return _handle; }
	void setHandle( Handle h );
	Root* root() const { return _pRoot; }
	
	// Property access / querying
	
	QStringList properties() const;
	void setProperty( const QString& name, const QVariant& value );
	QVariant getProperty( const QString& name );
	
	// Properties getters / setters
	
	QVariant getParent() const;				//!< Returns parent handle, or empty if none
	virtual QString getType() const = 0;	//!< Returns type name
	
	Matrix getUserData() const { return _userData; }
	void setUserData( const Matrix& data ) { _userData = data; }
	
	virtual QString getVisible() const { return _visible; }
	virtual void setVisible( const QString& str ) { _visible = str; }
	Enum visible() const { return _visible; }
	
	virtual QString getSelected() const { return "off"; }
	virtual void setSelected( const QString& ) {}
	
	QString getTag() const { return _tag; }
	void setTag( const QString& tag ) { _tag = tag; }
	
	Matrix getChildren() const;
	
private:

	void prepareCaseMap();			//!< Prepares case map

	// Data
	
	Root* 	_pRoot;					//!< Root object
	Handle	_handle;				//!< Object handle
	
	Matrix		_userData;			//!< Associated user data
	QString			_tag;			//!< Associated tag
	
	Enum 		_visible;
	
	/// Mapping between lowercase proeprty naems and actual names
	QMap< QString, QString > _caseMap;

};

}; // namespace

#endif // OBJECT_H

// EOF


