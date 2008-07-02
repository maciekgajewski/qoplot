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

namespace QOGraphics
{

// ============================================================================
// Constructor
UIItem::UIItem( QGraphicsItem* parent ): QGraphicsItem( parent )
{
	_pProperties = NULL;
}

// ============================================================================
// Destructor
UIItem::~UIItem()
{
	// nothing
}

// ============================================================================
/// Returns pen created form provided color and LineWidth and LineStyle properties.
QPen UIItem::pen( const QColor& color, const QPaintDevice* pDevice  ) const
{
	/* TODO
	double width = qRound( qMin( 1.0, ptToPixel( lineWidth, pDevice ) ) );
	return QPen( QBrush(color), int(width), Qt::PenStyle( int(lineStyle) ) );
	*/
	return QPen();
}

// ============================================================================
/// Returns font created from FontName, FontAngle, FontSize and FontWeight properties.
QFont UIItem::font() const
{
	/* TODO
	return QFont( fontName, fontSize, fontWeight, fontAngle != QFont::StyleNormal );
	*/
	return QFont();
}

// ============================================================================
/// Updates item state to changed properties.
void UIItem::propertiesChanged()
{
	update();
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


}
