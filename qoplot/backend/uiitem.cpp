// uiitem.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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

#include "uiitem.h"
#include "converters.h"

namespace QOGraphics
{

// ============================================================================
// Constructor
UIItem::UIItem( FigureWindow* figure, QGraphicsItem* parent ): QGraphicsItem( parent )
{
	_pFigure = figure;
}

// ============================================================================
// Destructor
UIItem::~UIItem()
{
	// nothing
}

// ============================================================================
/// Returns pen created form provided color and LineWidth and LineStyle properties.
/// If nay of these proeprties is missing, uses defaults: 0.p pt and solid line.
QPen UIItem::pen( const QColor& color, const QPaintDevice* pDevice  ) const
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
QFont UIItem::font() const
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
/// Updates item state to changed properties.
void UIItem::propertiesChanged()
{
	updateChildren();
}

// ============================================================================
/// Converts points to pixels. Uses mean of logical device's X/Y dpi.
double UIItem::ptToPixel( double pt, const QPaintDevice* pDevice ) const
{
	Q_ASSERT( pDevice );
	
	// use mean of X/Y logical dpis
	double dpi = ( pDevice->logicalDpiX() + pDevice->logicalDpiY() ) / 2.0;
	
	return pt*dpi/72.0; // 'dpi' pixels in inch, 72 points in inch.
}

// ============================================================================
/// UPdates children elements to new properties.
void UIItem::updateChildren()
{
	base_properties* pProps = properties();
	
	Matrix cm = pProps->get_children();
	
	int count = cm.nelem();
	QMap<double, UIItem*> newMap;
	
	for( int i = 0; i < count; i++ )
	{
		double h = cm.elem(i);
		base_properties* pProps = NULL;
		
		graphics_object obj = gh_manager::get_object (h);
		if ( obj )
		{
			// get properties
			pProps = &obj.get_properties();
		}
		
		// 1 - do we have this child already?
		if ( ! _children.contains( h ) )
		{
			// no, we don't
			// create object
			UIItem* pNewChild = createItem( pProps );
			if ( pNewChild )
			{
				newMap.insert( h, pNewChild );
			}
			else
			{
				qWarning("Didn't know how to create object of type %s",
					pProps->get_type().c_str() );
			}
		}
		else
		{
			// yes, we have it
			// 2. is it the same type?
			if ( _children[h]->properties()->get_type() == pProps->get_type() )
			{
				// just update
				_children[h]->copyProperties( pProps );
				newMap.insert( h, _children[h] );
				_children.remove( h ); // remove from old map
			}
			else
			{
				// type changed - re-create
				// TODO
				qDebug("re-creation not implemented");
			}
		}
	}
	
	// now items that left on old map should be removed
	foreach( double h, _children.keys() )
	{
		delete  _children[h];
	}
	
	// flip tables
	_children = newMap;
}

// ============================================================================
/// Creates item with provided property set. Item type is deduced from "type" property.
UIItem* UIItem::createItem( base_properties* pProps )
{
	return NULL;
}

}
