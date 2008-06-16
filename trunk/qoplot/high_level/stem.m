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

## -*- texinfo -*-
## @deftypefn {Function File} {} @var{h}= stem ([@var{x}],@var{y},[@var{lineSpec}])
## Plots a stem graph.
## The default color is "r" (red). The default line style is "-" and the default
## marker is "o".
## Returns in @var{h} the handles of the line and marker objects used to draw the
## stems.
##
## @example
## x = 1:10;
## stem(x);
## @end example
## @noindent
## plots 10 stems with hights from 1 to 10
##
## @example
## x = 1:10;
## y = ones(1,length(x))*2.*x;
## stem(x,y);
## @end example
## @noindent
## plots 10 stems with hights from 2 to 20
## 
## @example
## x = 1:10;
## y = ones(1,length(x))*2.*x;
## h = stem(x,y,'b');
## @end example
## @noindent
## plots 10 bars with hights from 2 to 20
## color is blue, 2x10 handles will be returned
## The first row holds the lines handles,
## the second rows holds the handles of the markers.
##
## @example
## x = 1:10;
## y = ones(1,length(x))*2.*x;
## h = stem(x,y,'-.k');
## @end example
## @noindent
## plots 10 stems with hights from 2 to 20
## color is black and line style is "-.", 2x10 handles will be returned
## The first row holds the lines handles,
## the second rows holds the handles of the markers.
##
## @example
## x = 1:10;
## y = ones(1,length(x))*2.*x;
## h = stem(x,y,'-.k.');
## @end example
## @noindent
## plots 10 stems with hights from 2 to 20
## color is black, line style is "-." and the marker style is ".",
## 2x10 handles will be returned
## The first row holds the lines handles,
## the second rows holds the handles of the markers.
##
## @example
## x = 1:10;
## y = ones(1,length(x))*2.*x;
## h = stem(x,y,"fill");
## @end example
## @noindent
## plots 10 stems with hights from 2 to 20
## color is rgb-tripl defined, line style is "-" and the marker style is "o",
## 2x10 handles will be returned
## The first row holds the lines handles,
## the second rows holds the handles of the markers.
##
## Color definitions with rgb-tripl are not valid!
##
## @end deftypefn
## @seealso{bar,barh,plot}

## Author: mds mailto:michaelschmid@users.sourceforge.net
## $Revision: 403 $, $Date: 2006-12-28 19:09:01 +0200 (Thu, 28 Dec 2006) $

function h = stem(varargin)

# check number of input parameters
error(nargchk(1,4,nargin));
[x,y,dofill,lc,ls,mc,ms] = checkStemArg(varargin{:});

__nxtplt__();

# first, plot the lines.. without marker
hh = plot([x(:)'; x(:)'],[zeros(size(y(:)')) ; y(:)'],[lc ls]);
# second, plot the markers..
hhh = [];
hhhh = [];
hold on;
hhh = plot([x(:)'; x(:)'],[y(:)' ; y(:)'],[mc ms]);
if (find(y<0))
  xAxisRange = get(gca,'XLim');
  hhhh = plot(xAxisRange,[0 0],'k');
endif
hold off;
if (dofill)
  set(hhh,"MarkerFaceColor",mc);
endif


if nargout==1
  if ~isempty(hhhh)
    hhhh = hhhh*(ones(length(hh),1))';
  endif
  h = [hh;hhh;hhhh];
endif


# ========================================================
## checkStemArg
function  [x,y,dofill,lc,ls,mc,ms] = checkStemArg(varargin)

# set specifiers to default values
[lc,ls,mc,ms] = setDefaultValues;
dofill = 0;
fill_2 = 0;
lineSpec_2 = 0;

# check input arguments
if(nargin==1)
  y=varargin{1};
  if isvector(y)
    x=1:length(y);
  elseif ismatrix(y)
    x=1:size(y,1);
  else 
    error('Y must be a matrix');
  endif # in each case, x & y will be defined

elseif(nargin==2)
  # several possibilities
  # 1. the real y data
  # 2. 'fill'
  # 3. line spec
  if ischar(varargin{2})
    # only 2. or 3. possible
    if strcmp("fill",varargin{2})
      dofill = 1;
    else
      # parse the LineSpec
      varargin{2}
      [lc,ls,mc,ms] = stemLineSpec(varargin{2});
    endif
    y=varargin{1};
    if isvector(y)
      x=1:length(y);
    elseif ismatrix(y)
      x=1:size(y,1);
    else
      error('Y must be a matrix');
    endif # in each case, x & y will be defined
  else
    # must be the real y data
    x = varargin{1};
    y = varargin{2};
    if ~(ismatrix(x) && ismatrix(y))
      error('X and Y must be matrices');
    endif
  endif
elseif(nargin==3)
  # again several possibilities
  # arg2 1. real y
  # arg2 2. 'fill' or LineSpec
  # arg3 1. 'fill' or LineSpec
  if ischar(varargin{2})
    # only arg2 2. / arg3 1. & arg3 3. are possible
    if strcmp("fill",varargin{2})
      dofill = 1;
      fill_2 = 1; # be sure, no second "fill" is in the arguments
    else
      # must be a LineSpec
      [lc,ls,mc,ms] = stemLineSpec(varargin{2});
      lineSpec_2 = 1;
    endif
    y=varargin{1};
    if isvector(y)
      x=1:length(y);
    elseif ismatrix(y)
      x=1:size(y,1);
    else
      error('Y must be a matrix');
    endif # in each case, x & y will be defined
  else
    # must be the real y data
    x = varargin{1};
    y = varargin{2};
    if ~(ismatrix(x) && ismatrix(y))
      error('X and Y must be matrices');
    endif
  endif # if ischar(varargin{2})
  # varargin{3} must be char...
  # check for "fill" ..
  if (strcmp("fill",varargin{3}) & fill_2)
    error("stem:checkStemArg: Twice the same argument!");
  elseif (strcmp("fill",varargin{3}) & lineSpec_2)
    # must be "fill"
    dofill = 1;
    fill_2 = 1;
  elseif (strcmp("fill",varargin{3}) & !lineSpec_2)
    # must be "fill"
    dofill = 1;
    fill_2 = 1;
  elseif !lineSpec_2
    # must be LineSpec
    [lc,ls,mc,ms] = stemLineSpec(varargin{3});
    lineSpec_2 = 1;
  endif
elseif (nargin==4)
  x = varargin{1};
  y = varargin{2};
  if ~(ismatrix(x) && ismatrix(y))
    error('X and Y must be matrices');
  endif

  if strcmp("fill",varargin{3})
    dofill = 1;
    fill_2 = 1; # be sure, no second "fill" is in the arguments
  else
    # must be a LineSpec
    [lc,ls,mc,ms] = stemLineSpec(varargin{3});
    lineSpec_2 = 1;
  endif

  # check for "fill" ..
  if (strcmp("fill",varargin{4}) & fill_2)
    error("stem:checkStemArg: Twice the same argument!");
  elseif (strcmp("fill",varargin{4}) & lineSpec_2)
    # must be "fill"
    dofill = 1;
    fill_2 = 1;
  elseif (!strcmp("fill",varargin{4}) & !lineSpec_2)
    # must be LineSpec
    [lc,ls,mc,ms] = stemLineSpec(varargin{4});
    lineSpec_2 = 1;
  endif
endif

endfunction # checkStemArg

## END checkStemArg
# ========================================================
## stemLineSpec

function [lc,ls,mc,ms] = stemLineSpec(str)
if !ischar(str)
  error("stem:stemLineSpec: Wrong argument type, must be ""fill"" or a string of specifiers!");
  return;
endif
[lc,ls,mc,ms] = setDefaultValues;
# __pltopt__ parse the line specifier string
cur_props = __pltopt__({str});
for i=1:1:length(cur_props)
  if strcmp(cur_props(i).name,"markeredgecolor");
    mc = cur_props(i).val;
  elseif strcmp(cur_props(i).name,"color"); # means line color
    lc = cur_props(i).val;
  elseif strcmp(cur_props(i).name,"linestyle");
    ls = cur_props(i).val;
  elseif strcmp(cur_props(i).name,"marker");
    ms = cur_props(i).val;
  endif
endfor
endfunction # stemLineSpec
## END stemLineSpec
# ========================================================
## setDefaultValues
function [lc,ls,mc,ms] = setDefaultValues
# set default values
mc = "r";
lc = "r";
ls = "-";
ms = "o";
endfunction
## END setDefaultValues
# ========================================================


endfunction
