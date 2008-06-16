## Copyright (C) 2006 Michel D. Schmid
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

## author: mds e-mail: michaelschmid@users.sourceforge.net

x = -2.9:0.2:2.9;

h = figure;

subplot(2,3,1);
bar(x,exp(-x.*x));
title("Simple Bar-Plot");


subplot(2,3,2);
h231 = bar(x,exp(-x.*x));
y = exp(-x.*x);
index = find(max(y)==y); # only one value, not the same value
# till 15 digits behind coma!
set(h231(index),'FaceColor',[0.2 0.5 0.7]);
title("Change color of ONE bar");


subplot(2,3,4);
h234 = bar(x,exp(-x.*x));
y = exp(-x.*x);
index = 1:2:length(y); # each second handle
set(h234(index),'FaceColor',[0.2+0.3*index 0.5 0.7]);
title("Change color of some bars");

subplot(2,3,5);
h235 = bar(1:10);
set(h235,'FaceColor',[0.2 0.2 0.9]);
title("Change color of all bars");


subplot(2,3,3);
barh(x,exp(-x.*x));
title("Simple Barh-Plot");

subplot(2,3,6);
h236 = barh(x,exp(-x.*x));
set(h236,'FaceColor',[0.9 0.25 0.5]);
title("Change colors of all barh's");


set(gcf,'Color','w'); # change background color to white