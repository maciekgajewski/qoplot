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
## @deftypefn {Function File}  caxis (@var{CV})
## Sets the color limits of the current axis to the values given
## by the vector @var{CV} = [min max]. The 'climmode' of the current
## axis is set to manual.
## caxis('auto') return to an automatic setting of the color limits
## caxis('manual') sets a manual mode.
## caxis without arguments returns the current color limits.
## @end deftypefn
## @seealso{gca, colorbar}

## Author: Kai Habel <kai.habel at gmx.de>

function varargout = caxis(V)

  if (nargin == 0)
    out = get(gca(), 'Clim');
    varargout{1} = out;
  elseif (nargin == 1)
    if (isstr(V))
      if (strcmp(V, 'manual'))
        set(gca(), 'Climmode', 'manual');
      elseif (strcmp(V, 'auto'))
        set(gca(), 'Climmode', 'auto');
      else
        print_usage();
      endif
    elseif (isreal(V))
      if (length(V) == 2)
        set(gca(), 'Climmode', 'manual');
        set(gca(), 'Clim', V);
      else
        print_usage();
      endif
    else
      print_usage();
    endif
  endif
  h = findobj(gcf(),'tag','colorbar')
  if (h)
    ## FIXME: A complete redraw should not
    ## be needed here, but otherwise the
    ## colorbar is not updated in any case
    octplot_redraw();
    colorbar;
  end
endfunction

