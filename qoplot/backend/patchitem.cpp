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
#include "exceptions.h"

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
	gh_manager::autolock guard;
	
	patch::properties* pProps = properties();
	// do nothing if called before properties provided
	if ( ! pProps )
	{
		return;
	}
	
	Matrix xdata				= pProps->get_xdata().matrix_value();
	Matrix ydata				= pProps->get_ydata().matrix_value();
	std::string clipping		= pProps->get_clipping();
	octave_value cdata			= pProps->get_cdata();
	
	// face color mode
	std::string faceColorMode	= pProps->get_facecolor().string_value();
	bool transparentFaces = faceColorMode == "none";
	if ( transparentFaces )
	{
		pPainter->setBrush( Qt::NoBrush );
	}
	
	// edge color mode
	bool edgesUsesFaceColor = false;
	QColor edgeColor = colorFromOctave( pProps->get_edgecolor() );
	if ( pProps->get_edgecolor().is_string() )
	{
		edgesUsesFaceColor = pProps->get_edgecolor().string_value() == "flat";
	}
	
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
		
		for( int f = 0; f< faces; f++ )
		{
			// get shape
			QPolygonF polygon;			
			for( int v = 0; v < vertices; v++ )
			{
				double x = xdata.elem( v, f );
				double y = ydata.elem( v, f );
				if ( ! isnan(x) && ! isnan(y) ) //TODO  NaM aare relevant information here, don't ignore it
				{
					QPointF pixel = mapFromParent( axesItem()->plotToPixel( QPointF( x, y ) ) );
					polygon.append( pixel );
				}
			}
			
			// get color
			QColor faceColor = colorFromCData( cdata, f );
			if ( ! transparentFaces )
			{
				pPainter->setBrush( faceColor );
			}
			if ( edgesUsesFaceColor )
			{
				pPainter->setPen( pen( faceColor, pPainter->device() ) );
			}
			else
			{
				pPainter->setPen( pen( edgeColor, pPainter->device() ) );
			}
			
		
			
			// draw
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

// ============================================================================
/// Gets face color from CData property.
///\par cdata - value of CData property
///\par face - face index 
QColor PatchItem::colorFromCData( const octave_value& cdata, int face )
{
	// is cdata scalar?
	if ( cdata.is_scalar_type() )
	{
		return colormapColor( cdata.scalar_value() );
	}
	
	Matrix cdataMatrix = cdata.matrix_value();
	
	if ( cdataMatrix.dim3() == 1 )
	{
		// TODO use per-vertex color here
		return colormapColor( cdataMatrix.elem( 0, face ) );
	}
	else
	{
		int r = int( 255 * cdataMatrix( 0, face, 0 ) );
		int g = int( 255 * cdataMatrix( 0, face, 1 ) );
		int b = int( 255 * cdataMatrix( 0, face, 2 ) );
		
		return QColor( r, g, b );
	}
}

// ============================================================================
/// Returns properties converted to appropriate type.
patch::properties* PatchItem::properties() const
{
	base_properties* pProps = PlotItem::properties();
	patch::properties* pPatchProps = dynamic_cast<patch::properties*>( pProps );
	if ( pPatchProps )
	{
		return pPatchProps;
	}
	else
	{
		throw Exception( QString("Patch has invalid properties type :%1").arg( pProps->get_type().c_str() ) );
	}
}

}
