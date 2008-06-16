## Copyright (C) 2003 Shai Ayal
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
## @deftypefn {Function File} {@var{h}} = surface (@var{x},@var{y},@var{z},@var{args})
## This function produces a surface object. 
## @var{z} should be a matrix. @var{x} and @var{y} can be empty, vectors or
## matrixes.
##
## The remainder of the arguments, if any, are taken as property value pairs
## and are applied to the surface
##
## surface returns the handle of the surface created
## @end deftypefn
## @seealso{set,get,pcolor}

## Author: Shai Ayal <shaiay@users.sourceforge.net>
## Keywords: octplot graphics

function handle = surface (x,y,z,varargin)

  if ~ismatrix(z)
    error("z must be a matrix");
  endif

  [nr,nc] = size(z);
  if isvector(x),
    if(length(x)~=nc)
      error("length(x) must be size(z,2)");
    endif
  elseif ismatrix(x),
    if any(size(x) - size(z)),
      error("x must have the same size as z");
    endif
  endif
  if isvector(y),
    if(length(y)~=nr)
      error("length(y) must be size(z,1)");
    endif
  elseif ismatrix(y),
    if any(size(y) - size(z)),
      error("y must have the same size as z");
    endif
  endif

  _h = octplot_command("surface",x,y,z){1};

  if length(varargin)
    set(h,varargin{:});
  endif

  if nargout, handle=_h; endif
endfunction
