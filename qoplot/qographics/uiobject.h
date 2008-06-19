// uiobject.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSUIOBJECT_H
#define QOGRAPHICSUIOBJECT_H

#include "object.h"

class QGraphicsScene;

namespace QOGraphics
{

/**
Comman base class for all graphics object added to figure.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/

class UIObject : public Object
{
Q_OBJECT
	
	Q_PROPERTY( QVariant Color READ getColor WRITE setColor );
	//Q_PROPERTY( Matrix FontSize READ getFontSize WRITE setFontSize );
	//Q_PROPERTY( QString GridLineStyle READ getGridLineStyle WRITE setGridLineStyle );
	//Q_PROPERTY( Matrix LineWidth READ getLineWidth WRITE setLineWidth );

public:
	UIObject ( Root* root, Handle handle, QObject* parent );
	virtual ~UIObject();

	// UI operations
	
	/// Sets scene on which UI item will be painted
	virtual void setScene( QGraphicsScene*) {}
	
	// properties
	
	virtual QVariant getColor() const { return QVariant(); }
	virtual void setColor( const QVariant& ){}

};

}

#endif // QOGRAPHICSUIOBJECT_H

// EOF


