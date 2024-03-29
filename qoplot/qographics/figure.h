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

#include "object.h"
#include "figurewindow.h"
#include "color.h"
#include "enum.h"

namespace QOGraphics
{

class Axes;

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
	Q_PROPERTY( QOGraphics::Matrix CurrentAxes READ getCurrentAxes WRITE setCurrentAxes );
	Q_PROPERTY( QOGraphics::Matrix ColorMap READ getColorMap WRITE setColorMap );
	Q_PROPERTY( QString PaperType READ getPaperType WRITE setPaperType );
	Q_PROPERTY( QString PaperOrientation READ getPaperOrientation WRITE setPaperOrientation );
public:
	
	// Enums
	
	enum PrintDevice  { Ps = 1, Eps, Pdf, Png, Jpeg, Svg }; ///< Print devices
	
	// construction / destruction
	
	Figure( Root* root, Handle handle, QObject* parent );
	virtual ~Figure();
	
	// window operations
	
	/// Raises window
	void raise() { _window.raise(); }
	
	/// Adds axes to figure
	Axes* createAxes( Handle h );
	
	QGraphicsScene* scene(){ return & _window.scene; }		///< Returns graphics scene to which items are added
	const Matrix& colorMap() const { return _colorMap; }
	
	/// Redraws scene
	void redraw();
	
	/// Removes all axes
	void clear();
	
	/// Prints to file
	void print( const QString& fileName, int device, int resolution, QSize size = QSize() );
	
	// properties
	
	virtual QString getType() const { return "figure"; }
	
	QVariant getColor() const { return _backgroundColor.toVariant(); }
	void setColor( const QVariant& color );
	
	Matrix getPosition() const;
	void setPosition( const Matrix& pos );
	
	Matrix getCurrentAxes() const;
	Handle currentAxes() const { return _currentAxes; }
	void setCurrentAxes( const Matrix&m );

	Matrix getColorMap() const { return _colorMap; }
	void setColorMap( const Matrix& m ) { _colorMap = m; }
	
	QString getPaperType() const { return _paperType; }
	void setPaperType( const QString& s ) { _paperType = s; }
	
	QString getPaperOrientation() const { return _paperOrientation; }
	void setPaperOrientation( const QString& s ) { _paperOrientation = s; }


private slots:

	void windowClosed();			//!< Handles window closing
	void windowResized();			//!< Handle window resize
	
	//! Handles axes deletion
	void axesDeleted( QObject* pAxes );

private:
	
	void initColorMap();
	void printToPixmap( const QString& fileName, const char* format, int resolution = 0, QSize size = QSize() );
	void printToPrinter( const QString& fileName, int format, int resoultion = 0 );
	void printToSvg( const QString& fileName );
	
	// Data
	
	FigureWindow _window;			///< Actual window
	Color		_backgroundColor;	///< Figure's background color
	Handle		_currentAxes;		///< Current axes
	Matrix		_colorMap;			///< Color map
	Enum		_paperType;			///< Paper format used for printing
	Enum		_paperOrientation;	///< Paper orientation: {portrait}|landscape
	
};

}; // namespace

#endif // FIGURE_H

// EOF


