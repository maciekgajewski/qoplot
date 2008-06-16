## Copyright (C) 2006 Michel D. Schmid
##
## This file is part of OctPlot.
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
## @deftypefn {Function File} {} @var{h} = pareto(@var{y}, [@var{x}], [@var{names}])
## Pareto display the values in vector @code{y} as bars in descending order.
##
## Example 1:
## @example
## y = [1 2 7 4 3];
## pareto(y)
## @end example
## @noindent
##
## Example 2:
## @example
## y = [1 2 7 4 3];
## x = @{"1st","2nd","7th","4th","3rd"@};
## h = pareto(y,x)
## @end example
## @noindent
##
## @end deftypefn
##
## @seealso{bar,barh}

## Author: mds

function h = pareto(varargin)

  # check input args
  error(nargchk(1,2,nargin))

  [x,y] = checkParetoArgs(varargin{:})

  hLeft = gca;
  hRight = axes;
  set(hRight,"Color","none");
  set(hRight,"XTick",[]); # removes XTicks from right side axes
  set(hRight,"YAxisLocation","right");
  set(hRight,"YTick", []);

  ymax = sum(y);
  # now check how much ticks are used
  % this part can be maybe deleted if ticks calculation will work...
  % division 5
  if ( !mod(ymax,5) ) # if "zero"
    numDistForYTicks = 5;
  elseif ( !mod(ymax,2) )
    numDistForYTicks = 2;
  endif

  # on the left axes, bars are drawn
  set(gcf(),"CurrentAxes",hLeft);
  if (nargout>0)
    h = bar(y);
  else
    bar(y);
  endif

  vecXTick = get(hLeft,"XTick");
  nNames = findstr(x,"|");
  set(hRight,"XTickLabelMode","manual");
  if (length(vecXTick)>length(nNames))
    vecXTick = 1:1:length(nNames)+1;
    set(hLeft,"XLim",[0 max(vecXTick)+(vecXTick(1)-0)]);
    set(hLeft,"XTick",vecXTick);
  endif
  set(hLeft,"YLim",[0 ymax]);
  set(hLeft,"YTick",0:numDistForYTicks:ymax);
  set(hLeft,"XTickLabel",x);

  YTicksLeftSide = get(hLeft,"YTick")
  nYTicks = length(YTicksLeftSide)
  yTicksRightSide = linspace(0,100,nYTicks);
  yTicksRightSide = (round(100*yTicksRightSide)/100);
  set(hRight,"YLim",[0 100]);
  set(hRight,"YTick",yTicksRightSide);
  yRight = [];
  for (i = 1:1:nYTicks)
    if (i < nYTicks)
      yRight = [yRight num2str(yTicksRightSide(i)) "%|"];
    else
      yRight = [yRight num2str(yTicksRightSide(i)) "%"];
    endif
  endfor
  set(hRight,"YTickLabel",yRight);

  ## calc how much percent are done ...

  for i = 1:1:(length(y))
    if (i==1)
      yValRight(i) = 100/ymax*y(i);
    else
      yValRight(i) = 100/ymax*(y(i))+yValRight(i-1);
    endif
  endfor

  set(hRight,"XLim",get(hLeft,"XLim"));
  set(gcf(),"CurrentAxes",hRight);
  hold on
  plot(vecXTick,yValRight,"r")


  function [x,y] = checkParetoArgs(varargin)

    x = [];
    y = varargin{1};
    order = [];
    yTemp = varargin{1};
    y = fliplr(sort(y)); # sort in descending order
    nRuns = length(y);
    for i = 1:1:nRuns
      [a,b] = find(yTemp==y(i));
      order = [order b];
      if (i<nRuns)
        x = [x num2str(b) "|"];
      else
        x = [x num2str(b)];
      endif
    endfor
    if (nargin==2)
      if iscell(varargin{2})
        nNames = length(varargin{2});
        xx = varargin{2};
        zz = [];
        for (i=1:1:nNames)
          if (i<nNames)
            zz = [zz xx{order(i)} "|"];
          else
            zz = [zz xx{order(i)}];
          endif
        endfor
        x = zz;
      elseif isnumeric(varargin{2})
        if isvector(varargin{2})
          nNames = length(varargin{2});
          xx = varargin{2};
          zz = [];
          for (i=1:1:nNames)
            if (i<nNames)
              zz = [zz num2str(xx(order(i))) "|"];
            else
              zz = [zz num2str(xx(order(i)))];
            endif
          endfor
          x = zz;
        endif
      endif # iscell(varargin{2})
    endif # elseif (nargin==2);

  endfunction

endfunction
