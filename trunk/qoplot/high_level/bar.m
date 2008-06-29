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
## @deftypefn {Function File} {} @var{h}= bar ([@var{x}],@var{y},[@var{width}|@var{'color'}|@var{'plottype'}])
## Draws a bar graph. Graphs the rows of @var{y}. The default width is 0.8
## The default color is taken from axes 'ColorOrder' property.
## Returns in @var{h} the handles of the patch objects used to draw the
## bars.
##
## @example
## x = 1:10;
## bar(x);
## @end example
## @noindent
## plots 10 bars with hights from 1 to 10
##
## @example
## x = 1:10;
## y = ones(1,length(x))*2.*x;
## bar(x,y);
## @end example
## @noindent
## plots 10 bars with hights from 2 to 20
## 
## @example
## x = 1:10;
## y = ones(1,length(x))*2.*x;
## h = bar(x,y,'b');
## @end example
## @noindent
## plots 10 bars with hights from 2 to 20
## color is blue.
##
## @example
## x = 1:10;
## y = ones(1,length(x))*2.*x;
## h = bar(x,y,0.6);
## @end example
## @noindent
## plots 10 bars with hights from 2 to 20
## bar width is 0.6.
##
## @example
## x = 1:10;
## y = ones(1,length(x))*2.*x;
## h = bar(x,y,0.6,'m');
## @end example
## @noindent
## plots 10 bars with hights from 2 to 20
## bar width is 0.6, bar color is magenta
##
## @example
## x = 1:10;
## y = ones(1,length(x))*2.*x;
## h = bar(x,y,0.6,[1 0 1]);
## @end example
## @noindent
## plots 10 bars with hights from 2 to 20
## bar width is 0.6, bar color is magenta
## 10 handles will be returned
##
## @end deftypefn
## @seealso{barh,patch,area}

## Author: shaia

function h = bar(varargin)

  hh = __bar(varargin{:},'bar');

  if nargout,
    h = hh;
  endif

endfunction
