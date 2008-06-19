// axes.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSAXES_H
#define QOGRAPHICSAXES_H

#include "uiobject.h"
#include "axesitem.h"

namespace QOGraphics
{

/**
Axes graphics object. USed as container for plot elements. Axes are always children of 
Figure.

Axes are associated with AxesItemm which is actual axes graphic item.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class Axes : public UIObject
{
	Q_OBJECT
	
	Q_PROPERTY( QString Box READ getBox WRITE setBox );
	//Q_PROPERTY( QOGraphics::Matrix CLim READ getClim WRITE setClim );
	//Q_PROPERTY( QString CLimMode READ getCLimMode WRITE setCLimMode );
	//Q_PROPERTY( Matrix Legend READ getLegend WRITE setLegend );
	//Q_PROPERTY( QString NextPlot READ getNextPlot WRITE setNextPlot );
	//Q_PROPERTY( Matrix TickLength READ getTickLength WRITE setTickLength );
	//Q_PROPERTY( QString Title READ getTitle WRITE setTitle );
	//Q_PROPERTY( QString XAxisLocation READ getXAxisLocation WRITE setXAxisLocation );
	//Q_PROPERTY( QString YAxisLocation READ getYAxisLocation WRITE setYAxisLocation );
	Q_PROPERTY( QVariant XColor READ getXColor WRITE setXColor );
	Q_PROPERTY( QVariant YColor READ getYColor WRITE setYColor );
	//Q_PROPERTY( QString XLabel READ getXLabel WRITE setXLabel );
	//Q_PROPERTY( QString YLabel READ getYLabel WRITE setYLabel );
	Q_PROPERTY( QOGraphics::Matrix XLim READ getXLim WRITE setXLim );
	Q_PROPERTY( QOGraphics::Matrix YLim READ getYLim WRITE setYLim );
	Q_PROPERTY( QString XLimMode READ getXLimMode WRITE setXLimMode );
	Q_PROPERTY( QString YLimMode READ getYLimMode WRITE setYLimMode );
	Q_PROPERTY( QOGraphics::Matrix XTick READ getXTick WRITE setXTick );
	Q_PROPERTY( QOGraphics::Matrix YTick READ getYTick WRITE setYTick );
	//Q_PROPERTY( QStringList XTickLabel READ getXTickLabel WRITE setXTickLabel );
	//Q_PROPERTY( QStringList YTickLabel READ getYTickLabel WRITE setYTickLabel );
	Q_PROPERTY( QString XTickMode READ getXTickMode WRITE setXTickMode );
	Q_PROPERTY( QString YTickMode READ getYTickMode WRITE setYTickMode );

public:

	Axes( Root* root, Handle handle, QObject* parent );
	virtual ~Axes();
	
	// visual setup and properties
	
	virtual void setScene( QGraphicsScene* scene);
	void setPosition( const QRectF& pos ); /// Sets axes postion in figure
	
	// prioperties
	
	virtual QString getType() const { return "axes"; }

	QString getBox() const { return _item.box; }
	void setBox( const QString& box );
	
	virtual QVariant getColor() const { return _item.color.toVariant(); }
	virtual void setColor( const QVariant& color );
	
	Matrix getXLim() const { return _item.xlim; }
	Matrix getYLim() const { return _item.ylim; }
	
	void setXLim( const Matrix& xlim );
	void setYLim( const Matrix& ylim );
	
	Matrix getXTick() const { return _item.xtick; }
	Matrix getYTick() const { return _item.xtick; }
	
	void setXTick( const Matrix& xtick );
	void setYTick( const Matrix& ytick );
	
	QString getXTickMode() const { return _item.xtickMode; }
	QString getYTickMode() const { return _item.ytickMode; }
	
	void setXTickMode( const QString& mode );
	void setYTickMode( const QString& mode );
	
	QVariant getXColor() const { return _item.xcolor.toVariant(); }
	QVariant getYColor() const { return _item.xcolor.toVariant(); }
	void setXColor( const QVariant& c ) { _item.xcolor.fromVariant( c ); _item.update(); }
	void setYColor( const QVariant& c ) { _item.ycolor.fromVariant( c ); _item.update(); }
	
	QString getXLimMode() const { return _item.xlimMode; }
	QString getYLimMode() const { return _item.ylimMode; }
	
	void setXLimMode( const QString& mode );
	void setYLimMode( const QString& mode );

private:

	// data
	
	AxesItem _item;
};

}

#endif // QOGRAPHICSAXES_H

// EOF


