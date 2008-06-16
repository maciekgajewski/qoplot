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
## @deftypefn {Function File} {} @var{h} = quiver ([@var{x},@var{y}],@var{u},@var{v},[@var{scale}])
## This function plots the velocity vectors at positions @var{x},@var{y} and
## directions @var{u},@var{v}. 
## parameters @var{x}, @var{y} and @var{scale} are optional.
##
## The return value @var{h} is a vector of the handles of the lines plotted
##
## if @var{x} and @var{y} are ommited they are taken as the row/column indices.
##
## quiver scales the resulting lines so that they will fit nicely. This
## scaling can be changed by using the optional @var{scale} parameter.
## if @var{scale} is zero, the lines are not scaled, otherwise their length
## is multiplied by @var{scale}
##
## @example
## [x,y] = meshgrid(-2:0.1:2);
## z = x.* exp(-x.^2-y.^2);
## [dx,dy] = gradient(z,0.1,0.1);
## quiver(x,y,dx,dy);
## @end example
##
## @end deftypefn
## @seealso{contour,line,plot}

## Author: shaia

function ret = quiver(varargin)

  scale = 1;
  if(nargin>=2 & nargin<=3)
    u=varargin{1};
    v=varargin{2};
    x=1:length(u(:));
    y=1:length(u(:));
    if(nargin==3)
      scale = varargin{3};
    endif
  elseif(nargin>=4 & nargin<=5)
    x=varargin{1};
    y=varargin{2};
    u=varargin{3};
    v=varargin{4};
    if(nargin==5)
      scale = varargin{5};
    endif
  else
    error("Must have 2-5 input arguments");
  endif

  if(~all(size(u)==size(v)))
    error("u and v must have the same size");
  endif

  __nxtplt__();


  if(scale)
    ## normalize the vectors:
    max_length = min( min(min(diff(x'))) , min(min(diff(y))) );
    u = u/max(max(u))*max_length*scale;
    v = v/max(max(v))*max_length*scale;
  endif

  xx=x(:);
  yy=y(:);
  lnx = [xx,xx+u(:)]';
  lny = [yy,yy+v(:)]';

  h = zeros(size(lnx,2),1);
  for ii=1:size(lnx,2),
    h(ii) = line(lnx(:,ii),lny(:,ii),\
		 "arrowhead",">",\
		 "arrowwidth",0.2,\
		 "arrowlength",0.8,\
		 "arrowratio",0.5);
  endfor

  if nargout , ret = h; endif

endfunction


