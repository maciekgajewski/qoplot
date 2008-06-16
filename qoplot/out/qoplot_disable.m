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
## @deftypefn {Function File} octplot_disable
## This script disables octplot operation. 
## @end deftypefn
## @seealso{set,get,plot,hold}

## Author: shaia

## this needs a newer version of dispatch

# only run if octplot was ever enabled
if(exist("octplot_config_info","var"))

  dispatch("pause","any");
  dispatch("set","any");
  dispatch("hold","any");
  dispatch("gset","any");
  dispatch("graw","any");
  dispatch("oneplot","any");
  dispatch("clg","any");

  input_event_hook();
  ## kill octplot
  octplot_atexit;
  
  rmpath(octplot_config_info.mpath);
  rmpath(octplot_config_info.opath);
  eval (octplot_config_info.clear_command);
  octplot_config_info.in_use = 0;

endif


 	  	 
