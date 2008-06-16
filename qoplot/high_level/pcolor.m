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
## @deftypefn {Function File} {} @var{h}=  pcolor (@var{x},@var{y},@var{z})
## This function plots a psuedo-color image of the matrix @var{z}
## parameters @var{x} and @var{y} are optional.
##
## the return value @var{h} is the handle of the created surface object
##
## if @var{x} and @var{y} are ommited they are taken as the row/column 
## index of @var{z}. If they are vectors than the surface point z(i,j)
## is plotted at position (x(j),y(i)). If they are matrixes than z(i,j) 
## is plotted at position (x(i,j),y(i,j))
##
## @example
## [x,y]=meshgrid(-3:.1:3, -3:.1:3);
## z = x.*exp(-x.^2 - y.^2);
## pcolor(x,y,z);
## @end example
## @end deftypefn
## @seealso{contour,surface,colormap}

## Author: shaia

function h = pcolor(varargin)

  if (nargin==1)
    z = varargin{1};
    [nr,nc] = size(z);
    x = [];
    y = [];
  elseif (nargin==3)
    x = varargin{1};
    y = varargin{2};
    z = varargin{3};
  else
    error("Wrong number of arguments");
  endif

  __nxtplt__();

## now create the surface
  hh =  surface(x,y,z);
  
  if nargout , 
    h = hh;
  endif

endfunction
