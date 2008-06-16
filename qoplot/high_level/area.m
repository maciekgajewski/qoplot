# Copyright (C) 2004 Shai Ayal
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
## @deftypefn {Function File} area (@var{x},@var{y},@var{c})
## area plot: similar to line plot except it is filled to the x-axis
## @end deftypefn
## @seealso{line,plot}

## Author: Shai Ayal <shaiay@users.sourceforge.net>
## Keywords: octplot graphics

function h=area (x,y,c)

  __nxtplt__();

  ## make it a column vector
  x = x(:);
  y = y(:);

  hh = patch ( [ x(1); x; x(1) ] , [ 0; y; 0] , c);

  if nargout,
    h = hh;
  endif

endfunction
