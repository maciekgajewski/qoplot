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
## @deftypefn {Patch object properties} {} 
## OctPlot patch object properties. Property names are case insensitive
## 
## @noindent Default values for these properties
## can be set in the root (0) object by adding "DefaultPatch" in front of
## the property name. i.e.
## @example
## set(0,"DefaultPatchLineWidth",3);
## @end example
## will set the default line width to 3
##
## @noindent Supported properties:
##
## @table @samp
## @item LineWidth [scalar]
## Edge linewidth in points
## @item Clipping [radio]
## Will the patch be clipped to the axes ? can be either one of "on" or "off"
## @item EdgeColor [colspec]
## Edge color. can be either one of "r","g","b","c","m","y","w","k"
## or an [r,g,b] vector
## @item FaceColor [colspec]
## Face color. can be either one of "r","g","b","c","m","y","w","k"
## or an [r,g,b] vector
## @item LineStyle [linespec]
## Edge linestyle. Can be one of "-","--",":","-.","none"
## @item Parent [handle]
## Patch's parent axes
## @item XData [matrix]
## @item YData [matrix]
## Patch's data. XData and YData should be the same size
## @item Visible [Radio]
## Patch's visibility, can be one of "on" or "off"
## @item Type [string]
## "Patch"
## @end table
## @end deftypefn
##
## @seealso{set,get,patch}

## Author: shaia


function patch_props
  help patch_props
endfunction

