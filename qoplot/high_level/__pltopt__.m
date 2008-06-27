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

function [prop,numarg]=__pltopt__(args)
  i = 0;
  p = 1;
  ls = 0;
  mk = 0;
 
  ps = args{1};
  numarg = 1;

  if (length(ps)==0),
    prop = [];
    return;
  endif
  
  while (i<length(ps))
    i++;
    if(index("rgbcymkw",ps(i)))
      prop(p).name="color";
      prop(p).val=ps(i);
      p++;
      # keep marker color and line color the same
      prop(p).name = "markeredgecolor";
      prop(p).val = ps(i);
      p++;
    elseif(index("+o*.xsd^v><ph",ps(i)))
      prop(p).name="marker";
      prop(p).val=ps(i);
      p++;
      mk = 1;
    elseif(ps(i)==":")
      prop(p).name="linestyle";
      prop(p).val=":";
      p++;
      ls = 1;
    elseif(ps(i)=="-")
      prop(p).name="linestyle";
      if(i==length(ps))
        prop(p).val="-";
      elseif(index(":-.",ps(i+1)))
        prop(p).val=ps(i:i+1);
        i++;
      else
        prop(p).val="-";
      endif
      p++;
      ls = 1;
    elseif(ps(i)==";")
      is = i+1;
      while (i<length(ps))
        i++;
        if (ps(i)==";") 
          break;
        endif
      endwhile
      prop(p).name="label";
      prop(p).val=ps(is:i-1);
      p++;
    elseif(i==1 & length(args)>1)
      ## a "property",value pair was specified explicitly
      prop(p).name = ps;
      prop(p).val  = args{2};
      p++;
      i = length(ps);
      numarg = 2;
    else
      error("Illegal plot format specifier");
    endif
  endwhile
  
  # specifing marker without linestyle implies
  # linestyle==none (default linestyle="-")
  if(mk & ~ls) ,
    prop(p).name = "linestyle";
    prop(p).val = "none";
    p++;
  endif
  
  
endfunction
