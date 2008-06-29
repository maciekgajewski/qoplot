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
#include "patchitem.h"
#include "axesitem.h"

namespace QOGraphics
{

// ============================================================================
// Constructor
PatchItem::PatchItem( QGraphicsItem* parent ): PlotItem( parent )
{
	setZValue( 0.5 ); // above axes
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
	int faces = qMin( xdata.cols(), ydata.cols() );
	int vertices = qMin( xdata.rows(), ydata.rows() );
	
	if ( faces == 0 || vertices <= 1 )
	{
		return; // nothing to paint
	}
	
	pPainter->save();
	
		// turn on clipping when appropriate
		if ( clipping == On )
		{
			pPainter->setClipRect( plotBox(), Qt::IntersectClip );
		}
		
		pPainter->setPen( pen( edgeColor, pPainter->device() ) );
		pPainter->setBrush( QColor( faceColor ) );
		
		for( int f = 0; f< faces; f++ )
		{
			QPolygonF polygon;
			for( int v = 0; v < vertices; v++ )
			{
				QPointF pixel = mapFromParent(
					axesItem()->plotToPixel( 
						QPointF( xdata.value( v+1, f+1 ), ydata.value( v+1, f+1 ) )
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
