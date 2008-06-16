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
## @deftypefn {Function File} {}@var{[xx,nn]} = hist (@var{y}, [@var{x}], [@var{nBins}], [@var{color}], [@var{norm}])
## Produce histogram counts or plots.
##
## With one vector input argument, plot a histogram of the values with
## 10 bins.  The range of the histogram bins is determined by the range
## of the data.
##
## Example 1:
## @example
## x = 1:10;
## hist(x);
## @end example
## @noindent
##
## Given a second scalar argument, use that as the number of bins.
##
## Example 2:
## @example
## x = 1:10;
## hist(x,5);
## @end example
## @noindent
##
## Given a second vector argument, the use of this vector depends on the
## content data:
## If the data are no color specifiers, the data will be used as the centers of the bins,
## with the width of the bins determined from the adjacent values in
## the vector.
##
## Example 3:
## @example
## x = 1:10;
## hist(x,[2 5 9]);
## @end example
## @noindent
## This will create a histogram with 3 bins and the bin center at 2 5 and 9!
##
## Example 4:
## @example
## x = 1:10;
## hist(x,[0 0.5 0.9]);
## @end example
## @noindent
## In this case, the second vector will be used as color specifier.
##
## Example 5:
## @example
## x = 1:10;
## hist(x,[0 0.5 0.9],[2 5 9]);
## @end example
## @noindent
## A valid combination of example 3 & 4!
##
## Example 6:
## @example
## x = 1:10;
## hist(x,[0 0.5 0.9],[2 5 9],3);
## @end example
## @noindent
## The last argument, in this case, is the "normalizer". This means, the histogram
## will be drawn, that the sum of the bins are 3
##
## Example 7:
## @example
## x = 1:10;
## hist(x,[0 0.5 0.9],8,3);
## @end example
## @noindent
## This is a histogram with data x, color [0 0.5 0.9], 8 bins, normalized with 3
##
## A lot of other combinations are also allowed. But if more as one scalar is defined,
## the first one will be the number of bins always, the second scalar is the normalizer.
##
## Extreme values are lumped in the first and last bins.
##
## With two output arguments, produce the values @var{nn} and @var{xx} such
## that @code{bar (@var{xx}, @var{nn})} will plot the histogram.
## @end deftypefn
##
## @seealso{histh,bar,barh}

## Author: Michel D. Schmid <michaelschmid@users.sourceforge.net>

function [nn, xx] = hist (varargin)

  error(nargchk(1,4,nargin))
  
  if (nargout == 2)

    [nn, xx] = __hist(varargin{:},"hist");
  elseif (nargout == 1)
    nn = __hist(varargin{:},"hist");
  else
    __hist(varargin{:},"hist");
  endif

endfunction
