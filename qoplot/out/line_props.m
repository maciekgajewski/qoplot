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
## @deftypefn {Line object properties} {} 
## OctPlot line object properties. Property names are case insensitive
## 
## @noindent Default values for these properties
## can be set in the root (0) object by adding "DefaultLine" in front of
## the property name. i.e.
## @example
## set(0,"DefaultLineLineWidth",3);
## @end example
## will set the default line width to 3
##
## @noindent Supported properties:
##
## @table @samp
## @item LineWidth [scalar]
## Line width in pixels
## @item Clipping [radio]
## Will the line be clipped to the axes ? can be either one of "on" or "off"
## @item Color [colspec]
## Line color. can be either one of "r","g","b","c","m","y","w","k"
## or an [r,g,b] vector
## @item LineStyle [linespec]
## Line style. Can be one of "-","--",":","-.","none"
## @item Marker
## Line marker style. Can be one of "none","+","o","*",".","x"
## @item MarkeFaceColor [colspec]
## Line marker face color
## @item MarkeEdgeColor [colspec]
## Line marker edge color
## @item MarkerSize [scalar]
## Line marker size in pixels
## @item Parent [handle]
## Line's parent axes
## @item XData [vector]
## @item YData [vector]
## Line's data. XData can be empty, in which case YData is plotted against
## it's index. If any of the elements (either in Xdata or Ydata)
## is "NaN", that element is treated as a missing value and not plotted.
## @item ArrowHead [radio] *
## controls drawing of arrowheads at the edges fo the line. Can one of "none", "<",">","<>"
## @item ArrowLength [scalar] *
## @item ArrowWidth [scalar] *
## @item ArrowRatio [scalar] *
## control the shape of the arrowhead
## @item Visible [Radio]
## Line's visibility. Can be one of "on" or "off"
## @item Type [string]
## "Line"
## @item Label [text]
## handel to a text object containing the lines label in the legend
## @end table
##
## Items labeled with * are not compatible with the leading brand
## @end deftypefn
## @seealso{set,get,line}

## Author: shaia

function line_props
  help line_props
endfunction
