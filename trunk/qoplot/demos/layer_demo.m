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

## big axes
clf();
cla();
grid("on");

## small axes
axes();
set(gca(),"position",[0.68,0.6,0.2,0.2]);
set(gca(),"color",[0.9,0.9,0.9]);

## ticks are not very nice -- zap them
set(gca(),"xtick",[]);
set(gca(),"ytick",[]);

## make axes bars invisible
set(gca(),"xcolor","none");
set(gca(),"ycolor","none");

## put a nice histogram just to show off
hist(randn(10000,1),15);

## return to big axes
set(gcf(),"CurrentAxes",get(gcf(),"children")(2));

hl=plot(1:10,"r-",\
	10:-1:1,"b-");

hp=patch([4,7,7,4],[4,4,7,7],"c");

hh = get(gca(),"children");

set(hh,"linewidth",3);

title("Two lines behind the patch");
printf("\npress a key to continue\n");
pause();

set(gca(),"children",[hl,hp]);
title("Two lines in front of the patch");
printf("\npress a key to continue\n");
pause();

set(gca(),"children",[hl(1),hp,hl(2)]);
title("red line in front of the patch");
printf("\npress a key to continue\n");
pause();
