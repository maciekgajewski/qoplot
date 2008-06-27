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
#include "text.h"
#include "legend.h"

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
	
	Q_PROPERTY( QString Box READ getBox WRITE setBox )
	Q_PROPERTY( QOGraphics::Matrix CLim READ getCLim WRITE setCLim );
	Q_PROPERTY( QString CLimMode READ getCLimMode WRITE setCLimMode );
	//Q_PROPERTY( Matrix Legend READ getLegend WRITE setLegend );
	Q_PROPERTY( QString NextPlot READ getNextPlot WRITE setNextPlot );
	//Q_PROPERTY( Matrix TickLength READ getTickLength WRITE setTickLength );
	//Q_PROPERTY( QString XAxisLocation READ getXAxisLocation WRITE setXAxisLocation );
	//Q_PROPERTY( QString YAxisLocation READ getYAxisLocation WRITE setYAxisLocation );
	
	///\brief Grid line style.
	///
	///\par Possible values:
	/// {none} | - | -. | -- | :
	Q_PROPERTY( QString GridLineStyle READ getGridLineStyle WRITE setGridLineStyle );
	Q_PROPERTY( QVariant XColor READ getXColor WRITE setXColor )
	Q_PROPERTY( QVariant YColor READ getYColor WRITE setYColor )
	Q_PROPERTY( QOGraphics::Matrix XLabel READ getXLabel )
	Q_PROPERTY( QOGraphics::Matrix YLabel READ getYLabel )
	Q_PROPERTY( QOGraphics::Matrix Title READ getTitle )
	Q_PROPERTY( QOGraphics::Matrix XLim READ getXLim WRITE setXLim )
	Q_PROPERTY( QOGraphics::Matrix YLim READ getYLim WRITE setYLim )
	Q_PROPERTY( QString XLimMode READ getXLimMode WRITE setXLimMode )
	Q_PROPERTY( QString YLimMode READ getYLimMode WRITE setYLimMode )
	Q_PROPERTY( QOGraphics::Matrix XTick READ getXTick WRITE setXTick )
	Q_PROPERTY( QOGraphics::Matrix YTick READ getYTick WRITE setYTick )
	//Q_PROPERTY( QStringList XTickLabel READ getXTickLabel WRITE setXTickLabel );
	//Q_PROPERTY( QStringList YTickLabel READ getYTickLabel WRITE setYTickLabel );
	Q_PROPERTY( QString XTickMode READ getXTickMode WRITE setXTickMode )
	Q_PROPERTY( QString YTickMode READ getYTickMode WRITE setYTickMode )
	Q_PROPERTY( QString XDir READ getXDir WRITE setXDir )
	Q_PROPERTY( QString YDir READ getYDir WRITE setYDir )
	Q_PROPERTY( QOGraphics::Matrix ColorOrder READ getColorOrder WRITE setColorOrder )
	Q_PROPERTY( QOGraphics::Matrix Position READ getPosition WRITE setPosition )
	Q_PROPERTY( QString Units READ getUnits WRITE setUnits )
	
	///\brief Handle to axes Legend object.
	Q_PROPERTY( QOGraphics::Matrix Legend READ getLegend )
	
public:

	Axes( Root* root, Handle handle, QObject* parent );
	virtual ~Axes();
	
	// visual setup and properties
	
	//void setPosition( const QRectF& pos ); /// Sets axes postion in figure TODO remove
	virtual UIItem* item() const { return _pItem; }
	
	
	/// Plot object factory
	UIObject* createPlotObject( const QString& type, Handle h );
	
	/// Message from children:  legends needs to be updated
	void updateLegend();
	
	/// Size changed -  update actual size to figure/position
	void sizeChanged();
	
	/// Message from figure - figure rect
	void setFigureRect( const QRect& r ){ _pItem->setFigureRect( r ); }
	
	/// Message from child - size changed
	void childSizeChanged();
	
	/// Clears axes (cla)
	void clear();
	
	/// Resets axes to defautl settings
	void reset();
	
	
	// prioperties
	
	virtual QString getType() const { return "axes"; }

	QString getBox() const { return _pItem->box; }
	void setBox( const QString& box );
	
	Matrix getXLim() const { return _pItem->xlim; }
	Matrix getYLim() const { return _pItem->ylim; }
	
	void setXLim( const Matrix& xlim );
	void setYLim( const Matrix& ylim );
	
	Matrix getXTick() const { return _pItem->xtick; }
	Matrix getYTick() const { return _pItem->xtick; }
	
	void setXTick( const Matrix& xtick );
	void setYTick( const Matrix& ytick );
	
	QString getXTickMode() const { return _pItem->xtickMode; }
	QString getYTickMode() const { return _pItem->ytickMode; }
	
	void setXTickMode( const QString& mode );
	void setYTickMode( const QString& mode );
	
	QVariant getXColor() const { return _pItem->xcolor.toVariant(); }
	QVariant getYColor() const { return _pItem->xcolor.toVariant(); }
	void setXColor( const QVariant& c ) { _pItem->xcolor.fromVariant( c ); _pItem->update(); }
	void setYColor( const QVariant& c ) { _pItem->ycolor.fromVariant( c ); _pItem->update(); }
	
	QString getXLimMode() const { return _pItem->xlimMode; }
	QString getYLimMode() const { return _pItem->ylimMode; }
	
	void setXLimMode( const QString& mode );
	void setYLimMode( const QString& mode );

	QString getXDir() const { return _pItem->xdir; }
	QString getYDir() const { return _pItem->ydir; }
	
	void setXDir( const QString& dir ) { _pItem->xdir = dir; _pItem->update(); }
	void setYDir( const QString& dir ) { _pItem->ydir = dir; _pItem->update(); }
	
	Matrix getXLabel() const { return Matrix( _pItem->pLabelX->handle() ); }
	Matrix getYLabel() const { return Matrix( _pItem->pLabelY->handle() ); }
	Matrix getTitle() const { return Matrix( _pItem->pTitle->handle() ); }
	Matrix getLegend() const { return Matrix( _pItem->pLegend->handle() ); }
	
	Matrix getColorOrder() const { return _pItem->colorOrder; }
	void setColorOrder( const Matrix& m ) { _pItem->colorOrder = m; }
		
	QString getNextPlot() const { return _pItem->nextPlot; }
	void setNextPlot( const QString& s) { _pItem->nextPlot = s; }
	
	Matrix getPosition() const { return _pItem->position; }
	void setPosition( const Matrix& m ) { _pItem->geometryWillChange(); _pItem->position = m; sizeChanged(); }
	
	QString getUnits() const { return _pItem->units; }
	void setUnits( const QString& s ) { _pItem->units = s; }// TODO apply
	
	Matrix getCLim() const { return _pItem->clim; }
	void setCLim( const Matrix& m ) { _pItem->clim = m; }
	
	QString getCLimMode() const { return _pItem->climMode; }
	void setCLimMode( const QString& s ) { _pItem->climMode = s; }
	
	QString getGridLineStyle() const { return _pItem->gridLineStyle; }
	void setGridLineStyle( const QString& s ) { _pItem->gridLineStyle = s; propertyChanged(); }

protected:

	virtual void initProperties();			///< Itnialzies proerties

private slots:

	void plotObjectDestroyed( QObject* object );

private:
	
	void newPlotObject( PlotObject* object );
	
	// data
	
	AxesItem* _pItem;
	
};

}

#endif // QOGRAPHICSAXES_H

// EOF


