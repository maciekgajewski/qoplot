## copyright (c) 2003 shai ayal
##
## this program is free software; you can redistribute it and/or modify it
## under the terms of the gnu general public license as published by
## the free software foundation; either version 2, or (at your option)
## any later version.
##
## octplot is distributed in the hope that it will be useful, but
## without any warranty; without even the implied warranty of
## merchantability or fitness for a particular purpose.  see the gnu
## general public license for more details.
##
## you should have received a copy of the gnu general public license
## along with octplot; see the file copying.  if not, write to the free
## software foundation, 59 temple place - suite 330, boston, ma
## 02111-1307, usa.

## -*- texinfo -*-
## @deftypefn {function file} {} [@var{c},[@var{h}]] = contour (@var{x},@var{y},@var{z},@var{vv})
##
## the return value @var{c} is a 2xn matrix containing the contour lines 
## as dexcribed in the help to the contourc function. contour also returns
## in #var{h} the handles of the line objects created
##
## if @var{x} and @var{y} are ommited they are taken as the row/column 
## index of @var{z}. @var{vn} is either a scalar denoting the number of lines 
## to compute or a vector contianing the values of the lines. if only one 
## value is wanted, set @var{vn}=[val,val];
## if @var{vn} is omitted it defualts to 10
##
## @example
## contour (@var{x}, @var{y}, @var{z}, linspace(0,2*pi,10))
## @end example
## @end deftypefn
## @seealso{contourc,line,plot}

## author: shaia

function varargout = contour(varargin)

  if (nargin==1)
    vn = 10;
    z = varargin{1};
    x = 1:size(z,2);
    y = 1:size(z,1);
  elseif (nargin==2)
    vn = varargin{2};
    z = varargin{1};
    x = 1:size(z,2);
    y = 1:size(z,1);
  elseif (nargin==3)
    vn = 10;
    x = varargin{1};
    y = varargin{2};
    z = varargin{3};
  elseif (nargin==4)
    vn = varargin{4};
    x = varargin{1};
    y = varargin{2};
    z = varargin{3};
  else
    error("Wrong number of arguments");
  endif
  
  [c,lev] = contourc(varargin{:});
  cmap = get(gcf(),"colormap");
  
  levx = linspace(min(lev),max(lev),size(cmap,1));

  __nxtplt__();

  ## set axes XLim and YLim to accomodate contour
  xlim = get( gca, 'XLim' );
  ylim = get( gca, 'YLim' );
  
  set( gca, 'XLim', [ min( [ xlim x ] ), max( [xlim x] ) ] );
  set( gca, 'YLim', [ min( [ ylim y ] ), max( [ylim y] ) ] );
  
  ## decode contourc output format
  i1 = 1;
  n=1;
  h=[];
  while(i1<length(c))
    clev = c(1,i1);
    clen = c(2,i1);
    ccr = interp1(levx,cmap(:,1),clev);
    ccg = interp1(levx,cmap(:,2),clev);
    ccb = interp1(levx,cmap(:,3),clev);

    ii = i1+1:i1+clen;
    h(n++) = line(c(1,ii),c(2,ii),"color",[ccr,ccg,ccb,1]);
    
    i1 += c(2,i1)+1;
  endwhile

  if( get(gca, 'CLimMode') == 'auto' )
  	set(gca(),"clim",[min(lev) max(lev)]);
  endif
  
  ## folowing dm's suggestion to surpress output if none asked for
  if nargout > 0
    varargout{1} = c;
  endif
  if (nargout > 1)
    varargout{2} = h;
  endif
    

endfunction


