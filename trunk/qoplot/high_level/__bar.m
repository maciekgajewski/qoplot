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
  [x,y,definedColor,width,plottype,yIsMatrix] = checkInputArgs(varargin{1:end-1});
  ## TODO: yisMatrix won't be used... I think so

  # prepare inputs to usable datas
  if ( strcmp(strCallerFunc,"hist") | strcmp(strCallerFunc,"histh"))
    plottype="histogram";
    y = y';
    sizeY = size(y,2);
    temp = ones(sizeY,4);
    for i = 1:sizeY
      temp(i,:)= definedColor;
    endfor
    definedColor = temp;
  endif
  [dx,xx,yy] = prepareBarData(x,y,width,plottype,yIsMatrix);


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
  function [x,y,definedColor,width,plottype,yIsMatrix] = checkInputArgs(varargin)
  
    # default values
    width = 0.8;
    definedColor = "r";
    plottype = "grouped";
    yIsMatrix = 0;

    if(nargin==1),
      y=varargin{1};
      if any(size(y)==1),
        x=1:length(y);
        definedColor = setColorMatrix(definedColor,y);
      else
        x=1:size(y,1);
      ## this seems to be a difference between earlier versions
      # and svn versionn 400
      #  definedColor = get(gca,"colororder")
        definedColor = setColorMatrix(definedColor);
      endif

    elseif(nargin==2)
      x=varargin{1};
      y=varargin{2};
      if any(size(y)==1),
        definedColor = setColorMatrix(definedColor,y);
      else
##      TODO: old style  #definedColor = get(gca,"colororder");
        definedColor = setColorMatrix(definedColor);
      endif

    elseif(nargin==3)
      x=varargin{1};
      y=varargin{2};
      if (isnumeric(varargin{3}) & isscalar(varargin{3}))
        width=varargin{3};
      else
        # in this case, it can be still a style or a color
        if (ischar(varargin{3}) & length(varargin{3})>1)
          # now it can't be a color definition	  
	      if (strcmp(varargin{3},"stacked") | strcmp(varargin{3},"grouped") )
	        plottype = varargin{3};
	      else
	        error("Unknown type argument")
	      endif
        else
          definedColor = varargin{3};
          # check if a valid color is defined
	      if any(size(definedColor))<1
	        error("Dimension of color is wrong")
	      endif
	      [n m] = size(definedColor);
	      for i=1:n
	        testColor = definedColor(i,:);
            if ~iscolorspec(testColor)
              disp("WARNING: Unknown color specification, will change color to red.");
              definedColor = "r";
	          break;
            endif
	      endfor
        endif
      endif
      if any(size(y)==1)
        definedColor = setColorMatrix(definedColor,y);
      else
        definedColor = setColorMatrix(definedColor);
      endif

    elseif(nargin==4)
      x=varargin{1};
      y=varargin{2};
      if (isnumeric(varargin{3}) & isscalar(varargin{3}))
        width=varargin{3};
      else
        # in this case, it can be only a color
        definedColor = varargin{3};
        # check if a valid color is defined
        if any(size(definedColor))<1
          error("Dimension of color is wrong")
        endif
        [n m] = size(definedColor);
        for i=1:n
          testColor = definedColor(i,:);
          if ~iscolorspec(testColor)
            disp("WARNING: Unknown color specification, will change color to red.");
            definedColor = "r";
            break;
          endif
        endfor
        if any(size(y)==1)
          definedColor = setColorMatrix(definedColor,y);
        else
          definedColor = setColorMatrix(definedColor);
        endif
      endif
      # in this case, it can be still a style or a color
      if (ischar(varargin{4}) & length(varargin{4})>1)
        # now it can't be a color definition
	    if (strcmp(varargin{4},"stacked") | strcmp(varargin{4},"grouped") )
	      plottype = varargin{4};
	      definedColor = setColorMatrix(definedColor);
	    else
	      error("Unknown type argument")
	    endif
      else
        definedColor = varargin{4};
	    if !ischar(definedColor)
          # check if a valid color is defined
	      if any(size(definedColor))<1
	        error("Dimension of color is wrong")
	      endif
	      [n m] = size(definedColor);
	      for i=1:n
	        testColor = definedColor(i,:);
            if ~iscolorspec(testColor)
              disp("WARNING: Unknown color specification, will change color to red.");
              definedColor = "r";
	          break;
            endif
	      endfor
	      if n>1
	        definedColor = setColorMatrix(definedColor);
	      else
	        definedColor = setColorMatrix(definedColor,y);
	      endif
	    else
	      definedColor = setColorMatrix(definedColor,y);
	    endif # !ischar(definedColor)
      endif
    elseif(nargin==5)
      x=varargin{1};
      y=varargin{2};
      width=varargin{3};
      definedColor=varargin{4};
      # check if a valid color is defined
      if any(size(definedColor))<1
	    error("Dimension of color is wrong")
      endif
      [n m] = size(definedColor);
      for i=1:n
	    testColor = definedColor(i,:);
        if ~iscolorspec(testColor)
          disp("WARNING: Unknown color specification, will change color to red.");
          definedColor = "r";
	      break;
        endif
      endfor
      if any(size(y)==1)
        definedColor = setColorMatrix(definedColor,y);
      else
        definedColor = setColorMatrix(definedColor);
      endif
      plottype=varargin{5};

    endif
  endfunction
# ------------------------------------------------------------
  function definedColor = setColorMatrix(definedColor,y)
    
    if (nargin==2)
      if (ischar(definedColor))    
        switch definedColor
          case "r"
            definedColor = [1 0 0 1];
          case "g"
            definedColor = [0 1 0 1];
          case "b"
            definedColor = [0 0 1 1];
          case "c"
            definedColor = [0 1 1 1];
          case "m"
            definedColor = [1 0 1 1];
          case "y"
            definedColor = [1 1 0 1];
          case "k"
            definedColor = [0 0 0 1];
          case "w"
            definedColor = [1 1 1 1];
        endswitch
     else # if it's a rgb-triple
       definedColor = [definedColor 1];
     endif # if (ischar(definedColor))

      sizeY = size(y,2);
      temp = ones(sizeY,4);
      for i = 1:sizeY
        temp(i,:)=definedColor;
      endfor
      definedColor = temp;
    else
      if !(ischar(definedColor))
        [n m] = size(definedColor);
        if (n<=7)
          definedColor(:,end+1) = 1;
	endif
      else
        definedColor = [1 0 0 1;
                      0 0 1 1;
                      0 1 0 1;
                      1 1 0 1;
                      0 1 1 1;
                      1 0 1 1;
                      1 1 1 1];
	endif
    endif  

  endfunction

## ===========================================================
#  END additional functions
## ===========================================================

endfunction
