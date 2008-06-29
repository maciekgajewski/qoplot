// patch.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSPATCH_H
#define QOGRAPHICSPATCH_H

#include "plotobject.h"
#include "patchitem.h"

namespace QOGraphics
{

/**
The Patch object.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/

class Patch : public PlotObject
{
	Q_OBJECT
	
	///\brief X-coordinates of patch vertices.
	///
	/// Matrix, each column represents coorindates of single face.
	Q_PROPERTY( QOGraphics::Matrix XData READ getXData WRITE setXData )
	
	///\brief Y-coordinates of patch vertices.
	///
	/// Matrix, each column represents coorindates of single face.
	Q_PROPERTY( QOGraphics::Matrix YData READ getYData WRITE setYData )
	
	///\brief Color used to fill patch faces.
	///
	/// Can be color name, 3-eelemt nor 4-element vector.
	Q_PROPERTY( QVariant FaceColor READ getFaceColor WRITE setFaceColor )
	
	///\brief Color used to draw patch edges.
	///
	/// Can be color name, 3-eelemt nor 4-element vector.
	Q_PROPERTY( QVariant EdgeColor READ getEdgeColor WRITE setEdgeColor )

public:
	Patch( Root* root, Handle handle, QObject* parent );
	virtual ~Patch();
	
	virtual PatchItem* item() const { return _pItem; }
	
	// properties
	
	virtual QString getType() const { return "patch"; }
	
	Matrix getXData() const { return _pItem->xdata; }
	void setXData( const Matrix& m) { _pItem->geometryWillChange(); _pItem->xdata = m; propertyChanged(); }

	Matrix getYData() const { return _pItem->ydata; }
	void setYData( const Matrix& m) { _pItem->geometryWillChange(); _pItem->ydata = m; propertyChanged(); }

	QVariant getEdgeColor() const { return _pItem->edgeColor.toVariant(); }
	void setEdgeColor( const QVariant& v ) { _pItem->edgeColor.fromVariant(v); propertyChanged(); }

	QVariant getFaceColor() const { return _pItem->faceColor.toVariant(); }
	void setFaceColor( const QVariant& v ) { _pItem->faceColor.fromVariant(v); propertyChanged(); }

protected:

	virtual void initProperties();				///< Initializes properties
private:

	PatchItem* _pItem;
};

}

#endif // QOGRAPHICSPATCH_H

// EOF


