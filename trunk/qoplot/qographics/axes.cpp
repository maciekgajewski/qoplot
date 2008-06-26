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
#include "root.h"
#include "exceptions.h"
#include "text.h"
#include "line.h"
#include "image.h"
#include "legend.h"

namespace QOGraphics
{

// ============================================================================
/// Constructor
Axes::Axes( Root* root, Handle handle, QObject* parent ): UIObject(root, handle, parent)
{
	// Create item
	_pItem = new AxesItem( qobject_cast<Figure*>( parent) );
	
	// create mandatory children
	_pItem->pTitle = new Text( root, InvalidHandle, this );
	_pItem->pLabelX = new Text( root, InvalidHandle, this );
	_pItem->pLabelY = new Text( root, InvalidHandle, this );
	_pItem->pLegend = new Legend( root, InvalidHandle, this );
	
	root->addObject( _pItem->pTitle );
	root->addObject( _pItem->pLabelX );
	root->addObject( _pItem->pLabelY );
	root->addObject( _pItem->pLegend );
	
	// go on with initializations
	initProperties();
	addToParent();
}

// ============================================================================
/// Initializes object's properties
void Axes::initProperties()
{
	UIObject::initProperties();
	
	_pItem->color = Qt::white;
	
	_pItem->box.addValue( 1, "on" );
	_pItem->box.addValue( 0, "off", true );
	
	_pItem->xtickMode.addValue( AxesItem::Auto, "auto", true );
	_pItem->xtickMode.addValue( AxesItem::Manual, "manual" );
	
	_pItem->ytickMode.addValue( AxesItem::Auto, "auto", true );
	_pItem->ytickMode.addValue( AxesItem::Manual, "manual" );
	
	_pItem->xlim = Matrix( 1, 2 );
	_pItem->xlim.setVectorValue( 1, 0.0 );
	_pItem->xlim.setVectorValue( 2, 1.0 );
	
	_pItem->ylim = Matrix( 1, 2 );
	_pItem->ylim.setVectorValue( 1, 0.0 );
	_pItem->ylim.setVectorValue( 2, 1.0 );
	
	_pItem->xcolor = QApplication::palette().color( QPalette::ButtonText );
	_pItem->ycolor = QApplication::palette().color( QPalette::ButtonText );
	
	_pItem->xlimMode.addValue( AxesItem::Auto, "auto", true );
	_pItem->xlimMode.addValue( AxesItem::Manual, "manual" );
	
	_pItem->ylimMode.addValue( AxesItem::Auto, "auto", true );
	_pItem->ylimMode.addValue( AxesItem::Manual, "manual" );
	
	_pItem->xdir.addValue( AxesItem::Normal, "normal", true );
	_pItem->xdir.addValue( AxesItem::Reverse, "reverse" );
	
	_pItem->ydir.addValue( AxesItem::Normal, "normal", true );
	_pItem->ydir.addValue( AxesItem::Reverse, "reverse" );
	
	// init labels	
	
	_pItem->pTitle->setVerticalAlignment( "bottom" );
	_pItem->pTitle->setHorizontalAlignment( "center" );
	_pItem->pTitle->setUsePlotCoordinates( "off" );
	_pItem->pTitle->setHandleVisibility( "off" );
	_pItem->pTitle->setMargin( Matrix( 5 ) );
	
	_pItem->pLabelX->setVerticalAlignment( "top" );
	_pItem->pLabelX->setHorizontalAlignment( "center" );
	_pItem->pLabelX->setUsePlotCoordinates( "off" );
	_pItem->pLabelX->setHandleVisibility( "off" );
	_pItem->pLabelX->setMargin( Matrix( 5 ) );
	
	_pItem->pLabelY->setVerticalAlignment( "bottom" );
	_pItem->pLabelY->setHorizontalAlignment( "center" );
	_pItem->pLabelY->setUsePlotCoordinates( "off" );
	_pItem->pLabelY->setRotation( 90 );
	_pItem->pLabelY->setHandleVisibility( "off" );
	_pItem->pLabelY->setMargin( Matrix( 5 ) );
	
	// init legend
	
	_pItem->pLegend->setHandleVisibility( "off" );
	_pItem->pLegend->setVisible( "off" );
	_pItem->pLabelY->setUsePlotCoordinates( "off" );
	
	// color order
	
	Matrix co( 7, 3 );
	co.setValue( 1, 1, 0.0 );
	co.setValue( 1, 2, 0.0 );
	co.setValue( 1, 3, 1.0 );
	
	co.setValue( 2, 1, 0.0 );
	co.setValue( 2, 2, 0.5 );
	co.setValue( 2, 3, 0.0 );
	
	co.setValue( 3, 1, 1.0 );
	co.setValue( 3, 2, 0.0 );
	co.setValue( 3, 3, 0.0 );

	co.setValue( 4, 1, 0.0 );
	co.setValue( 4, 2, 0.75 );
	co.setValue( 4, 3, 0.75 );

	co.setValue( 5, 1, 0.75 );
	co.setValue( 5, 2, 0.0 );
	co.setValue( 5, 3, 0.75 );

	co.setValue( 6, 1, 0.75 );
	co.setValue( 6, 2, 0.75 );
	co.setValue( 6, 3, 0.0 );

	co.setValue( 7, 1, 0.25 );
	co.setValue( 7, 2, 0.25 );
	co.setValue( 7, 3, 0.25 );
	
	_pItem->colorOrder = co;
	
	_pItem->nextPlot.addValue( AxesItem::Add, "add" );
	_pItem->nextPlot.addValue( AxesItem::Replace, "replace", true );
	_pItem->nextPlot.addValue( AxesItem::ReplaceChildren , "replacechildren" );
	
	_pItem->units.addValue( AxesItem::Inches, "inches" );
	_pItem->units.addValue( AxesItem::Centimeters, "centimeters" );
	_pItem->units.addValue( AxesItem::Normalized, "normalized", true );
	_pItem->units.addValue( AxesItem::Points, "points" );
	_pItem->units.addValue( AxesItem::Pixels, "pixels" );
	
	_pItem->position = Matrix( 1, 4 );
	_pItem->position.setVectorValue( 1, 0.1 );
	_pItem->position.setVectorValue( 2, 0.1 );
	_pItem->position.setVectorValue( 3, 0.8 );
	_pItem->position.setVectorValue( 4, 0.8 );
	
	Matrix clim( 1, 2 );
	clim.setVectorValue( 1, 0.0 );
	clim.setVectorValue( 2, 1.0 );
	
	_pItem->clim = clim;
	
	_pItem->climMode.addValue( AxesItem::Auto, "auto", true );
	_pItem->climMode.addValue( AxesItem::Manual, "manual" );
}

// ============================================================================
/// Destructor
Axes::~Axes()
{
	// nope
}

// ============================================================================
/// Setsd axes position
/*
void Axes::setPosition( const QRectF& pos )
{
	_pItem->setPos( pos.topLeft() );
	_pItem->setSize( pos.size() );
	_pItem->updateChildPositions();
}
*/
// ============================================================================
/// Sets 'box visible' property
void Axes::setBox( const QString& box )
{
	_pItem->box = box;
	_pItem->update();
}

// ============================================================================
/// Sets XTick proeprty. Also sets XTickMode to 'manual'.
void Axes::setXTick( const Matrix& xtick )
{
	_pItem->xtick = xtick;
	_pItem->xtickMode = AxesItem::Manual;
	_pItem->update();
}

// ============================================================================
/// Sets YTick proeprty. Also sets YTickMode to 'manual'.
void Axes::setYTick( const Matrix& ytick )
{
	_pItem->ytick = ytick;
	_pItem->ytickMode = AxesItem::Manual;
	_pItem->update();
}

// ============================================================================
/// Sets tick mode.
void Axes::setXTickMode( const QString& mode )
{
	_pItem->xtickMode = mode;
	_pItem->recalculateTicks();
	_pItem->update();
}

// ============================================================================
/// Sets tick mode.
void Axes::setYTickMode( const QString& mode )
{
	_pItem->xtickMode = mode;
	_pItem->recalculateTicks();
	_pItem->update();
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
	
	_pItem->xlim = xlim;
	_pItem->xlimMode = AxesItem::Manual;
	_pItem->recalculateTicks();
	_pItem->updateChildPositions();
	_pItem->update();
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
	
	_pItem->ylim = ylim;
	_pItem->ylimMode = AxesItem::Manual;
	_pItem->updateChildPositions();
	_pItem->recalculateTicks();
	_pItem->update();
}

// ============================================================================
/// Sets XLim mode. If set back to 'auto', XLim is recalulcalted again to match displayed data.
void Axes::setXLimMode( const QString& mode )
{
	_pItem->xlimMode = mode;
	
	if ( _pItem->xlimMode == AxesItem::Auto )
	{
		// TODO recalculate xlim here
		_pItem->updateChildPositions();
	}
	
	_pItem->update();
}

// ============================================================================
/// Sets YLim mode. If set back to 'auto', YLim is recalulcalted again to match displayed data.
void Axes::setYLimMode( const QString& mode )
{
	_pItem->ylimMode = mode;
	
	if ( _pItem->ylimMode == AxesItem::Auto )
	{
		// TODO recalculate xlim here
		_pItem->updateChildPositions();
	}
	
	_pItem->update();
}

// ============================================================================
/// Creates child plot object. Assigns handle 'h'.
/// Do not use this method directly. Use Root:createUIObject instead.
UIObject* Axes::createPlotObject( const QString& type, Handle h )
{
	if ( type == "text" )
	{
		Text* pText = new Text( root(), h, this );
		return pText;
	}
	else if ( type == "line" )
	{
		Line* pLine = new Line( root(), h, this );
		return pLine;
	}
	else if ( type == "image" )
	{
		Image* pImage = new Image( root(), h, this );
		return pImage;
	}
	// TODO other types here
	else
	{
		throw Exception( QString("Unknown plot object type: %1").arg( type ) );
	}
}

// ============================================================================
/// MEssage from child: Child size has changed.
void Axes::childSizeChanged()
{
	_pItem->updateChildPositions();
	_pItem->update();
}

// ============================================================================
/// Removes all children, except of constant children
void Axes::clear()
{
	QList<Object*> children = findChildren<Object*>();
	
	foreach( Object* pChild, children )
	{
		if ( pChild != _pItem->pLabelX	&&
			pChild != _pItem->pLabelY &&
			pChild  != _pItem->pTitle )
		{
			pChild->free();
			delete pChild;
		}
	}
	
	_pItem->update();
}

// ============================================================================
/// Size changedm or becouse figure was resize, od becouse 'position' property has changed.
void Axes::sizeChanged()
{
	_pItem->updateSize();
}

}
