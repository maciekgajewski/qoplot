## Copyright (C) 2004 Shai Ayal
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
## @deftypefn {Function File} {@var{h}} = xlabel(@var{label},@var{args})
## sets the xlabel of the current axis to @var{label} and returns
## the handle to the text object used as label.
## Other arguments are taken as property pairs.
## @end deftypefn
## @seealso{set}

## Author: Shai Ayal <shaiay@users.sourceforge.net>
## Keywords: octplot graphics

function h=ylabel(label,varargin)

  hnd = get(gca(),"ylabel");
  set(hnd,"string",label);
  set(hnd,"rotation",90);
  if length(varargin),
    set(hnd,varargin{:});
  endif

  if nargout,
    h=hnd;
  endif
endfunction
