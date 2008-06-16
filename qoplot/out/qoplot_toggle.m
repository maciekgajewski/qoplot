## Copyright (C) 2006 Tormod Volden
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
## @deftypefn {Function File} toggle_octplot
## This script toggles octplot operation. 
## @end deftypefn
## @seealso{set,get,plot,hold}

## Author: Tormod Volden

if( ~exist("octplot_config_info","var"))
  octplot_enable
elseif(octplot_config_info.in_use==0)
  octplot_enable
else
  octplot_disable
endif


 	  	 
