## Copyright (C) 2005 Shai Ayal
##
## This program is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2, or (at your option)
## any later version.
##
## OctPlot is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with OctPlot; see the file COPYING.  If not, write to the Free
## Software Foundation, 59 Temple Place - Suite 330, Boston, MA
## 02111-1307, USA.

## -*- texinfo -*-
## @deftypefn {Function File} {} @var{is}= iscolorspec (@var{cd})
##
## Eight color specifiers are defined:
## @example
## "r":	red
## "g":	green
## "b":	blue
## "c":	cyan
## "m":	magenta
## "y":	yellow
## "w":	white
## "k":	black
## @end example
##
## Also possible are colors defined by the RGB-triplet or RGBA
## quartet
## @example
## [1 0 0]
## [1 0 1]
## [0.1 0.5 0.75]
## [0 0.25 0.5]
## [0 1 1 0.5]
## @end example
## The RGBA values must be in the range of 0 to 1
## , including boundaries.
##
## @end deftypefn
## @seealso{patch,line,set,get}

## Author: shaia

function is=iscolorspec(cs)
	is = 0;
	if( ischar(cs) )
		if( length(cs)==1)
			if( ~isempty(findstr('rgbcmywk',cs) ))
				is = 1;
			endif
		endif
	elseif( isvector(cs) )
		if( length(cs)==3 |  length(cs)==4 )
			if( max(cs)<=1 & min(cs)>=0 )
				is = 1;
			endif
		endif
	endif
endfunction
