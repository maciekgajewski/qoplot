## Copyright (C) 2006  Kai Habel
##
## This file is part of octplot.
##
## Octave is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2, or (at your option)
## any later version.
##
## Octave is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with Octave; see the file COPYING.  If not, write to the Free
## Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
## 02110-1301, USA.

## -*- texinfo -*-
## @deftypefn {Function File}  shading (@var{m})
##
## Sets the shading of a surface. Valid arguments are "flat", "interp", or "faceted"
##
## @example
## shading ("interp")
## @end example
##
## @end deftypefn

function shading(mode)
  hv = get(gca(),'Children');
  for n = 1:length(hv) 
    h = hv(n);
    if strcmp(get(h,'Type'),"Surface")
      if strcmp(mode,"flat") 
        set(h,'FaceColor','flat');
        set(h,'EdgeColor',"none");
      elseif strcmp(mode,"interp")
        set(h,'FaceColor','interp');
        set(h,'EdgeColor',"none");
      elseif strcmp(mode,"faceted")
        set(h,'FaceColor','flat');
        set(h,'EdgeColor',[0 0 0]);
      else
        error("unknown argument")
      endif
    endif
  endfor
endfunction
