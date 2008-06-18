// figure.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef FIGURE_H
#define FIGURE_H

#include <object.h>
#include "figurewindow.h"

namespace QOGraphics
{

/**
Figure object represents UI window. It uses FigureWindow as actula UI element.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class Figure : public Object
{
	Q_OBJECT
	
	// Properties
	Q_PROPERTY( QOGraphics::Matrix Position READ getPosition WRITE setPosition )
	Q_PROPERTY( QVariant Color READ getColor WRITE setColor )
	
public:
	
	// construction / destruction
	
	Figure( Root* root, Handle handle, QObject* parent );
	virtual ~Figure();
	
	// window operations
	
	/// Raises window
	void raise() { _window.raise(); }
	
	// properties
	
	virtual QString getType() const { return "figure"; }
	
	QVariant getColor() const { return "w"; } // TODO
	void setColor( const QVariant& color ) {} // TODO
	
	Matrix getPosition() const;
	void setPosition( const Matrix& pos );

private slots:

	void windowClosed();			//!< Handles window closing

private:

	// Data
	
	FigureWindow _window;			///< Actual window
};

}; // namespace

#endif // FIGURE_H

// EOF


