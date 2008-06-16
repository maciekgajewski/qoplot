## Copyright (C) 2006 Jorgen Andreas Michaelsen
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
## @deftypefn {Function File} {} box (@var{hstat})
## This function sets the box status for the current axes
## @var{hstat} can be "on" or "off". if used without arguments, toggles
## the box state of the axes.
## @end deftypefn
## @seealso{plot}

## Author: jam 

function box (tp)

  if(nargin==1)
    if(strcmp(tp,"on")),
        set(gca(),"Box","on");
    elseif(strcmp(tp,"off")),
        set(gca(),"Box","off");
    else
        error("Unknown argument");
    endif
  elseif (nargin==0)
    _gca = gca();
    boxstate=get(_gca,"Box");
    if(strcmp(boxstate,"off"))
      set(_gca,"Box","on");
    else
      set(_gca,"Box","off");
    endif
  else
    error("Wrong number of arguments");
  end

endfunction

