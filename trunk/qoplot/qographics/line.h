// line.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSLINE_H
#define QOGRAPHICSLINE_H

#include "plotobject.h"
#include "lineitem.h"

namespace QOGraphics
{

/**
Line

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/

class Line : public PlotObject
{
	Q_OBJECT
	Q_PROPERTY( QString Marker READ getMarker WRITE setMarker )
	Q_PROPERTY( QVariant MarkerEdgeColor READ getMarkerEdgeColor WRITE setMarkerEdgeColor )
	Q_PROPERTY( QVariant MarkerFaceColor READ getMarkerFaceColor WRITE setMarkerFaceColor )
	Q_PROPERTY( QOGraphics::Matrix MarkerSize READ getMarkerSize WRITE setMarkerSize )
	Q_PROPERTY( QOGraphics::Matrix XData READ getXData WRITE setXData )
	Q_PROPERTY( QOGraphics::Matrix YData READ getYData WRITE setYData )

public:
	
	Line( Root* root, Handle handle, QObject* parent );
	virtual ~Line();
		
	virtual UIItem* item() const{ return _pItem; }
	void dataChanged(); 				///< lets axes know that data has changed.

	
	// property access
	
	virtual QString getType() const { return "line";}
	
	virtual void setUsePlotCoordinates( const QString& ) { /*not changeable*/ }
	
	QString getMarker() const { return _pItem->marker; }
	void setMarker( const QString& s ) { _pItem->marker = s; propertyChanged(); }
	
	QVariant getMarkerEdgeColor() const { return _pItem->markerEdgeColor.toVariant(); }
	void setMarkerEdgeColor( const QVariant& v ) { _pItem->markerEdgeColor.fromVariant(v); propertyChanged(); }
	
	QVariant getMarkerFaceColor() const { return _pItem->markerEdgeColor.toVariant(); }
	void setMarkerFaceColor( const QVariant& v ) { _pItem->markerEdgeColor.fromVariant(v); propertyChanged(); }

	Matrix getMarkerSize() const { return _pItem->markerSize; }
	void setMarkerSize( const Matrix& m ) { _pItem->geometryWillChange(); _pItem->markerSize = m.toScalar(); sizeChanged(); }

	Matrix getXData() const { return _pItem->xdata; }
	void setXData( const Matrix& m ) { _pItem->geometryWillChange(); _pItem->xdata = m; dataChanged(); sizeChanged(); }

	Matrix getYData() const { return _pItem->ydata; }
	void setYData( const Matrix& m ) { _pItem->geometryWillChange(); _pItem->ydata = m; dataChanged(); sizeChanged(); }

protected:

	virtual void initProperties();

private:

	LineItem* _pItem;

};

} // namespace

#endif // QOGRAPHICSLINE_H

// EOF


