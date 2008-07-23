// textitem.cpp, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#include <QFontMetricsF>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>

#include "textitem.h"
#include "converters.h"
#include "exceptions.h"

namespace QOGraphics 
{

// ============================================================================
// Constructor
TextItem::TextItem( double h, AxesItem* parent )
	: PlotItem( h, parent)
{
	setZValue( 0.5 ); // Above lines, below legend. TODO do some infrastructure for this

	propertiesChanged();
}

// ============================================================================
// Destructor
TextItem::~TextItem()
{
	// nothing
}

// ============================================================================
/// Paints item
void TextItem::paint
	( QPainter *pPainter
	, const QStyleOptionGraphicsItem* /*option*/
	, QWidget * /*widget*/ /*= NULL*/ )
{
	gh_manager::autolock guard;
	
	text::properties* pProps = properties_cast<text::properties*>( properties() );
	// this can be caled befor proerties are here
	if ( ! pProps ) return;
	
	pPainter->save();
	
	// get neccesary properties
	
	double rotation = pProps->get_rotation();
	double margin = pProps->get_margin();
	QColor edgeColor = colorFromOctave( pProps->get_edgecolor_rgb() );
	QColor backgroundColor = colorFromOctave( pProps->get_backgroundcolor_rgb() );
	QString string = pProps->get_string().c_str();
	QColor color = colorFromOctave( pProps->get_color_rgb() );
	
		// set clipping
		if ( pProps->get_clipping() == "on" )
		{
			pPainter->setClipRect( plotBox(), Qt::IntersectClip );
		}
	
		// transform
		pPainter->rotate( -rotation );
		pPainter->translate( alignTranlsation() );
		
		// draw frame
		QRectF extent = textExtent();
		QRectF frame = QRectF( -margin, -margin, extent.width() + 2*margin, extent.height() + 2*margin );
		
		pPainter->setPen( pen( edgeColor, pPainter->device() ) );
		pPainter->setBrush( backgroundColor );
		pPainter->drawRect( frame );
	
		// draw text
		pPainter->setPen( QColor( color ) );
		pPainter->setFont( font() );
		pPainter->drawText( QPointF( 0, extent.height() ), string );
	pPainter->restore();
}
	
// ============================================================================
/// Returns item's bounding rectangle
QRectF TextItem::boundingRect() const
{
	gh_manager::autolock guard;
	
	text::properties* pProps = properties_cast<text::properties*>( properties() );
	// this can be caled befor proerties are here
	if ( ! pProps ) return QRectF();
	
	double margin		= pProps->get_margin();
	double lineWidth	= pProps->get_linewidth();
	double rotation		= pProps->get_rotation();
	
	// get extent
	QRectF extent = textExtent();
	
	// get margin
	double m = margin + ptToPixel( lineWidth, QApplication::desktop() ); // TODO fing another source of DPI
	
	// create bounding rect by adding margin to extent
	QRectF br = QRectF( -m, -m, extent.width() + 2*m, extent.height() + 2*m );
	
	// apply alignment translation
	br.translate( alignTranlsation() );
	
	// rotate!
	QMatrix matrix;
	matrix.rotate( -rotation );
	return matrix.mapRect( br );
}

// ============================================================================
/// Fints text extent, from text's top-left corner.
QRectF TextItem::textExtent() const
{
	text::properties* pProps = properties_cast<text::properties*>( properties() );
	QString string = pProps->get_string().c_str();
	
	// get text extent
	QFontMetricsF metrics( font() );
	
	return metrics.tightBoundingRect( string );

}

// ============================================================================
/// Finds transformation that has to be applied to text rect to get desired alignment.
/// It is assumed that without translation text will be paited aligned left-cap
QPointF TextItem::alignTranlsation() const
{
	text::properties* pProps = properties_cast<text::properties*>( properties() );
	double margin		= pProps->get_margin();
	double lineWidth	= pProps->get_linewidth();
	
	QString horizontalAlignment	= pProps->get_horizontalalignment().c_str();
	QString verticalAlignment	= pProps->get_verticalalignment().c_str();
	
	QRectF extent = textExtent();
	
	double w = extent.width();
	double h = extent.height();
	
	// get margin
	double m = margin + ptToPixel( lineWidth, QApplication::desktop() ); // TODO fing another source of DPI;
	
	// find x and y
	double x = 0.0, y = 0.0;
		
	if ( horizontalAlignment == "left" ) x = 0.0;
	else if ( horizontalAlignment == "center" ) x = -w / 2;
	else if ( horizontalAlignment == "right" ) x = -w;
	
	if ( verticalAlignment == "top" )	y = m;
	else if ( verticalAlignment == "cap" )	y = 0;
	else if ( verticalAlignment == "middle" )	y = -h/2;
	else if ( verticalAlignment == "baseline" )	y = -h;
	else if ( verticalAlignment == "bottom" )	y = -h-m;
	
	return QPointF( x, y );
}

// ============================================================================
/// Updates to properties.
void TextItem::propertiesChanged()
{
	PlotItem::propertiesChanged();
	update();
}

}
