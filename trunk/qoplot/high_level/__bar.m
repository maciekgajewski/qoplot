## Copyright (C) 2005 - 2006 Shai Ayal
## Copyright (C) 2007 Michel D. Schmid
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
## @deftypefn {Function File} {} @var{h}= __bar([@var{x}],@var{y},[@var{width}],[@var{'color'}],@var{'callerFunc'})
##
## @end deftypefn
## @seealso{bar,barh,patch,area}

## Author: shaia
## Author: mds  michaelschmid@users.sourceforge.net


function h =__bar(varargin)

  # check number of input parameters
  error(nargchk(2,6,nargin));
  # last input argument must be the caller function, bar or barh
  strCallerFunc = varargin{end};

  __nxtplt__();
  persistent color_order_pointer = 1;
  
  
  # check input arguments
  [x,y,color,width,plottype] = checkInputArgs(varargin{1:end-1});
  # x        - vector of x-coordinates of bars
  # y        - matrix of bar sieries to draw. Series are in rows, data in columns
  # width    - relative bar width
  # color    - bar color, used only for single bar sieries. Otherwise ColorOrder used.
  # plottype - can be: 'grouped'/'stacked'/'hist'/'histc' (irrevelant for single patch)

  series = size( y, 2 );
  bars   = size( y, 1 );
  
  
  
  # ========= single series - paint differently ===============
  if series == 1 
    # get color
    if isempty( color )
      colors = get( gca, 'ColorOrder' );
      color = colors( color_order_pointer, : );
      color_order_pointer = mod( color_order_pointer + 1, size( colors, 1) );
    endif
    xm = [];
    ym = [];
    for i = 1:bars
      # find coordinates for this bar
      xs = [ x(i) - width/2; x(i) - width/2;  x(i) + width/2; x(i) + width/2 ];
      ys = [ 0; y(i); y(i); 0 ];
      # append to matrix
      xm = [xm  xs];
      ym = [ym ys];
    endfor
    barxlim = [ min(x) - width*0.75, max(x) + width*0.75 ];
    barylim = [ min(0, min(y)) max(y) ]; # find new xlim/ylim
    
    # horizontal bars
    if ( strcmp(strCallerFunc, 'barh') )
      
      # preapre axes
      if ( strcmp( get( gca, 'XLimMode'), 'auto') )
        set( gca, 'XLim', barylim );
      endif
      if ( strcmp( get( gca, 'YLimMode'), 'auto') )
        set( gca, 'YLim', barxlim );
      endif
      
      #create patch
      hh = patch( ym, xm, color );
    
    # vertical bars
    else
      # preapre axes
      if ( strcmp( get( gca, 'XLimMode'), 'auto') )
        set( gca, 'XLim', barxlim );
      endif
      if ( strcmp( get( gca, 'YLimMode'), 'auto') )
        set( gca, 'YLim', barylim );
      endif
      
      #create patch
      hh = patch( xm, ym, color );
    endif
  # ========= multisetries bars - take use of plottype, paint defferently =========
  else
    for s = [1:series]
    endfor
  endif
  
      


  if nargout,
    h = hh;
  endif

## ===========================================================
#  additional functions
## ===========================================================


# ------------------------------------------------------------
# Check Input Args

  function [x,y,color,width,plottype] = checkInputArgs(varargin)
  
    # default values
    width = 0.8;
    color = [];
    plottype = "grouped";

    # One param - only Y
    if(nargin==1)
      y = varargin{1};
      x = findx(y);

    # Two params: x,Y or Y,color or Y,plottype or Y,width
    elseif(nargin==2)
      # both (hopefully) numeric - x,Y or Y,width
      if ( isnumeric( varargin{2} ) )
        if ( isscalar( varargin{2} ) )
          y=varargin{1};
          width=varargin{2};
          x = findx(y);
        else
          x=varargin{1};
          y=varargin{2};
        endif
      # second is color or plottype
      else
        s = varargin{2};
        if s == 'grouped' || s == 'stacked'
          plottype = s;
        else
          color = s;
        endif
        x = findx(y);
      endif
      
    # three params: x, Y, string or x,Ymwidth
    elseif(nargin==3)
      x=varargin{1};
      y=varargin{2};
      if ( isnumeric( varargin{3} ) )
        width = varargin{3};
      else
        # third is color or plottype
        s = varargin{3};
        if s == 'grouped' || s == 'stacked'
          plottype = s;
        else
          color = s;
        endif
      endif
    endif
  
  # if y is vector, make sure it's a column vector
  if( any(size(y)) == 1 )
    y = reshape( y, length(y), 1 );
  endif

  # check types
  if ( ! isnumeric(y) || isscalar(y) )
    error("Bar data should be vector or matrix.");
  endif
   
  # check x
  if ( ! isnumeric(x) || isscalar(x) || min( size(x) ) > 2 )
    error("Bar x-coordinates should be vector.");
  endif
  
  # y is vector?
  if( any(size(y)) == 1 )
    if ( length(x) != length(y) )
      error("X and Y sizes should match.");
    endif
  else
    if( length(x) != size(Y,1) )
      error("X size shoud match number of rows in Y");
    endif
  endif
  
  endfunction

# -----------
# find X for y
function x=findx(y)
  # find x for y
  if any(size(y)==1),
    x=1:length(y);
  else
    x=1:size(y,1);
  endif

## ===========================================================
#  END additional functions
## ===========================================================

endfunction
