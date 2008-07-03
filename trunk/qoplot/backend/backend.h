// backend.h, Copyright (C) 2008 Maciek Gajewski <maciej.gajewski0@gmail.com>
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
#ifndef QOGRAPHICSBACKEND_H
#define QOGRAPHICSBACKEND_H

#include <stdio.h>

#include <octave/oct.h>
#include <octave/graphics.h>

namespace QOGraphics
{

class FigureManager;

/**
Octave backend implementation.

@author Maciek Gajewski <maciej.gajewski0@gmail.com>
*/
class Backend : public base_graphics_backend
{
public:
	Backend( FigureManager* manager );
	~Backend();

	bool is_valid (void) const { return true; }
	
	void close_figure (const octave_value& ov) const;
	
	void redraw_figure (const graphics_handle& fh) const;
	
	void print_figure (const graphics_handle& /*fh*/,
				const std::string& /*term*/,
				const std::string& /*file*/, bool /*mono*/,
				const std::string& /*debug_file*/) const
	{
		printf("qoplot: print figure\n");
	}
	
	Matrix get_canvas_size (const graphics_handle& fh) const
	{
		printf("qoplot: get canvas size\n");
		return Matrix();
	}
	
	double get_screen_resolution (void) const;
	
	Matrix get_screen_size(void) const;
	
private:

	FigureManager* _pManager;
};

}

#endif // QOGRAPHICSBACKEND_H

// EOF


