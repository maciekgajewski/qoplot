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
## @deftypefn {Legend object properties} {} 
## OctPlot line object properties. Property names are case insensitive
## 
## @noindent Default values for these properties
## can be set in the root (0) object by adding "DefaultLine" in front of
## the property name. i.e.
## @example
## set(0,"DefaultLegendClipping","off");
## @end example
## will set the default value of the "clipping" property of all newly
## created legend objects to "off"
##
## @noindent Supported properties:
##
## @table @samp
## @item Clipping [radio]
## Will the legend be clipped to the axes ? can be either one of "on" or "off"
## @item FontName [radio]
## The labels fontname
## @item FontSize [scalar]
## The labels fontsize
## @item Color [color]
## The labels text color
## @item EdgeColor [color or 'none']
## The legend box's edgecolor
## @item FaceColor [color]
## The legend box's face color
## @item FaceAlpha [0-1]
## The legend box's face alpha (opacity)
## @item Location [radio]
## Specifies the textbox location. Can be one of the 8 major compass
## directiona, abbreviated or not (i.e northwest or nw). Default is NE.
## @end table
## @end deftypefn
## @seealso{set,get,legend,text_props,patch_props}

## Author: shaia

help legend_props
