// imageitem.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSIMAGEITEM_H
#define QOGRAPHICSIMAGEITEM_H

#include "plotitem.h"

#include "matrix.h"
#include "enum.h"

namespace QOGraphics {

/**
Image item. Represents image object on canvas.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class ImageItem : public PlotItem
{
public:
	ImageItem(QGraphicsItem* parent = NULL);
	virtual ~ImageItem();

	/// Paints item
	virtual void paint
		( QPainter *painter
		, const QStyleOptionGraphicsItem* option
		, QWidget * widget = NULL );
		
	/// Returns item bounding rectangle
	virtual QRectF boundingRect() const;
	
	virtual void propertyChanged();
	// enums used in properties
	
	enum ImageMode { Colormap, RGB, RGBA, Intensity };
	
	// properties
	
	Matrix cdata, cdataR, cdataG, cdataB, alphaData; // image data
	Matrix xdata, ydata; // where to paint the image
	
	Enum mode;	///< Image mode: {colormap}|rgb|rgba|intensity

private:

	void createImage();
	void createColormapImage();
	void createIntensityImage();
	void createRGBImage();
	
	QImage _image;	///< Actual image used in rendering
	
	QRectF imageRect() const; ///< Image rectangle on plot's XY plane
	
	
};

}

#endif // QOGRAPHICSIMAGEITEM_H

// EOF


