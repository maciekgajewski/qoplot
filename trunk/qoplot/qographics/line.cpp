// line.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#include "line.h"

namespace QOGraphics
{

// ============================================================================
/// Constructor
Line::Line( Root* root, Handle handle, QObject* parent ): PlotObject( root, handle, parent )
{
	_pItem = new LineItem();
	initProperties();
	addToParent();
}

// ============================================================================
// Destructor
Line::~Line()
{
}

// ============================================================================
/// Initializes object's properties
void Line::initProperties()
{
	PlotObject::initProperties();
	
	_pItem->marker.addValue( LineItem::None, "none", true );
	_pItem->marker.addValue( LineItem::Plus, "+");
	_pItem->marker.addValue( LineItem::Circle, "o");
	_pItem->marker.addValue( LineItem::Asterix, "*" );
	_pItem->marker.addValue( LineItem::Point, "." );
	_pItem->marker.addValue( LineItem::Cross, "x" );
	_pItem->marker.addValue( LineItem::Square, "s" );
	_pItem->marker.addValue( LineItem::Square, "square" );
	_pItem->marker.addValue( LineItem::Diamond, "d" );
	_pItem->marker.addValue( LineItem::Diamond, "diamond" );
	_pItem->marker.addValue( LineItem::TriangleUp, "^" );
	_pItem->marker.addValue( LineItem::TriangleDown, "v" );
	_pItem->marker.addValue( LineItem::TriangleLeft, "<" );
	_pItem->marker.addValue( LineItem::TriangleRight, ">" );
	_pItem->marker.addValue( LineItem::Pentagram, "pentagram" );
	_pItem->marker.addValue( LineItem::Pentagram, "p" );
	_pItem->marker.addValue( LineItem::Hexagram, "hexagram" );
	_pItem->marker.addValue( LineItem::Hexagram, "h" );
	
	_pItem->color = Qt::blue; // TODO use auto coloring
	_pItem->markerEdgeColor = _pItem->color;
	_pItem->markerFaceColor = Qt::transparent;
	
	_pItem->markerSize = 6; // 6pt, as specified by Matlab manual

	_pItem->clipping = LineItem::On;
}

// ============================================================================
/// nform axes that data has changed. If axes are in auto range mode, they will be updated
void Line::dataChanged()
{
	_pItem->dataChanged();
}


}
