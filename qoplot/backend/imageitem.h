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

namespace QOGraphics
{

/**
Image item. Represents image objec.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class ImageItem : public PlotItem
{
public:
	ImageItem( double h, AxesItem* parent );
	virtual ~ImageItem();

	/// Paints item
	virtual void paint
		( QPainter *painter
		, const QStyleOptionGraphicsItem* option
		, QWidget * widget = NULL );
		
	/// Returns item bounding rectangle
	virtual QRectF boundingRect() const;
	
protected:

	virtual void propertiesChanged();

private:

	void createImage();
	void createColormapImage( const Matrix& cdata );
	void createFloatRGBImage( const FloatNDArray& cdata );
	void createUint8RGBImage( const uint8NDArray& cdata );
	
	QImage _image;	///< Actual image used in rendering
	
	QRectF imageRect() const; ///< Image rectangle on plot's XY plane
};

}

#endif // QOGRAPHICSIMAGEITEM_H

// EOF


