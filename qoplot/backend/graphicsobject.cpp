// graphicsobject.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#include <QBrush>
#include <QPaintDevice>
#include <QString>

#include "converters.h"
#include "exceptions.h"

#include "graphicsobject.h"

namespace QOGraphics
{

// ============================================================================
// Constructor
GraphicsObject::GraphicsObject( double handle )
{
	_handle = handle;
}

// ============================================================================
// Destructor
GraphicsObject::~GraphicsObject()
{
	// nope
}

// ============================================================================
/// Returns pen created form provided color and LineWidth and LineStyle properties.
/// If any of these proeprties is missing, uses defaults: 0.p pt and solid line.
QPen GraphicsObject::pen( const QColor& color, const QPaintDevice* pDevice  ) const
{
	base_properties* pProps = properties();
	
	double pointWidth = 0.5;
	Qt::PenStyle style = Qt::SolidLine;
	
	// check if required properties are present
	if ( pProps->has_property("LineWidth") )
	{
		octave_value v = pProps->get_property("LineWidth").get();
		pointWidth	= v.double_value();
	}
	if( pProps->has_property("LineStyle") )
	{
		style	= styleFromOctave( pProps->get_property("LineStyle").get().string_value() );
	}
	
	double width = qRound( qMin( 1.0, ptToPixel( pointWidth, pDevice ) ) );
	return QPen( QBrush(color), int(width), style );
}

// ============================================================================
/// Returns font created from FontName, FontAngle, FontSize and FontWeight properties.
QFont GraphicsObject::font() const
{
	base_properties* pProps = properties();
	QFont font;
	
	// name
	if ( pProps->has_property("FontName") )
	{
		font.setFamily( pProps->get_property("FontName").get().string_value().c_str() );
	}
	
	// size
	if ( pProps->has_property("FontSize") )
	{
		font.setPointSize( int( pProps->get_property("FontSize").get().double_value() ) );
	}
	
	// weight
	if ( pProps->has_property("FontWeight") )
	{
		font.setWeight( weightFromOctave( pProps->get_property("FontWeight").get().string_value() ) );
	}
	
	// style
	if ( pProps->has_property("FontAngle") )
	{
		font.setWeight( fontStyleFromOctave( pProps->get_property("FontAngle").get().string_value() ) );
	}
	
	return font;
}

// ============================================================================
/// Converts points to pixels. Uses mean of logical device's X/Y dpi.
double GraphicsObject::ptToPixel( double pt, const QPaintDevice* pDevice ) const
{
	Q_ASSERT( pDevice );
	
	// use mean of X/Y logical dpis
	double dpi = ( pDevice->logicalDpiX() + pDevice->logicalDpiY() ) / 2.0;
	
	return pt*dpi/72.0; // 'dpi' pixels in inch, 72 points in inch.
}

// ============================================================================
/// Creates item with provided property set. Item type is deduced from "type" property.
GraphicsObject* GraphicsObject::createItem( double, base_properties* )
{
	return NULL;
}

// ============================================================================
/// Message from octave: child object was created.
/// Visual object will be created using createItem().
GraphicsObject* GraphicsObject::childAdded( double h )
{
	gh_manager::autolock guard;
	
	// get props
	graphics_object go = gh_manager::get_object( h );
	base_properties& props = go.get_properties();
	
	// create
	GraphicsObject* pObject = createItem( h, &props );
	
	// add to list
	_children[ h ] = pObject;
	
	return pObject;
}

// ============================================================================
/// Message from outer world: child removed.
void GraphicsObject::childRemoved( double h )
{
	if ( _children.contains( h )  )
	{
		_children.remove( h );
	}
	else
	{
		qWarning("GraphicsObject::childRemoved: no such child: %g", h );
	}
}

// ============================================================================
/// Message from octave: property has changed.
void GraphicsObject::propertyChanged( const QString& /*name*/ )
{
	// nothing, reimplement
}

// ============================================================================
/// Returns object properties, extracted from associated grpahics_object.
///\warning Always call this with gh_manager locked!
base_properties* GraphicsObject::properties() const
{
	graphics_object go = gh_manager::get_object( _handle );
	if ( go )
	{
		return &go.get_properties();
	}
	else
	{
		throw Exception( QString("Object with handle %1 is invalid!").arg(_handle) );
	}
}

}
