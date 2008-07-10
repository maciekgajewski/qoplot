// patchitem.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#include <QPainter>

#include "patchitem.h"
#include "axesitem.h"
#include "converters.h"

namespace QOGraphics
{

// ============================================================================
// Constructor
PatchItem::PatchItem( double h, AxesItem* parent ): PlotItem( h, parent )
{
	setZValue( 0.5 ); // above axes
	
	propertiesChanged();
}

// ============================================================================
// Destructor
PatchItem::~PatchItem()
{
	// empty
}

// ============================================================================
// Draws item
void PatchItem::paint
	( QPainter *pPainter
	, const QStyleOptionGraphicsItem* /*option*/
	, QWidget * /*widget*/ /*= NULL*/ )
{
	gh_manager::lock_guard guard;
	
	patch::properties* pProps = properties();
	// do nothing if called before properties provided
	if ( ! pProps )
	{
		return;
	}
	
	Matrix xdata = pProps->get_xdata().matrix_value();
	Matrix ydata = pProps->get_ydata().matrix_value();
	std::string clipping = pProps->get_clipping();
	QColor edgeColor = colorFromOctave( pProps->get_edgecolor() );
	
	QColor faceColor = colorFromOctave( pProps->get_facecolor() ); // TODO what abot 'cdata'?
	
	int faces = qMin( xdata.dim2(), ydata.dim2() );
	int vertices = qMin( xdata.dim1(), ydata.dim1() );
	
	if ( faces == 0 || vertices <= 1 )
	{
		return; // nothing to paint
	}
	
	pPainter->save();
	
		// turn on clipping when appropriate
		if ( clipping == "on" )
		{
			pPainter->setClipRect( plotBox(), Qt::IntersectClip );
		}
		
		pPainter->setPen( pen( edgeColor, pPainter->device() ) );
		pPainter->setBrush( faceColor );
		
		for( int f = 0; f< faces; f++ )
		{
			QPolygonF polygon;
			for( int v = 0; v < vertices; v++ )
			{
				QPointF pixel = mapFromParent(
					axesItem()->plotToPixel( 
						QPointF( xdata.elem( v, f ), ydata.elem( v, f ) )
							)
						);
				polygon.append( pixel );
			}
			
			pPainter->drawPolygon( polygon );
		}
		
	pPainter->restore();
}
	
// ============================================================================
// Returns item's boundiong rectangle.
QRectF PatchItem::boundingRect() const
{
	// be easy, return entire parent axes rectangle
	// TODO cut if optimization needed
	
	QRectF axesRect = axesItem()->boundingRect();
	
	return mapFromParent( axesRect ).boundingRect();
}


}
