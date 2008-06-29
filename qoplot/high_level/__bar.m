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
  
  
  # check input arguments
  [x,y,color,width,plottype] = checkInputArgs(varargin{1:end-1});
  # x        - vector of x-coordinates of bars
  # y        - matrix of bar sieries to draw. Series are in rows, data in columns
  # width    - relative bar width
  # color    - bar color, used only for single bar sieries. Otherwise ColorOrder used.
  # plottype - can be: 'grouped'/'stacked'/'hist'/'histc' (irrevelant for single patch)

  [dx,xx,yy] = prepareBarData( x, y, width, plottype );


  if(min(yy)<0 & max(yy)>0)
    draw_ax = 1;
  else
    draw_ax = 0;
  endif

  hh = [];
  [nr,nc] = size(y);
  

  if  (strcmp(strCallerFunc,"barh") | strcmp(strCallerFunc,"histh"))
  # horizontal bars
    for j=1:nr
      for i=1:nc
        hh = [ \
	      hh , \
	      patch(\
		    [yy(j,1+(i-1)*4),yy(j,2+(i-1)*4),yy(j,3+(i-1)*4),yy(j,4+(i-1)*4)],\
		    [xx(j,1+(i-1)*4),xx(j,2+(i-1)*4),xx(j,3+(i-1)*4),xx(j,4+(i-1)*4)],\
		    definedColor(i,1:3))];
	  endfor
    endfor
    if( draw_ax )
      line( [0,0],\
            [-dx(1)*width/2+x(1),dx(end)*width/2+x(end)],\
            "Color","k");
    endif
  else
  # vertical bars
    for j=1:nr
      for i=1:nc
        hh = [ \
	      hh , \
	      patch(\
		    [xx(j,1+(i-1)*4), xx(j,2+(i-1)*4), xx(j,3+(i-1)*4), xx(j,4+(i-1)*4)],\
		    [yy(j,1+(i-1)*4), yy(j,2+(i-1)*4), yy(j,3+(i-1)*4), yy(j,4+(i-1)*4)],\
		    definedColor(i,1:3))];
	  endfor
    endfor
    if( draw_ax )
      line( [-dx(1)*width/2+x(1),dx(end)*width/2+x(end)],\
            [0,0],\
            "Color","k");
    endif
  endif

  if nargout,
    h = hh;
  endif

## ===========================================================
#  additional functions
## ===========================================================

# -------------------------------------------------------------------
# Prepare bar data

  function [dx,xx,yy] = prepareBarData(x,y,width,plottype,yIsMatrix)

    dx = diff(x(:)');
    dx = [dx(1),dx,dx(end)];

    xLength = length(x);
    xBounds = [];
    xx = [];
    yy = [];
    xTemp = [];
    yTemp = [];
    

    if (!strcmp(plottype,"histogram"))
      for i = 1:xLength
        xBounds = [xBounds; x(i)-width/2];
      endfor
    else
      for i = 1:xLength
        xBounds = [xBounds; x(i)-dx(i)/2];
      endfor
    endif

    [nRows,nColumns] = size(y);
    
    # TODO:
    # "unnice" programmed, should be redesigned sometimes
    # this means the next 2 rows
    # <Michel D. Schmid>
    nUnequal1 = find(dx(:)!=1);
    if ( !isempty(nUnequal1) || (strcmp(plottype,"grouped") & (nRows>1)))
      div1=width/nColumns;
      newWidth = div1*width;
      diff1 = div1-newWidth;
      deltaPos = diff1/2;

      for j=1:nRows
        for i=1:nColumns
          xBar = xBounds(j,1) + deltaPos + (i-1)*div1 ;
          xTemp = [xTemp xBar xBar xBar+newWidth xBar+newWidth];
          yTemp = [yTemp [0 1 1 0]*y(j,i)];
        endfor
        xx = [xx;xTemp];
        yy = [yy;yTemp];
        xTemp = [];
        yTemp = [];
      endfor
    elseif ( (strcmp(plottype,"grouped") & (nRows==1)) | \
             (strcmp(plottype,"histogram") & (nRows==1))  )
      # y is no matrix
      for i=1:nColumns
        xBar = xBounds(i,1);
        if strcmp(plottype,"histogram")
          xx = [xx xBar xBar xBar+dx(i) xBar+dx(i)];
	else
          xx = [xx xBar xBar xBar+width xBar+width];
	endif
        yy = [yy [0 1 1 0]*y(i)];
      endfor
    elseif (strcmp(plottype,"stacked") & (nRows>1))
      # y is matrix; plottype is stacked
      y = y';
      for j=1:nColumns
        for i=1:nRows
          xBar = xBounds(i,1);
          xTemp = [xTemp xBar xBar xBar+width xBar+width];
          if (j==1)
            yTemp = [yTemp [0 1 1 0]*y(j,i)];
          elseif (j>1)
            yTemp = [yTemp [yy(j-1,(i-1)*4+2),yy(j-1,(i-1)*4+2),\
			    yy(j-1,i*4-1),yy(j-1,i*4-1)]+[0 1 1 0]*y(j,i)];
          endif
        endfor
        xx = [xx;xTemp];
        yy = [yy;yTemp];
        xTemp = [];
        yTemp = [];
      endfor
      tempX4 = [];
      tempY4 = [];
      nColumns = size(yy,2)/4;
      nRows = size(yy,1);
      for j= 1:nColumns
        for i=1:nRows
          tempX4 = [tempX4 xx(i,(j-1)*4+1:j*4)];
          tempY4 = [tempY4 yy(i,(j-1)*4+1:j*4)];
        endfor
        xTemp = [xTemp;tempX4];
        yTemp = [yTemp;tempY4];
        tempX4 = [];
        tempY4 = [];
      endfor
      xx = xTemp;
      yy = yTemp;
    endif

  endfunction



# ------------------------------------------------------------
# Check Input Args

  function [x,y,color,width,plottype] = checkInputArgs(varargin)
  
    # default values
    width = 0.8;
    color = "r";
    plottype = "grouped";

    # One param - only Y
    if(nargin==1),
      y=varargin{1};
      if any(size(y)==1),
        x=1:length(y);
      else
        x=1:size(y,1);
      endif

    # Two params: x,Y or Y,color or Y,plottype or Y,width
    elseif(nargin==2)
      # both (hopefully) numeric - x,Y or Y,width
      if ( isnumeric( varargin{2} )
        if ( isscalar( varargin{2} ) )
          y=varargin{1};
          width=varargin{2};
        else
          x=varargin{1};
          y=varargin{2};
        endif
      # second is color or plottype
      else
        s = varargin{2};
        if s == 'grouped' || s == 'stacked' || s == 'histc' || s == 'hist'
          plottype = s;
        else
          color = s;
        endif
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
        if s == 'grouped' || s == 'stacked' || s == 'histc' || s == 'hist'
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


## ===========================================================
#  END additional functions
## ===========================================================

endfunction
