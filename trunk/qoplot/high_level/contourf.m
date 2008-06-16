## Copyright (C) 2007 Kai Habel
## Copyright (C) 2003 Shai Ayal
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
## @deftypefn {Function File} {} [@var{C}, @var{H}] = contourf (@var{x},@var{y},@var{z},@var{vn})
## This function computes filled contours of the matrix @var{z}.
## Parameters @var{x}, @var{y} and @var{vn} are optional.
##
## The return value @var{c} is a 2xn matrix containing the contour lines
## as dexcribed in the help to the contourc function
##
## The return value @var{H} is handle-vector to the patch objects creating
## the filled contours
##
## if @var{x} and @var{y} are ommited they are taken as the row/column
## index of @var{z}. @var{vn} is either a scalar denoting the number of lines
## to compute or a vector contianing the values of the lines. If only one
## value is wanted, set @var{vn}=[val,val];
## If @var{vn} is omitted it defaults to 10
##
## @example
## [x,y,z] = peaks(50);
## contourf (@var{x}, @var{y}, @var{z}, -7:9)
## @end example
## @end deftypefn
## @seealso{contour, contourc, line, plot}

## Author: Kai Habel, shaia

function varargout = contourf(X, Y, Z, lvl, varargin)

  if (nargin == 2)
    lvl = Y;
  end

  if (nargin < 3)
    Z = X;
    [X, Y] = meshgrid(1 : columns(Z),1 : rows(Z));
  end

  if (any(size(X)) != any(size(Y)))
    usage('X and Y must be of same size')
  end

  if isvector(X)
    [X, Y] = meshgrid(X, Y);
  end
  
  minx = min(min(X)); maxx = max(max(X));
  miny = min(min(Y)); maxy = max(max(Y));
  minz = min(min(Z)); maxz = max(max(Z));
  [nr, nc] = size(Z);

  if (nargin == 1 | nargin == 3)
    lvl = linspace(minz, maxz, 10);
  end
  if (isscalar(lvl))
    lvl = linspace(minz, maxz, lvl+2)(1:end - 1);
  else
    idx1 = find(lvl < minz);
    idx2 = find(lvl > maxz);
    lvl(idx1(1:end-1)) = [];
    lvl(idx2) = [];
    if isempty(lvl)
      lvl = [minz minz];
    end
  end
  X0 = prepad(X, nc + 1, 2 * X(1, 1) - X(1, 2), 2);
  X0 = postpad(X0, nc + 2, 2 * X(1, nc) - X(1, nc - 1), 2);
  X0 = [X0(1, :); X0; X0(1, :)];
  Y0 = prepad(Y, nr + 1, 2 * Y(1, 1) - Y(2, 1), 1);
  Y0 = postpad(Y0, nr + 2, 2 * Y(nr, 1) - Y(nr - 1, 1));
  Y0 = [Y0(:, 1), Y0, Y0(:, 1)];
  Z0 = ones(nr + 2, nc + 2) * (minz - maxz);
  Z0(2:nr + 1, 2:nc + 1) = Z;
  [c, lev] = contourc(X0, Y0, Z0, lvl);
  cmap = colormap();
  lvl_eps = min(diff(lvl)) / 1000.0;
  ## if we have one level only set to 1e-6
  if (lvl_eps < 10*eps) 
    lvl_eps = 1e-6;
  end

  levx = linspace(min(lev), max(lev), size(cmap,1));

  __nxtplt__();

  ## decode contourc output format
  i1 = 1;
  ncont = 0;
  while(i1 < columns(c))
    ncont++;
    cont_lev(ncont) = c(1, i1);
    cont_len(ncont) = c(2, i1);
    cont_idx(ncont) = i1 + 1;

    ii = i1 + 1 : i1 + cont_len(ncont);
    cur_cont = c(:, ii);
    ## reset contours outside of frame to border
    idx1 = find(c(1, ii) > maxx) + i1;
    idx2 = find(c(1, ii) < minx) + i1;
    idx3 = find(c(2, ii) > maxy) + i1;
    idx4 = find(c(2, ii) < miny) + i1;
    c(1, idx1) = maxx; c(1, idx2) = minx;
    c(2, idx3) = maxy; c(2, idx4) = miny;
    c(:, ii); startidx = ii(1); stopidx = ii(end);
    cont_area(ncont) = polyarea(c(1, ii), c(2, ii));
    i1 += c(2, i1) + 1;
  endwhile

  # handle for each level the case where,
  # we have (a) hole(s) in a patch 
  # Those are to be filled with the
  # color of level below
  # or with the background colour.
  for k = 1:length(lev)
    lvl_idx = find(abs(cont_lev - lev(k)) < lvl_eps);
    len = length(lvl_idx);
    if (len > 1)
      # FIXME: next line should be replaced with
      # mark = false(size(lvl_idx));
      # when octave-2.1.73 support (esp. cygwin) is dropped
      mark = logical(zeros(size(lvl_idx)));
      a = 1;
      while (a < len)
        # take 1st patch
        b = a + 1;
        pa_idx = lvl_idx(a);
        # get pointer to contour start, and contour length
        curr_ct_idx = cont_idx(pa_idx);
        curr_ct_len = cont_len(pa_idx);
        # get contour
        curr_ct = c(:, curr_ct_idx : curr_ct_idx + curr_ct_len - 1);
        b_vec = (a + 1) : len;
        next_ct_pt_vec = c(:, cont_idx(lvl_idx(b_vec)));
        in = inpolygon(next_ct_pt_vec(1,:), next_ct_pt_vec(2,:), curr_ct(1, :), curr_ct(2, :));
        mark(b_vec(in)) = !mark(b_vec(in));
        a += 1;
      end
      if (length(mark) > 0)
        # all marked contours describe a hole in a larger contour
        # of the same level and must be filled with
        # colour of level below
        ma_idx = lvl_idx(mark);
        if (k > 1)
          # find color of level below
          tmp = find(abs(cont_lev - lev(k - 1)) < lvl_eps);
          lvl_bel_idx = tmp(1);
          # set color of patches found
	  cont_lev(ma_idx) = cont_lev(lvl_bel_idx);
        else
          # set lowest level contour
          # to NaN
	  cont_lev(ma_idx) = NaN;
        end
      end
    end
  end

  # the algoritm can create patches
  # with the size of the plotting
  # area, we would like to draw only
  # the patch with the highest level  
  del_idx = [];
  max_idx = find(cont_area == max(cont_area));
  cond1 = abs((maxx - minx) * (maxy - miny)-max(cont_area)) < sqrt(eps); 
  if (cond1 && length(max_idx) > 1)
    # delete double entries
    del_idx = max_idx(1 : end - 1);
    cont_area(del_idx) = [];
    cont_lev(del_idx) = [];
    cont_len(del_idx) = [];
    cont_idx(del_idx) = [];
  end

  # now we have everything together
  # and can start plotting the patches
  # beginning with largest area
  [tmp, svec] = sort(cont_area);
  len = ncont - length(del_idx);
  h = zeros(1,len);
  for n = len : -1 : 1
    idx = svec(n);
    ii = cont_idx(idx) : cont_idx(idx) + cont_len(idx) - 2;
    h(n) = patch(c(1, ii), c(2, ii), cont_lev(idx), varargin{:});
  end

  if (min(lev) == max(lev))
    set(gca(),"clim",[min(lev) - 1 max(lev) + 1]);
  else
    set(gca(),"clim",[min(lev) max(lev)]);
  end

  if (nargout > 0)
    varargout{1} = c;
  end
  if (nargout > 1)
    varargout{2} = h;
  end
endfunction
