## Copyright (C) 2007 Kai Habel
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
## @deftypefn {Function File} {} @var{go} = findobj (@var{propname1}, @var{propvalue1}, ...)
## @deftypefnx {Function File} {} @var{go} = findobj (@var{h}, @var{propname1}, @var{propvalue1}, ...)
## @deftypefnx {Function File} {} @var{go} = findobj (@var{h}, 'flat', @var{propname1}, @var{propvalue1}, ...)
## @deftypefnx {Function File} {} @var{go} = findobj (@var{h})
## @deftypefnx {Function File} {} @var{go} = findobj ()
## Returns all graphic objects @var{go} that contain property/values pair(s) 
## @var{propname1}, @var{propvalue1}, ... .
## If @var{h} is given the search is restricted to object tree below @var{h} and @var{h} itself. 
## A second argument 'flat' restricts the search to the objects given in @var{h}.
## If no property/value pair(s) are given all graphic objects below @var{h} or the root are returned. 
##
## @seealso{isprop, ishandle, set, get}
## @end deftypefn

## Author: Kai Habel

function obj = findobj(varargin)
  obj = [];
  gobj = 0;
  arglist = varargin;
  flat = false;

  # find the 'special' cases
  if (length(arglist) > 0)
    if ishandle(arglist{1})
      gobj = arglist{1};
      arglist = arglist(2 : end);
      if (length(arglist) > 0)
        if strcmp(tolower(arglist(1)), 'flat')
          flat = true;
          arglist = arglist(2 : end);
        end
      end
    end
  end

  if (length(arglist) == 0)
    obj = [obj; gobj(:)];
    for i = 1 : length(gobj)
      if (isprop(gobj(i), 'Children'))
        ch = get(gobj(i), 'Children');
        if ((length(ch) > 0) & !flat)
          obj = [obj; findobj(ch)];
        end
      end
    end
  else
    # we have propname/propvalues pair(s)
    propnames = arglist(1 : 2 : end);
    propvalues = arglist(2 : 2 : end);
    if (flat)
      obj_lst = findobj(gobj, 'flat');
    else
      obj_lst = findobj(gobj);
    end
    for i = 1 : length(obj_lst)
      go = obj_lst(i);
      if (ishandle(go))
        incl = true;
        for i = 1 : length(propnames)
          # check each property 
          propname = propnames{i};
          propvalue = propvalues{i};
          h = [];
          if isprop(go, propname)
            val = get(go, propname);
            if (length(val) > 0)
              if isstr(val)
                # for string valued properties
                if (strcmp(val, tolower(propvalue)) == 1)
                  h = go;
                end
              else
                # for numeric properties
                if all(val == propvalue)
                  h = go;
                end
              end
            end
          end
          if (length(h) == 0)
            incl = false;
          end
        end

        if (incl)
          obj = [obj; h];
        end

      end
    end
  end
end

