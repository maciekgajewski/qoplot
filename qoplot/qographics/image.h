// image.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSIMAGE_H
#define QOGRAPHICSIMAGE_H

#include "plotobject.h"
#include "imageitem.h"

namespace QOGraphics
{

/**
Image object. Represents image. Actual painting is done by ImageItem

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/

class Image : public PlotObject
{
	Q_OBJECT
	Q_PROPERTY( QOGraphics::Matrix CData READ getCData WRITE setCData )
	Q_PROPERTY( QOGraphics::Matrix CDataR READ getCDataR WRITE setCDataR )
	Q_PROPERTY( QOGraphics::Matrix CDataG READ getCDataG WRITE setCDataG )
	Q_PROPERTY( QOGraphics::Matrix CDataB READ getCDataB WRITE setCDataB )
	Q_PROPERTY( QOGraphics::Matrix AlphaData READ getAlphaData WRITE setAlphaData )
	Q_PROPERTY( QOGraphics::Matrix XData READ getXData WRITE setXData )
	Q_PROPERTY( QOGraphics::Matrix YData READ getYData WRITE setYData )
	
	Q_PROPERTY( QString Mode READ getMode WRITE setMode ) // rgb|rgba|intensity|colormap
	

public:

	Image( Root* root, Handle handle, QObject* parent );
	virtual ~Image();
	
	virtual ImageItem* item() const { return _pItem; }
	
	// properties
	
	virtual QString getType() const { return "image"; }
	
	Matrix getCData() const { return _pItem->cdata; }
	void setCData( const Matrix& m ){ _pItem->geometryWillChange(); _pItem->cdata = m; propertyChanged(); }
	
	Matrix getCDataR() const { return _pItem->cdataR; }
	void setCDataR( const Matrix& m ){ _pItem->geometryWillChange(); _pItem->cdataR = m; propertyChanged(); }
	Matrix getCDataG() const { return _pItem->cdataG; }
	void setCDataG( const Matrix& m ){ _pItem->geometryWillChange(); _pItem->cdataG = m; propertyChanged(); }
	Matrix getCDataB() const { return _pItem->cdataB; }
	void setCDataB( const Matrix& m ){ _pItem->geometryWillChange(); _pItem->cdataB = m; propertyChanged(); }
	
	Matrix getAlphaData() const { return _pItem->alphaData; }
	void setAlphaData( const Matrix& m ){ _pItem->geometryWillChange(); _pItem->alphaData = m; propertyChanged(); }
	
	Matrix getXData() const { return _pItem->xdata; }
	void setXData( const Matrix& m ) { _pItem->geometryWillChange();_pItem->xdata = m; propertyChanged(); }
	
	Matrix getYData() const { return _pItem->ydata; }
	void setYData( const Matrix& m ) { _pItem->geometryWillChange(); _pItem->ydata = m; propertyChanged(); }
	
	QString getMode() const { return _pItem->mode; }
	void setMode( const QString& s ) {  _pItem->mode = s; propertyChanged(); }
		

	
protected:

	virtual void initProperties();
	
private:

	ImageItem* _pItem;

};

}

#endif // QOGRAPHICSIMAGE_H

// EOF


