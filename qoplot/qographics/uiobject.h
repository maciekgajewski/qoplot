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
#include "matrix.h"
#include "uiitem.h"

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
	Q_PROPERTY( QOGraphics::Matrix LineWidth READ getLineWidth WRITE setLineWidth );
	Q_PROPERTY( QString LineStyle READ getLineStyle WRITE setLineStyle );
	
	Q_PROPERTY( QOGraphics::Matrix FontSize READ getFontSize WRITE setFontSize );
	Q_PROPERTY( QString FontWeight READ getFontWeight WRITE setFontWeight );
	Q_PROPERTY( QString FontAngle READ getFontAngle WRITE setFontAngle );
	Q_PROPERTY( QString FontName READ getFontName WRITE setFontName );
	
	
	Q_PROPERTY( QString DisplayName READ getDisplayName WRITE setDisplayName ); // TODO plot objects only


public:
	UIObject ( Root* root, Handle handle, QObject* parent );
	virtual ~UIObject();

	// UI operations
	
	virtual UIItem* item() const = 0;			///< Returns pointer to graphics item
	
	/// Information: property has been changed.
	virtual void propertyChanged() { item()->propertyChanged();  }
	
	// properties
	
	QVariant getColor() const { return item()->color.toVariant(); }
	void setColor( const QVariant& c ){ item()->color.fromVariant( c ); propertyChanged(); }
	
	Matrix getLineWidth() const { return item()->lineWidth; }
	void setLineWidth( const Matrix& w ){ item()->lineWidth = w.toScalar(); propertyChanged(); }
	
	QString getLineStyle() const { return item()->lineStyle; }
	void setLineStyle( const QString& s ){ item()->lineStyle = s; propertyChanged(); }
	
	Matrix getFontSize() const { return item()->fontSize; }
	void setFontSize( const Matrix& s ){ item()->fontSize = s.toScalar(); propertyChanged(); }
	
	QString getFontWeight() const { return item()->fontWeight; }
	void setFontWeight( const QString& s ){ item()->fontWeight = s; propertyChanged(); }
	
	QString getFontAngle() const { return item()->fontAngle; }
	void setFontAngle( const QString& s ){ item()->fontAngle = s; propertyChanged(); }

	QString getFontName() const { return item()->fontName; }
	void setFontName( const QString& s ){ item()->fontName = s; propertyChanged(); }

	QString getDisplayName() const { return item()->displayName; }
	void setDisplayName( const QString& s ){ item()->displayName = s; propertyChanged(); }

protected:

	void addToParent();							///< Adds graphics item to parent
	virtual void initProperties();				///< Initializes properties	

};

}

#endif // QOGRAPHICSUIOBJECT_H

// EOF


