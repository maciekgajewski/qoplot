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

## -*- texinfo -*-
## @deftypefn {Function File} {@var{h}} = legend (@var{args})
## Controls the legend in the current axes. The followign combinations
## of input arguments are accepted:
##
## @table @samp
## @item legend(@var{vis})
## where @var{vis} is a string with a value of @code{on}, @code{off}, 
## @code{hide}, @code{show}, or @code{toggle} controls the legends 
## visibility.
##
## @item legend("lab1","lab2",...)
## Sets the labels of the lines in the current plot. The order of the
## lines is the order of their handles in the axes' "Children" property.
## An empty label ommits the line from the legend.
##
## @item legend(...,"Location",@var{loc})
## Sets the location of the legend to @var{loc}. Refer to the legend
## properties for legal values of @var{loc}
## @end table
##
## legend returns the handle of the current axes' legend 
## @end deftypefn
## @seealso{axes,line}

## Author: Shai Ayal <shaiay@users.sourceforge.net>
## Keywords: octplot graphics

function handle = legend (varargin)

  lgnd = get(gca(),"legend");
  name_s = 1; # names start index in varargin
  name_e = length(varargin); # names end index
  visible = "on"; # defautl value of 'visible' property
  
  if length(varargin)==1,
    arg1 = tolower(varargin{1});
    if isstr(arg1),
      if strcmp(arg1,"show") | strcmp(arg1,"on"),
        visible = "on";
        name_s = 2;
      elseif strcmp(arg1,"hide") | strcmp(arg1,"off"),
        visible = "off";
        name_s = 2;
      elseif strcmp(arg1,"toggle") ,
        if(strcmp(get(lgnd,"visible"),"on"))
          visible = "off";
          name_s = 2;
        else
          visible = "on";
          name_s = 2;
        endif
      endif
    endif
  endif

  ## check for location
  if length(varargin)>=2,
    if isstr(varargin{end-1}) & isstr(varargin{end})
      if strcmp(tolower(varargin{end-1}),"location")
        set(lgnd,"Location",varargin{end});
        name_e -= 2;
      endif
    endif
  endif

  ## check that all remamining ars are strings
  is=1;
  for i=name_s:name_e,
    if ~isstr(varargin{i}),
      error("all arguments must be strings")
    endif
  endfor

  chld = get(gca(),"children");
  li = name_s;
  ci = length(chld);
  while(li<=name_e & ci>0)
    if strcmp(get(chld(ci),"Annotation"),"on"),
      set(chld(ci),"DisplayName",varargin{li++});
    endif
    ci --;
  endwhile
  
  set(lgnd,"visible", visible );

  if nargout , handle=lgnd ; endif

endfunction
