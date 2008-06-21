// uiitem.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSUIITEM_H
#define QOGRAPHICSUIITEM_H

#include <QGraphicsItem>
#include <QPen>
#include <QFont>

#include "color.h"
#include "enum.h"

namespace QOGraphics
{

/**
Common QGraphicsItem for all UI items. Contains fields holding most common properties,
and it's associated with UIObject, which set's it's properties.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/

class UIItem : public QGraphicsItem
{

public:
	UIItem( QGraphicsItem* parent = NULL );
	virtual ~UIItem();
	
	virtual void propertyChanged();		///< Updates item after proertty change
	void gometryWillChange();
	
	// enums used in proeprties
	enum AutoManual { Auto, Manual };
	enum Direction { Normal, Reverse };
	enum OnOff { On, Off };
	
	// property fields, stored here, set in UIObject. Used by descendand classes for drawing
	
	Color	color;			///< Color used
	Enum	clipping;		///< CLipping to parent On|Off
	QString	displayName;	///< Name used by legend
	Enum	lineStyle;		///< Line style (uses Qt:PenStyle)
	double	lineWidth;		///< Line width
	double	fontSize;		///< Font size [pt] TODO add other units support
	QString fontName;		///< Font name
	Enum	fontWeight;		///< Font weight
	Enum	fontAngle;		///< Font angle
	
protected:

	QPen	pen( const QColor& color ) const;	///< Pen created from properties
	QFont	font() const;						///< Font created from properties
	
};

}

#endif // QOGRAPHICSUIITEM_H

// EOF


