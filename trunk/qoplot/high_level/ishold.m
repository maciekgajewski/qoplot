## Copyright (C) 2006 Shai Ayal
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
## @deftypefn {Function File} {} @var{is} = ishold ()
## Return 1 if the next line will be added to the current plot, or 0
## if the plot device will be cleared before drawing the next line.
## @end deftypefn
## @seealso{hold}

## Author: shaia

function ih = ishold ()

  ## usage:  ih = ishold ()
  ##
  ## 
  tt = get(gca(),"nextplot");
  if (strcmp(tt,"add")),
    ih=1;
  elseif (strcmp(tt,"replace")),
    ih = 0;
  else
    error("illegal value in nextplot");
  end

endfunction