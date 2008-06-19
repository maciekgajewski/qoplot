// axes.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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

#include <QGraphicsScene>
#include <QApplication>
#include <QPalette>

#include "axes.h"
#include "exceptions.h"

namespace QOGraphics
{

// ============================================================================
/// Constructor
Axes::Axes( Root* root, Handle handle, QObject* parent ): UIObject(root, handle, parent)
{
	// init properties
	_item.color = Qt::white;
	
	_item.box.addValue( 1, "on" );
	_item.box.addValue( 0, "off", true );
	
	_item.xtickMode.addValue( AxesItem::Auto, "auto", true );
	_item.xtickMode.addValue( AxesItem::Manual, "manual" );
	
	_item.ytickMode.addValue( AxesItem::Auto, "auto", true );
	_item.ytickMode.addValue( AxesItem::Manual, "manual" );
	
	_item.xlim = Matrix( 1, 2 );
	_item.xlim.setVectorValue( 1, 0.0 );
	_item.xlim.setVectorValue( 2, 1.0 );
	
	_item.ylim = Matrix( 1, 2 );
	_item.ylim.setVectorValue( 1, 0.0 );
	_item.ylim.setVectorValue( 2, 1.0 );
	
	_item.xcolor = QApplication::palette().color( QPalette::ButtonText );
	_item.ycolor = QApplication::palette().color( QPalette::ButtonText );
	
	_item.xlimMode.addValue( AxesItem::Auto, "auto", true );
	_item.xlimMode.addValue( AxesItem::Manual, "manual" );
	
	_item.ylimMode.addValue( AxesItem::Auto, "auto", true );
	_item.ylimMode.addValue( AxesItem::Manual, "manual" );
}

// ============================================================================
/// Destructor
Axes::~Axes()
{
	// nope
}

// ============================================================================
/// Sets scene on which axes are painted
void Axes::setScene( QGraphicsScene* pScene )
{
	Q_ASSERT( pScene );
	pScene->addItem( & _item );
}

// ============================================================================
/// Setsd axes position
void Axes::setPosition( const QRectF& pos )
{
	_item.setPos( pos.topLeft() );
	_item.setSize( pos.size() );
}

// ============================================================================
/// Sets 'box visible' property
void Axes::setBox( const QString& box )
{
	_item.box = box;
	_item.update();
}

// ============================================================================
/// Sets colro property
void Axes::setColor( const QVariant& color )
{
	_item.color.fromVariant( color );
	_item.update();
}

// ============================================================================
/// Sets XTick proeprty. Also sets XTickMode to 'manual'.
void Axes::setXTick( const Matrix& xtick )
{
	_item.xtick = xtick;
	_item.xtickMode = AxesItem::Manual;
	_item.update();
}

// ============================================================================
/// Sets YTick proeprty. Also sets YTickMode to 'manual'.
void Axes::setYTick( const Matrix& ytick )
{
	_item.ytick = ytick;
	_item.ytickMode = AxesItem::Manual;
	_item.update();
}

// ============================================================================
/// Sets tick mode.
void Axes::setXTickMode( const QString& mode )
{
	_item.xtickMode = mode;
	_item.recalculateTicks();
	_item.update();
}

// ============================================================================
/// Sets tick mode.
void Axes::setYTickMode( const QString& mode )
{
	_item.xtickMode = mode;
	_item.recalculateTicks();
	_item.update();
}

// ============================================================================
/// Validates and sets XLim property
void Axes::setXLim( const Matrix& xlim )
{
	if ( xlim.vectorSize() < 2 )
	{
		throw Exception("'XLim' property value should be a 2-element vector.");
	}
	
	if ( xlim.vectorValue( 1 ) >= xlim.vectorValue( 2 ) )
	{
		throw Exception("'XLim' values should be increasing.");
	}
	
	_item.xlim = xlim;
	_item.xlimMode = AxesItem::Manual;
	_item.recalculateTicks();
	_item.update();
}

// ============================================================================
/// Validates and sets YLim property
void Axes::setYLim( const Matrix& ylim )
{
	if ( ylim.vectorSize() < 2 )
	{
		throw Exception("'YLim' property value should be a 2-element vector.");
	}
	
	if ( ylim.vectorValue( 1 ) >= ylim.vectorValue( 2 ) )
	{
		throw Exception("'YLim' values should be increasing.");
	}
	
	_item.ylim = ylim;
	_item.ylimMode = AxesItem::Manual;
	_item.recalculateTicks();
	_item.update();
}

// ============================================================================
/// Sets XLim mode. If set back to 'auto', XLim is recalulcalted again to match displayed data.
void Axes::setXLimMode( const QString& mode )
{
	_item.xlimMode = mode;
	
	if ( _item.xlimMode == AxesItem::Auto )
	{
		// TODO recalculate xlim here
	}
	
	_item.update();
}

// ============================================================================
/// Sets YLim mode. If set back to 'auto', YLim is recalulcalted again to match displayed data.
void Axes::setYLimMode( const QString& mode )
{
	_item.ylimMode = mode;
	
	if ( _item.ylimMode == AxesItem::Auto )
	{
		// TODO recalculate xlim here
	}
	
	_item.update();
}

}
