// legend.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSLEGEND_H
#define QOGRAPHICSLEGEND_H

#include "plotobject.h"
#include "legenditem.h"

namespace QOGraphics {

/**
	@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class Legend : public PlotObject
{
Q_OBJECT

	///\brief Legend position within axes.
	///\par Possible values
	/// North | West | East | South | {NorthEast} | NorthWest | SouthEast | SouthWest
	Q_PROPERTY( QString Position READ getPosition WRITE setPosition )
	
	///\brief Controls painting box around the legend.
	///
	/// Box is painted using EdgeColor, LineWidth and LineStyle properties.
	///\par Possible values
	/// {on} | off
	Q_PROPERTY( QString Box READ getBox WRITE setBox )
	
	///\brief Frame edge color.
	///
	/// Color used to draw box around legend. 
	Q_PROPERTY( QVariant EdgeColor READ getEdgeColor WRITE setEdgeColor )

public:
	
	// construction / destruction
	
	Legend( Root* root, Handle handle, QObject* parent );
	virtual ~Legend();
	
	void updateLegend();	///< Updates list of objects displayed in legend
	
	virtual PlotItem* item() const { return _pItem; }
	
	// properties
	
	virtual QString getType() const { return "legend"; }
	
	QString getBox() const { return _pItem->box; }
	void setBox( const QString& s ) { _pItem->box = s; propertyChanged(); }
	
	QString getPosition() const { return _pItem->position; }
	void setPosition( const QString& s ) { _pItem->position = s; propertyChanged(); }

	QVariant getEdgeColor() const { return _pItem->edgeColor.toVariant(); }
	void setEdgeColor( const QVariant& v ) { _pItem->edgeColor.fromVariant(v); propertyChanged(); }

protected:

	virtual void initProperties();

private:

	LegendItem* _pItem;			///< Associated item
};

}

#endif // QOGRAPHICSLEGEND_H

// EOF


