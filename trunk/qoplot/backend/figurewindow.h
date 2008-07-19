// figurewindow.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef FIGUREWINDOW_H
#define FIGUREWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QDateTime>

#include "octave/oct.h"
#include "octave/graphics.h"

#include "uiitem.h"

#include "ui_figurewindow.h"

namespace QOGraphics
{

/**
FigureWindow is implementation of figure, using Qt's QMainWindow.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class FigureWindow : public QMainWindow, public Ui::FigureWindow
{
	Q_OBJECT
public:

	FigureWindow( double handle );
	virtual ~FigureWindow();
	
	/// Returns object's properties
	figure::properties* properties() const;
	
	double handle() const { return _handle; }

	/// Message from outer world - child added
	virtual UIItem* addChild( double h );
	
	/// Message from outer world - property changed
	virtual void propertyChanged( const QString& name );

	// colormap access
	
	/// Returns direct colro from colormap, identified by index.
	QRgb getDirectColor( int index );	
	
	/// Returns scaled color, using min and max limits.
	QRgb getScaledColor( double min, double max, double value );
	
signals:

	void closed();			///< Signals window closing
	void resized();			///< Sigals window size change
	
protected:

	// event handlers
	
	virtual void closeEvent( QCloseEvent* event );
	virtual void showEvent( QShowEvent* event );
	virtual void resizeEvent( QResizeEvent* event );
	virtual void moveEvent( QMoveEvent * event );

private:

	/// Master method called when properties has changed
	void propertiesChanged();
	
	void updateActualToPosition();	///< Updates geometry to 'position' and 'units' property
	void updatePositionToActual();	///< Udates 'position' property to geometry
	void updateChildren();	///< Updates child elements
	
	void updateChildrenSizes();	///< Updates sizes of child elements
	
	UIItem* createItem( double h, base_properties* pProps );
	
	// data
	
	QGraphicsScene		_scene;				///< Scene on which child elemens are painted
	
	QMap<double, UIItem*> _children;		///< Map faciliting updating children
	double _handle;							///< Handle
	
	/// Stores time of last position property change.
	/// Used to prevent reverse setting for some time.
	///\todo this is hack. Not so ugly, bu still a hack.
	QDateTime	_lastPositionPropertyChange;
};

}; // namespace

#endif // FIGUREWINDOW_H

// EOF


