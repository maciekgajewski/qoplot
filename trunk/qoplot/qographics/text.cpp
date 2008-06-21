// text.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#include <QApplication>
#include <QPalette>

#include "text.h"
#include "exceptions.h"
#include "axes.h"

namespace QOGraphics
{

// ============================================================================
// Constructor
Text::Text(Root* root, Handle handle, QObject* parent): PlotObject(root, handle, parent)
{
	_pItem = new TextItem();
	initProperties();
	addToParent();
	
}

// ============================================================================
// Destructor
Text::~Text()
{
}

// ============================================================================
/// Initializes object's properties
void Text::initProperties()
{
	PlotObject::initProperties();
	
	_pItem->color = QApplication::palette().color( QPalette::ButtonText );
	
	_pItem->margin		= 0.0;
	_pItem->rotation	= 0.0;
	
	_pItem->string		= "";
	
	_pItem->edgeColor		= Qt::transparent;
	_pItem->backgroundColor	= Qt::transparent;
	
	_pItem->horizontalAlignment.addValue( TextItem::Left, "left", true );
	_pItem->horizontalAlignment.addValue( TextItem::Center, "center" );
	_pItem->horizontalAlignment.addValue( TextItem::Right, "right" );
	
	_pItem->verticalAlignment.addValue( TextItem::Top, "top" );
	_pItem->verticalAlignment.addValue( TextItem::Cap, "cap" );
	_pItem->verticalAlignment.addValue( TextItem::Middle, "middle", true );
	_pItem->verticalAlignment.addValue( TextItem::Baseline, "baseline" );
	_pItem->verticalAlignment.addValue( TextItem::Bottom, "bottom" );
}

}
