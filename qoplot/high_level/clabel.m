## Copyright (C) 2007 Kai Habel
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
## @deftypefn {Function File} {@var{ht} =} clabel (@var{c}, @var{h})
## Adds contour label to contour or filled contour (contourf) plots. @var{c} 
## is the contour matrix and @var{h} is the graphic object vector as returned
## by contour or contourf respectively.
## @var{ht} is the graphic object vector pointing the text objects.
## @end deftypefn
## @seealso{contour, contourf}

## Author: Kai Habel <kai.habel at gmx.de>

function ret = clabel(c, h)
  # decode contour matrix c
  idx = 1;
  xlim = get(gca, 'Xlim');
  ylim = get(gca, 'Ylim');
  dx = diff(xlim);
  dy = diff(ylim);
  xmin = xlim(1); xmax = xlim(2);
  ymin = ylim(1); ymax = ylim(2);
  xl = xmin + [0.05 0.95] * dx;
  yl = ymin + [0.05 0.95] * dy;
  n = 1;
  while(idx < columns(c))
    lev = c(1, idx);
    len = c(2, idx);
    ct = c(:, idx + 1:idx + len);
    dxy = diff(ct, 1, 2);
    ctlen = sqrt(sumsq(dxy));
    cumlen = cumsum(ctlen / sqrt(dx * dy));
    phi = mod(180 / pi * cart2pol(dxy(1, :), dxy(2, :)) + 90, 180) - 90;
    posval = 1/3 : 1/3 : cumlen(end);
    if length(posval)>0
      posidx = zeros(1, length(posval));
      for k = 1 : length(posval)
        posidx(k) = min(find(posval(k) < cumlen));
      end
      for k = 1 : length(posidx)
        x = ct(1, posidx(k));
        y = ct(2, posidx(k));
	      p = phi(posidx(k));
        h = text(x, y, num2str(lev), 'FontSize', 11, 'Visible', 'Off', 'HorizontalAlignment', 'center', 'Rotation', p);
        hw = get(h, 'WidthHeight');
        pos = get(h, 'Position');
        ## FIXME: the width and heigth of current text should be considered here
        ## to avoid plotting outside the axis area
        if ( (x < xl(2)) & (x > xl(1)) & (y < yl(2)) & (y > yl(1)) )
          set(h, 'Visible', 'On');
          ht(n) = h;
          n = n + 1;
        else
          h = [];
        end
      end
    end
    idx += len + 1;
  end

  if nargout, ret = ht; end

end
