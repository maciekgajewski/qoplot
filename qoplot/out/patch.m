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
## @deftypefn {Function File} {@var{h}} = patch (@var{x}, @var{y}, @var{c}, @var{args})
## This function adds a new patch object with vertices (@var{x}, @var{y}) and color @var{c} to
## the current axes.
## For an uniform colored patch, @var{c} can be given as [r, g, b]-vector, scalar value refering
## to the current colormap, or single character (e.g. 'r' for red).
##
## The remainder of the arguments, if any, are taken as property value pairs
## and are applied to the patch
##
## patch returns the handle of the patch object created
## @end deftypefn
## @seealso{set, get}

## Author: Shai Ayal <shaiay@users.sourceforge.net>
## Keywords: octplot graphics

function ret = patch (x, y, c, varargin)

  if (size(x) != size(y))
    usage('size of x and y must be equal')
  end
  
  # if x and y are vectors, make sure there are colums
  if min( size(x)) == 1
  	l = length(x);
  	x = reshape( x, l, 1 );
  	y = reshape( y, l, 1 );
  endif

  handle = qoplot_command('patch', x, y ){1};
  if (length(c) == 1)
      # have color string
      set(handle, "FaceColor", c);
  endif
  
 if length(varargin),
    set(handle, varargin{:});
  endif
  if nargout, ret = handle; endif
endfunction

