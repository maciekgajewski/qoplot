## Copyright (C) 2006 Shai Ayal
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
## @deftypefn {Plotting engine} octplot
## Octplot provides quality 2D graphics for octave. Ocplot can display
## graphics on screen and produce quality PS/PDF/PNG hard-copy.
##
## To switch between Octplot and other plotting engines, issue one of the
## follwing commands: 
##
## octplot_enable , octplot_disable, octplot_toggle
##
## Octplot's low-level graphic elements are object: Each graphical object
## has properties determining how it is displayed. Each object has a
## unique numerical identifier called "handle" which can be used to
## read/write it's properties using the @code{get}/@code{set} functions
## respectively. The objects are arranged in a hierarchical tree-like
## structure with the root object given the handle 0.
##
## The objects available in Octplot are:
## @itemize @bullet
## @item root
## @item figure
## @item axes
## @item line
## @item surface
## @item patch
## @item text
## @item legend
## @end itemize
##
## for a listing of an object's properties, use
## @example
## get(h) 
## @end example
## where @code{h} is the object's handle. 
##
## for help on the properties, use
## @example
## help XXX_props 
## @end example 
## where XXX is the object name.
##
## Keyboard and Mouse in the octplot window
##
## @itemize @bullet
## @item left mouse:
## @itemize -
## @item drag to zoom 
## @item double click to copy current coordinates to clipboard
## @end itemize
## @item right mouse: click to unzoom
## @item a: autoscale
## @item g: toggle grid
## @end itemize
## @end deftypefn
## @seealso{plot,bar,pcolor,print}

## Author: shaia


function octplot ()
  help octplot
endfunction
