// axesitem.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSAXESITEM_H
#define QOGRAPHICSAXESITEM_H

#include "uiitem.h"
#include "color.h"
#include "enum.h"
#include "matrix.h"
#include "text.h"

namespace QOGraphics
{

/**
Gpahics item representingm and associated with Axes object.

 @author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/

class AxesItem : public UIItem
{

public:
	AxesItem( QGraphicsItem * parent = NULL );
	virtual ~AxesItem();
	
	// Item proeprties
	//QSizeF size() const { return _size; } TODO remove
	//void setSize( const QSizeF& size );
	void updateSize();
	void setFigureRect( const QRect& r ) { _figureRect = r; }
	
	/// Paints item
	virtual void paint
		( QPainter *painter
		, const QStyleOptionGraphicsItem* option
		, QWidget * widget = NULL );
		
	/// Returns item bounding rectangle
	virtual QRectF boundingRect() const;
	
	void recalculateTicks();				///< Recalculates ticks
	void updateChildPositions();			///< Updates child positons
	void dataChanged();						///< Updates YLim/XLim to current data
	
	// enum used in properties
	enum ReplaceMode { Add, Replace, ReplaceChildren }; 
	enum Units { Inches, Centimeters, Normalized, Points, Pixels };
	
	// properties (stored here, set in Axes )
	
	Enum box;
	Matrix xlim, ylim;
	Matrix xtick, ytick;
	Enum xtickMode, ytickMode;
	Color xcolor, ycolor;
	Enum xlimMode, ylimMode;
	Enum xdir, ydir;
	Matrix colorOrder;
	Enum nextPlot;
	Matrix position; // 1x4: [ left bottom width height ]
	Enum units; 	// inches  | centimeters | {normalized} | points | pixels
	Matrix clim;	// TODO what is this used for?
	Enum climMode;
	
	// constant child elements
	
	Text* pLabelX;
	Text* pLabelY;
	Text* pTitle;
	
		
	QPointF plotToPixel( const QPointF& p ) const;	///< converts between plot and pixel space
	QPointF pixelToPlot( const QPointF& p ) const;	///< converts between plot and pixel space
	QRectF plotBox() const;							///< Returns coordinates of plot box
	
private:
	
	// utilities
	
	double findSpacing( double len, double pixels, double minPixels );
	Matrix generateTicks( double min, double max, double spacing );
	
	double tickLength() { return 5.0; }				///< Tick length, in pixels TODO calculate from property
	
	void setPixelPositon( PlotItem* pItem, QPointF pos );	///< Sets constnt plot item position
	
	// drawing methods
	
	void drawBox( QPainter *painter );		///< Draws background box
	void drawXAxis( QPainter *painter );	///< Draws axis
	void drawYAxis( QPainter *painter );	///< Draws axis
	
	
	// data
	
	QSizeF _size;							///< Current pixel size
	QRect _figureRect;						///< Current figure rectangle to paint on

};

}

#endif // QOGRAPHICSAXESITEM_H

// EOF


