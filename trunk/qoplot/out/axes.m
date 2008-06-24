## Copyright (C) 2003 Shai Ayal
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
## @deftypefn {Function File} {@var{h}} = axes (@var{args})
## Creates a new axes
## returning the handle. 
##
## Arguments, if any, are taken as property value pairs
## and are applied to the axes
##
## @end deftypefn
## @seealso{gca,axes_props}

## Author: Shai Ayal <shaiay@users.sourceforge.net>
## Keywords: octplot graphics
function out = axes(varargin)
  
  if length(varargin) == 1
    # first argin is a handle, use it to set current axes
    h = varargin(1){1}
    if ishandle( h )
    	set(gcf,'CurrentAxes',h);
	else
		usage("axes(h) or axes([prop,value,...])");
	endif
  else
	out = qoplot_command("axes"){1};
	  if length(varargin),
    	set(out,varargin{:});
  	endif
  endif
endfunction
