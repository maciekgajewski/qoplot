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
#include "ui_figurewindow.h"

namespace QOGraphics
{

/**
FigureWindow is implementation of figure, using Qt's QMainWindow.
Each window is associated with graphics Figure object.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class FigureWindow : public QMainWindow, protected Ui::FigureWindow
{
	Q_OBJECT
public:

	FigureWindow( QWidget* parent = 0, Qt::WindowFlags flags = 0 );
	virtual ~FigureWindow();

signals:

	void closed();			///< Signals window closing
	
protected:

	// event handlers
	
	virtual void closeEvent( QCloseEvent* event );
};

}; // namespace

#endif // FIGUREWINDOW_H

// EOF


