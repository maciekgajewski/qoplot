// graphicsobject.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSGRAPHICSOBJECT_H
#define QOGRAPHICSGRAPHICSOBJECT_H


#include <octave/oct.h>
#include <octave/graphics.h>

#include <QFont>
#include <QPen>
#include <QMap>

#include "exceptions.h"

namespace QOGraphics
{

/**
	Common base class for all visual objects implementing rendering of Octave
	Graphics Object.
	This base class contains common facilities.
	There is another, shim-temnplate-class which associates graphics object
	with appropriate octave property class.
	@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class GraphicsObject
{
public:
	GraphicsObject( double handle );
	virtual ~GraphicsObject();

	/// Returns current properties.
	virtual base_properties* properties() const;
	
	/// Message from outer world - child added
	virtual GraphicsObject* childAdded( double h );
	
	/// Message from outer world: child removed
	virtual void childRemoved( double h );
	
	/// Message from outer world - property changed
	virtual void propertyChanged( const QString& name );
	
	/// Returns handle
	double handle() const { return _handle; }
	
	/// Property class converter.
	template<class PropertiesPointer>
	PropertiesPointer properties_cast( base_properties* pBase ) const;
	
	/// Returns list of object's children.
	QList<GraphicsObject*> children() const { return _children.values(); }
	
	/// Returns child identified by handle, or NULL if none.
	GraphicsObject* child( double h ) const { return _children[h]; }
	
protected:

	/// Pen created from properties
	QPen	pen( const QColor& color, const QPaintDevice* pDevice   ) const;
	QFont	font() const;						///< Font created from properties
	
	/// Converts points to pixels
	double ptToPixel( double pt, const QPaintDevice* device ) const;
	
	virtual void propertiesChanged(){};		///< Updates item after properties change
	
	/// Creates item with provided property set.
	virtual GraphicsObject* createItem( double h, base_properties* pProps );
	
	
private:
	
	QMap< double, GraphicsObject* > _children;	///< Child elements
	double				_handle;				///< Item's handle
	

};

// ============================================================================
/// Casts bse properties pointer to one of descendand classes, throwing exception
/// if conversion fails.
template<class PropertiesPointer>
PropertiesPointer GraphicsObject::properties_cast( base_properties* pBaseProps ) const
{
	PropertiesPointer pProps = dynamic_cast<PropertiesPointer>( pBaseProps );
	if ( pProps )
	{
		return pProps;
	}
	else
	{
		throw Exception(
			QString("Ivalid property type: for h=%1: %2")
				.arg( handle() ).arg( pBaseProps->get_type().c_str() )
				);
	}
}


}

#endif // QOGRAPHICSGRAPHICSOBJECT_H

// EOF


