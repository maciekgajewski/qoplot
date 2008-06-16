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
## @deftypefn {Function File} @var{h} = pie (@var{x},[@var{explode}])
## draws a pie chart. @var{x} is taken as a vector of percentages. 
## if @code{sum(@var{x})>1}, @var{x} is normalised by it's sum.
## if @var{explode} is given it should be the same length as @var{x}. 
## Slices for which @var{explode} is non zero are offset. pie returns
## the handles of the patch and text object it creates
## @end deftypefn
## @seealso{patch,text}

## Author: Shai Ayal <shaiay@users.sourceforge.net>
## Keywords: octplot graphics

function h=pie (x,xpld)

  error(nargchk(1,2,nargin));
  
  if !ismatrix(x)
    error("X must be a matrix");
  endif

  if (nargin==1)
    xpld = zeros(size(x));
  elseif ismatrix(xpld) && (size(xpld)==size(x))
    xpld = (xpld>0);
  else
    error("EXPLODE must be a matrix of the same size as X");
  endif

  __nxtplt__();
  
  ## TODOSHAIAY
  axes; # this is only here that the next row will work,
  # otherwise the returned matrix co is empty ...
  co = get(gca(),"colororder");
 
  csx = [0;cumsum(x(:))];
  ## normalize if needed
  if (csx(end)>1)
    x /= csx(end);
    csx /= csx(end);
  endif
  csx = csx * 2*pi +pi/2;

  hh = [];

  for i=2:length(csx)
    phi = linspace(csx(i-1),csx(i),max(2,(csx(i)-csx(i-1))/(2*pi/90)));
    xpi = xpld(i-1)*0.1;
    mx = cos(mean(phi));
    my = sin(mean(phi));
    hh = [hh , patch([0 , cos(phi) , 0]*(1 + xpi) + mx*xpi, \
                     [0 , sin(phi) , 0]*(1 + xpi) + my*xpi , \
                     co(mod(i-2,length(co))+1,1:3))];
    hh = [hh , text((1.2+2*xpi)*mx,(1.2+2*xpi)*my,sprintf("%d%%",round(100*x(i-1))))];
  endfor

  axis("off");
  axis("equal");

  if nargout ,
    h = hh;
  endif
endfunction
