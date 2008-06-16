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

## -*- texinfo -*- 
## @deftypefn {Function File} {@var{h}} = plot(@var{args})
## This function produces two-dimensional plots.  Many different
## combinations of arguments are possible.  The simplest form is
##
## @example 
## plot (@var{y}) 
## @end example
##
## @noindent where the argument is taken as the set of @var{y}
## coordinates and the
## @var{x} coordinates are taken to be the indices of the elements,
## starting with 1.
##
## If more than one argument is given, they are interpreted as
##
## @example 
## plot (@var{x}, @var{y}, @var{fmt} ...) 
## @end example
##
## @noindent where @var{y} and @var{fmt} are optional, and any number of
## argument
## sets may appear.  The @var{x} and @var{y} values are interpreted as
## follows:
##
## @itemize @bullet 
## @item If a single data argument is supplied, it is
## taken as the set of @var{y}
## coordinates and the @var{x} coordinates are taken to be the indices
## of the elements, starting with 1.
##
## @item If the first argument is a vector and the second is a matrix,the
## the vector is plotted versus the columns (or rows) of the matrix.
## (using whichever combination matches, with columns tried first.)
##
## @item If the first argument is a matrix and the second is a vector,the
## the columns (or rows) of the matrix are plotted versus the vector.
## (using whichever combination matches, with columns tried first.)
##
## @item If both arguments are vectors, the elements of @var{y} are
## plotted versus the elements of @var{x}.
##
## @item If both arguments are matrices, the columns of @var{y} are
## plotted versus the columns of @var{x}.  In this case, both matrices 
## must have
## the same number of rows and columns and no attempt is made to transpose
## the arguments to make the number of rows match.
##
## @item If both arguments are scalars, a single point is plotted. 
## @end itemize
##
## If @var{fmt} is missing, the default line style is assumed. Line
## colors will be determined using the ColorOrder propertu of the
## current axes.
##
## If the @var{fmt} argument is supplied, it is interpreted as follows.
##
## @table @samp 
##
## @item - 
## Set lines line style (default).
##
## @item : 
## Set dotted line style.
##
## @item -- 
## Set dashed line style.
##
## @item -. 
## Set dash-dot line style.
##
## @item none 
## Set no line style.
##
## @item ;text; 
## sets the line's label to @code{text}
##
## @item @var{c} 
## If @var{c} is one of @code{r}, @code{g},
## @code{b}, @code{c}, @code{m}, @code{y}, @code{k}, 
## or @code{w}, it is interpreted
## as the plot color (red, green, blue, cyan, magenta, yellow, black or
## white).
##
## @item @var{s}
## if @var{s} is one of @code{+}, @code{o}, @code{*}, @code{.},
## @code{x}, @code{^}, @code{v}, @code{>}, @code{<}, @code{s} or
## @code{d}, it is interepted as the marker style.
## 
## @end table
##
## plot returns the handle(s) of the line(s) created
##
## Here are some plot examples:
##
## @example 
## h=plot (y, "b*--;dead parrot;");
## @end example
##
## This command will plot the data in the variable @code{y} vs the index
## of @code{y}. The plot style will be blue dahsed lines with a * symbol
## and the line label will be "dead parrot". The lines handle will be
## returned in @code{h}.
## @end deftypefn 
## @seealso{set,get,line}

## Author: shaia

function hout = plot (varargin)

  ## the current color when no color is given explicitly
  persistent color_order_ptr

  if(__nxtplt__())
    color_order_ptr = 1;
  endif

  if(isempty(color_order_ptr))
    color_order_ptr = 1;
  endif

  data_parms = 0;
  format_parms = 0;
  plot_it = 0;
  cur_arg = 1;
  p1 = [];
  p2 = [];
  h = [];
  cur_props=[];
  
  while(cur_arg<=nargin)
    if( isstr(varargin{cur_arg}))
      if (data_parms==0)
        error("no data to plot");
      else
        format_parms++;
        [cur_props,numarg] = __pltopt__(varargin(cur_arg:end));
        cur_arg += numarg-1;
      endif
    else 
      if(format_parms | data_parms==2)
        [color_order_ptr,newh]=__plt__(p1,p2,color_order_ptr,cur_props);
        h = [h,newh];
        data_parms=0;
        format_parms=0;
        p1=[];
        p2=[];
        cur_props=[];
      endif
      
      if(data_parms==0)      
        p2 = varargin{cur_arg};
      elseif(data_parms==1) 
        p1 = p2;
        p2 = varargin{cur_arg};
      endif
      data_parms++;
    endif
    cur_arg++;
  endwhile

  if (~isempty(p2))
    [color_order_ptr,newh]=__plt__(p1,p2,color_order_ptr,cur_props);
    h = [h,newh];
  else
    error("no data to plot");
  endif

  ca = get(h(1),'Parent');
  set(ca,"xscale","linear");
  set(ca,"yscale","linear");

  if(nargout)
    hout = h;
  endif

endfunction

