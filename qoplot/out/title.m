## Copyright (C) 2004 Shai Ayal
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
## @deftypefn {Function File} {@var{h}}=title(@var{label})
## sets the title of the current axis to @var{label}  
## Returns a handle to the text used as title
## @end deftypefn
## @seealso{set}

## Author: Shai Ayal <shaiay@users.sourceforge.net>
## Keywords: octplot graphics
function h=title(label)
  tith = get(gca(),"title");
  set(tith,"string",label);
  set(tith,"FontSize",13);
  if nargout ,
    h = tith;
  endif
endfunction
