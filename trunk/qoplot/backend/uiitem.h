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

#include <octave/oct.h>
#include <octave/graphics.h>

namespace QOGraphics
{

/**
Common QGraphicsItem for all UI items.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/

class UIItem : public QGraphicsItem
{

public:
	UIItem( QGraphicsItem* parent = NULL );
	virtual ~UIItem();
	
	/// Copies supplied properties to internal storage.
	/// Is pure virtual, becouse it need to know the exact type of properties.
	/// Should call propertiesChanged() before returning.
	virtual void copyProperties( const base_properties* pProps ) = 0;
	
	/// Returns current properties
	virtual const base_properties* properties() const { return _pProperties; }
	
	/* TODO relic from previous life, replaced with octave's  base_properties
	Color	color;			///< Color used
	Enum	clipping;		///< CLipping to parent On|Off
	Enum	lineStyle;		///< Line style (uses Qt:PenStyle)
	double	lineWidth;		///< Line width
	double	fontSize;		///< Font size [pt] TODO add other units support
	QString fontName;		///< Font name
	Enum	fontWeight;		///< Font weight
	Enum	fontAngle;		///< Font angle
	*/
	
protected:

	/// Pen created from properties
	QPen	pen( const QColor& color, const QPaintDevice* pDevice   ) const;
	QFont	font() const;						///< Font created from properties
	
	/// Converts points to pixels
	double ptToPixel( double pt, const QPaintDevice* device ) const;
	
	virtual void propertiesChanged();		///< Updates item after properties change
	
	base_properties* _pProperties;
};

}

#endif // QOGRAPHICSUIITEM_H

// EOF


