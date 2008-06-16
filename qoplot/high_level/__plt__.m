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

function [color_order_ptr,handle] =__plt__(xdata,ydata,color_order_ptr,props)
  if(isvector(xdata) || isempty(xdata))
    if(isvector(ydata)) ## vector-vector
      if(length(xdata)==length(ydata) || isempty(xdata))
        handle = line(xdata,ydata);
      else
        error("xdata, ydata dimensions don't match");
      endif
    else ## vector-matrix
      [nr,nc]=size(ydata);
      if(nc==length(xdata))
        ydata = ydata';
      endif
      [nr,nc]=size(ydata);
      if(nr==length(xdata) || isempty(xdata))
        handle=zeros(1,nc);
        for i=1:nc,
          handle(i) = line(xdata,ydata(:,i));
        endfor
      else
        error("xdata, ydata dimensions don't match");
      endif
    endif
  else
    if(isvector(ydata)) ## matrix-vector
      [nr,nc]=size(xdata);
      if(nr==length(ydata))
        xdata = xdata';
      endif
      [nr,nc]=size(xdata);
      if(nc==length(ydata)),
        handle=zeros(1,nr);
        for i=1:nr,
          handle(i) = line(xdata(i,:),ydata);
        endfor
      else
        error("xdata, ydata dimensions don't match");
      endif
    else ## matrix-matrix
      if(size(ydata)==size(xdata))
        handle = zeros(1,size(xdata,2));
	for i=1:size(xdata,2),
          handle(i) = line(xdata(:,i),ydata(:,i));
        endfor
      else
        error("xdata, ydata dimensions don't match");
      endif
    endif
  endif

  ## flags for coloring using colororder property
  color_set =0;

  if(~isempty(props))
    for i=1:length(props)
      ## check for explicit color request
      if(strcmp(props(i).name,"color"))
        color_set = 1;
      endif
      for j=1:length(handle)
        set(handle(j),props(i).name,props(i).val);
      endfor
    endfor
  endif

  if(~color_set)
    ## no colors were explicitly given, so we will use the color order
    ## property to determine line colors and marker colors (these are
    ## always the same when using the plot command)
    co = get(gca(),"colororder");
    if(color_order_ptr>size(co,1))
      color_order_ptr = 1;
    endif
    for j=1:length(handle)
      set(handle(j),"color",co(color_order_ptr,:));
      set(handle(j),"markeredgecolor",co(color_order_ptr,:));
      if(++color_order_ptr > size(co,1))
        color_order_ptr = 1;
      endif
    endfor
  endif

endfunction
