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
## @deftypefn {Function File} {} 
## [@var{ax},@var{hl},@var{hr}]= plotyy 
## (@var{xl},@var{yl},@var{xr},@var{yr},[@var{fl},[@var{fr}]])
##
## Draws two plots on a single graph using seperate y-axes. The optional
## function handles @var{fl} and @var{fr} can be used to draw the left
## and right graphs corrspondingly. The must point to function which 
## are of the form @var{h}=f(@var{x},@var{y}) such as 
## @code{plot}, @code{semilogy}, @code{bar}, etc...
##
## plotyy returns the handles of the created axes in @var{ax} and the 
## handles of the created objects in the left and right axes in @var{hl}
## and @var{hr} respectively.
##
## @end deftypefn
## @seealso{plot,bar,axes}

## Author: shaia


function [_ax,_hl,_hr] = plotyy (xl,yl,xr,yr,fl,fr)

  error(nargchk(4,6,nargin));
  cla();
  if(nargin==4)
    fl=@plot;
    fr=@plot;
  elseif(nargin==5)
    fr=fl;
  endif

  ## create the two plots and axes
  ax(1)=gca();
  hl = fl(xl,yl);
  ax(2)=axes();
  hr = fr(xr,yr);

  ## now make sure they look OK
  set(ax(2),"Position",get(ax(1),"Position"));
  set(ax(2),"Color","none");
  set(ax(2),"YAxisLocation","right");
  set(ax(2),"XTick",[]);
  
  ## get the x-axis to the the same in both axes:
  __drawnow__();
  xrl = get(ax(1),"Xlim");
  xrr = get(ax(2),"Xlim");
  xrange = [min(xrl(1),xrr(1)),max(xrl(2),xrr(2))];
  set(ax(2),"XLim",xrange);
  set(ax(1),"XLim",xrange);

  set(gcf(),"CurrentAxes",ax(1));
  if(nargout)
    _ax = ax;
    _hl = hl;
    _hr = hr;
  endif

endfunction
