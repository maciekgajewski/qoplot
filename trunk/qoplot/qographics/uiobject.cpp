// uiobject.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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

#include <QFont>

#include "uiitem.h"
#include "uiobject.h"
#include "figure.h"
#include "exceptions.h"

namespace QOGraphics
{

// ============================================================================
// Constructor
UIObject::UIObject ( Root* root, Handle handle, QObject* parent )
		: Object ( root, handle, parent )
{
	// nothing
}

// ============================================================================
// Destructor
UIObject::~UIObject()
{
	// nothing
}

// ============================================================================
/// Adds QGraphicsItem associated with object to parent. If parent is UIOject, adds it as a child 
/// item, if parent is figure, adds item to it's scene.
void UIObject::addToParent()
{
	// first - try add to scene
	Figure* pFigure = qobject_cast<Figure*>( parent() );
	
	if ( pFigure )
	{
		pFigure->scene()->addItem( item() );
	}
	// then - assume that parent is a UIObject
	else
	{
		UIObject* pObject = qobject_cast<UIObject*>( parent() );
		if ( pObject )
		{
			item()->setParentItem( pObject->item() );
		}
		else
		{
			throw Exception("UIObject has no valid parent");
		}
	}
	
}

// ============================================================================
/// Initializes properties. Extent this method in your class and call in constructor.
void UIObject::initProperties()
{
	UIItem* pItem = item();
	
	Q_ASSERT( pItem );
	
	pItem->color		= Qt::white;
	
	pItem->clipping.addValue( UIItem::On, "on", true );
	pItem->clipping.addValue( UIItem::Off, "off");
	
	pItem->lineStyle.addValue( Qt::SolidLine, "-", true);
	pItem->lineStyle.addValue( Qt::DashLine, "--");
	pItem->lineStyle.addValue( Qt::DotLine, ":");
	pItem->lineStyle.addValue( Qt::DashDotLine, "-.");
	pItem->lineStyle.addValue( Qt::NoPen, "none");
	
	pItem->lineWidth	= 0.5;	// [pt]
	
	pItem->fontSize		= 8.0;	// [pt]
	pItem->fontName		= QApplication::font().family();
	
	pItem->fontWeight.addValue( QFont::Light, "light");
	pItem->fontWeight.addValue( QFont::Normal, "normal", true );
	pItem->fontWeight.addValue( QFont::DemiBold, "demi");
	pItem->fontWeight.addValue( QFont::Bold, "bold");
	
	
	pItem->fontAngle.addValue( QFont::StyleNormal, "normal", true );
	pItem->fontAngle.addValue( QFont::StyleItalic, "italic" );
	pItem->fontAngle.addValue( QFont::StyleOblique, "oblique" );
}

// ============================================================================
/// Deleted associated Graphics Item. Should be called manually just before 
/// deleting instance.
void UIObject::free()
{
	delete item();
}

// ============================================================================
/// Gets object visibility status
QString UIObject::getVisible() const
{
	return item()->isVisible() ? "on" : "off";
}

// ============================================================================
/// Hides/shows object
void UIObject::setVisible( const QString& str )
{
	if ( str == "on" )
	{
		item()->show();
	}
	else if ( str == "off" )
	{
		item()->hide();
	}
	else
	{
		throw Exception("Invalid visibility value. Valid values are: {on} | off.");
	}
}

} // namespace

// EOF


