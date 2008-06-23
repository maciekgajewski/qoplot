// text.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSTEXT_H
#define QOGRAPHICSTEXT_H

#include "textitem.h"
#include "plotobject.h"

namespace QOGraphics
{

class Axes;

/**
Text object.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class Text : public PlotObject
{
	Q_OBJECT
	
	Q_PROPERTY( QOGraphics::Matrix Rotation READ getRotation WRITE setRotation );
	Q_PROPERTY( QOGraphics::Matrix Margin READ getMargin WRITE setMargin );
	Q_PROPERTY( QString String READ getString WRITE setString );
	Q_PROPERTY( QVariant EdgeColor READ getEdgeColor WRITE setEdgeColor );
	Q_PROPERTY( QVariant BackgroundColor READ getBackgroundColor WRITE setBackgroundColor );
	
	Q_PROPERTY( QString HorizontalAlignment READ getHorizontalAlignment WRITE setHorizontalAlignment );
	Q_PROPERTY( QString VerticalAlignment READ getVerticalAlignment WRITE setVerticalAlignment );
	

public:

	Text( Root* root, Handle handle, QObject* parent );
	~Text();
	
	virtual UIItem* item() const { return _pItem; }
	
	// property setters/getters
	
	virtual QString getType() const { return "text"; }
	
	Matrix getRotation() const { return _pItem->rotation; }
	void setRotation( const Matrix& m ) { _pItem->geometryWillChange(); _pItem->rotation = m.toScalar(); propertyChanged(); sizeChanged(); }

	Matrix getMargin() const { return _pItem->margin; }
	void setMargin( const Matrix& m ) { _pItem->geometryWillChange(); _pItem->margin = m.toScalar(); propertyChanged(); sizeChanged(); }

	QString getString() const { return _pItem->string; }
	void setString( const QString& s ) { _pItem->geometryWillChange(); _pItem->string = s; propertyChanged(); sizeChanged(); }
	
	QVariant getEdgeColor() const { return _pItem->edgeColor.toVariant(); }
	void setEdgeColor( const QVariant& v ) { _pItem->edgeColor.fromVariant(v); propertyChanged(); }

	QVariant getBackgroundColor() const { return _pItem->backgroundColor.toVariant(); }
	void setBackgroundColor( const QVariant& v ) { _pItem->backgroundColor.fromVariant(v); propertyChanged(); }
	
	QString getHorizontalAlignment() const { return _pItem->horizontalAlignment; }
	void setHorizontalAlignment( const QString& s ) { _pItem->geometryWillChange(); _pItem->horizontalAlignment = s; propertyChanged(); sizeChanged(); }

	QString getVerticalAlignment() const { return _pItem->verticalAlignment; }
	void setVerticalAlignment( const QString& s ) { _pItem->geometryWillChange(); _pItem->verticalAlignment = s; propertyChanged(); sizeChanged(); }

protected:

	virtual void initProperties();			//!< Initializes properties
	
private:

	TextItem*	_pItem;						//!< Text item itself

};

}

#endif // QOGRAPHICSTEXT_H

// EOF


