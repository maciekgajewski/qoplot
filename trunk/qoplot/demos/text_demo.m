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

## allowed alignments
vertical_alignment={"top","middle","bottom"};
horizontal_alignment={"left","center","right"};

## a nice gray for the reference lines
gray = 0.8*[1,1,1];

## a nice colorpmap for showing off colors
cmap=colormap("jet");

clf();

for va=1:3,
  ## grid lines
  line(va*5*[1,1],[0,20],"color",gray);
  for ha=1:3,
    if (va==1)
      ## grid lines
      line([0,20],ha*5*[1,1],"color",gray);
    endif

    vas = vertical_alignment{va};
    has = horizontal_alignment{ha};

    text(va*5,ha*5,sprintf("%s/%s",vas,has),\
          "VerticalAlignment",vas,\
          "HorizontalAlignment",has,\
          "FontSize",10,\
          "Color","r");
  endfor
endfor


## text angles
for ang = linspace(0,360,7)(1:end-1);
  text(20,22,sprintf("  Angle=%d",ang),\
        "Rotation",ang,\
        "Color",cmap(ang/10+1,:));
endfor

## text fonts
text(1,28,"Font sans","FontName","sans","FontSize",14);
text(1,25,"Font serif","FontName","serif","Fontsize",14);
text(1,22,"Font mono","FontName","mono","Fontsize",14);

title("Text Demo");
axis([0,30,0,30]);
## no ticks
set(gca(),"xtick",[],"ytick",[]);


printf("type text_props for help on text properties\n");

