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

clf();

## signal parameters
t=[0:0.001:2];
x = chirp(t,0,2,500,"logarithmic");  # freq. sweep from 0-500 over 2 sec.
Fs=1000;                  # sampled every 0.001 sec so rate is 1 kHz
step=ceil(20*Fs/1000);    # one spectral slice every 20 ms
window=ceil(100*Fs/1000); # 100 ms data window

## plot signal
subplot(2,1,1);
plot(t,x);
grid("on");
title("Specgram Demo");
## no xticklabels
set(gca(),"xticklabel","");
## get positiotn for later
pos1=get(gca(),"position");

subplot(2,1,2);
specgram(x, 2^nextpow2(window), Fs, window, window-step);
colormap("jet");

## enlarge 2nd axes to fill almost up to first
pos2=get(gca(),"position");
set(gca(),"position",[pos2(1),pos2(2),pos2(3),0.95*(pos1(2)-pos2(2))]);

## set tick and limits at sensible location
ax=axis();
axis([ax(1),ax(2),0,512]);
set(gca(),"ytick",[0,1/4,1/2,3/4,1]*512);

