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
## @deftypefn {Function File} {}  colorbar ()
## Adds a colorbar to the side of the current axis
## @end deftypefn
## @seealso{pcolor,colormap}

## Author: shaia

function colorbar()
  ca = gca();
  if (length(ca) == 0)
    # we have no axes object in current
    # figure so add a new one
    ca = axes;
  end
  cpos = get(ca, "position");
  npcl = get(ca, "clim");
  if ( __figure_has_colorbar__() )

    ch = get(gcf(),"Children");
    for i = 1 : length(ch)
      try 
        if (strcmp(get(ch(i), "Type"), "axes") & strcmp(get(ch(i),"Tag"), "colorbar"))
          na = ch(i);
          set(gcf(),"currentaxes",na);
        end
      end
    end
  else
    npos = cpos .* [1, 1, 0.8, 1]';
    bpos = cpos .* [0, 1, 0.1, 1]' + [cpos(1) + 0.9 * cpos(3), 0, 0, 0]';

    set(ca, "position", npos);
    na = axes();
    set(na, "position", bpos);
  end
    cm = get(gcf(),"colormap");
    rcm = size(cm, 1);

    set(na, "clim", [1, rcm]);

    x = [0; 1] * ones(1, rcm);
    y = ones(2, 1) * linspace(npcl(1), npcl(2), rcm);
    z = ones(2, 1) * linspace(1, rcm, rcm);

    ## FIXME: this should be replaced with an
    ## image object, if available. [Kai]
    pcolor(x,y,z);
    axis([0 1 npcl(1) npcl(2)]);
    set(gca(),"xtick",[]);
    set(gca(),"Tag","colorbar");
    set(gcf(),"currentaxes",ca);
endfunction

function ret = __figure_has_colorbar__()
  ch = get(gcf(),"Children");
  ret = false();
  for i = 1 : length(ch)
    try 
      if (strcmp(get(ch(i), "Type"), "axes") 
            & strcmp(get(ch(i), "Tag"), "colorbar"))
        ret = true();
      end
    end
  end
end
