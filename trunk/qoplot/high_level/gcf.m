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
## @deftypefn {Function File} {@var{h}} = gcf()
## returns the handle of the current figure. If no figure is
## present, creates one; 
##
## @end deftypefn
## @seealso{gca,get}

## Author: Shai Ayal <shaiay@users.sourceforge.net>
## Keywords: octplot graphics

function out = gcf ()

  out = get(0,"currentfigure");
  if(isempty(out))
    clf();
    out = get(0,"currentfigure");
  endif

endfunction

