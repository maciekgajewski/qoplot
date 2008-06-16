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
## @deftypefn {Surface object properties} {} 
## OctPlot Surface object properties. Property names are case insensitive.
## 
## @noindent Default values for these properties
## can be set in the root (0) object by adding "DefaultSurface" in front of
## the property name. i.e.
## @example
## set(0,"DefaultSurfaceClipping","off");
## @end example
## will set the default surface clipping to off
##
## @noindent Supported properties:
##
## @table @samp
## @item Parent [handle]
## Figures parent (root)
## @item Type [string]
## "Surface"
## @item Visible [Radio]
## Surface visibility. can be one of "on" or "off"
## @item Clipping [Radio]
## Surface clipping. Values: "on" "off"
## @item XData,YData,ZData [Matrix]
## x,y,z  coordiantes. The surface is defined by (x(i,j),y(i,j),z(i,j)). 
## They must be of the same size
## @end table
## @end deftypefn
##
## @seealso{set,get,pcolor,colormap}

## Author: shaia

help surface_props
