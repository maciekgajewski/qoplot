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

markers = "+o*.xsd^v><";
cmap=colormap("jet");

clf();
title(sprintf("%d Marker Styles",length(markers)));
for i=1:length(markers),
  h=plot(1:11,[1:11]+2*i,sprintf("-%s;Marker %s;",markers(i),markers(i)));
  
  ## set the face color 
  set(h,"MarkerFaceColor",cmap(i*3,:));
  ## set the linewidth
  set(h,"linewidth",mod(i,3)+1);
  hold on
endfor
hold off
grid("on");
axis([0 15 0 35]);

printf("type line_props for help on line properties\n");

