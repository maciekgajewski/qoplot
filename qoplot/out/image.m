## Copyright (C) 2008 Maciej Gajewski
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
## @deftypefn {Function File} {@var{h}} = image (@var{data},@var{args})
## This function creates image using @var{data}.
## If data is n x m x 3, creates RGB image, otherwise, creates image using figure colormap.
##
## Current axes are prepared for image in following way: YDir property is set to 'reverse',
## and  XLim/YLim are make big enough to accomodate image.
##
## The remainder of the arguments, if any, are taken as property value pairs
## and are applied to the line
##
## image returns the handle of the object created
## @end deftypefn
## @seealso{set,get,plot}

## Author: Maciej Gajewslo <maciej.gajewski0@gmail.com>
## Keywords: qoplot graphics

function handle = image (data,varargin)
  
  __nxtplt__();
  
  xlim = get(gca, 'XLim');
  ylim = get(gca, 'YLim');
  
  set(gca, 'YDir', 'reverse');
  
  h = size( data, 1 );
  w = size( data, 2 );
  
  set( gca, 'XLim', [ min(xlim(1), 0 ) max(xlim(2), w) ] );
  set( gca, 'YLim', [ min(ylim(1), 0 ) max(ylim(2), h) ] );
  
  # detect mode, create image
  # is integer RGB data? Assume this is 0-255 image data, scale down to 0-1 
  wasinteger = 0;
  if isinteger( data )
	data = double( data ) / 255;
	wasinteger = 1;
  endif
  
  # RGB?
  if size( data, 3 ) == 3
    r = data(:,:,1);
    g = data(:,:,2);
    b = data(:,:,3);
    handle = qoplot_command('image', r, g, b ){1};
  # single plane image
  else
	if( get(gca, 'CLimMode') == 'auto' && ! wasinteger )
		# for non-integrer images, adapt to min/max
		set(gca(),"clim",[min(min(data)) max(max(data))]);
	endif
  	handle = qoplot_command('image', data ){1};
  	# if image was integer - use intensity mode by default
  	if wasinteger
  	  set( handle, 'Mode', 'intensity' );
  	endif
  endif
  
  if length(varargin),
    set(handle,varargin{:});
  endif
endfunction
