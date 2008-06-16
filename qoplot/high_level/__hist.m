## Copyright (C) 1996, 1997 John W. Eaton
## adaptet for OctPlot by Michel D. Schmid, 30. March 2006
##
## This file is part of OctPlot.
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

## Author: Michel D. Schmid <michaelschmid@users.sourceforge.net>

function [nn, xx] = __hist (varargin)

  error(nargchk(1,5,nargin))
  [y,x,color,nBins,norm] = checkHistArgs(varargin{1:end-1});
	strCallerFunc = varargin{end};

  arg_is_vector = isvector (y);

  cutoff = (x(1:end-1,:) + x(2:end,:)) / 2;
  nBins = rows (x);
  if (nBins < 30 && columns (x) == 1)
    ## The following algorithm works fastest for n less than about 30.
    chist = zeros (nBins+1, columns (y));
    for i = 1:nBins-1
      chist(i+1,:) = sum (y <= cutoff(i));
    endfor
    chist(nBins+1,:) = rows (y);
  else
    ## The following algorithm works fastest for n greater than about 30.
    ## Put cutoff elements between boundaries, integrate over all
    ## elements, keep totals at boundaries.
    [s, idx] = sort ([y; cutoff]);
    len = rows (y);
    chist = cumsum (idx <= len);
    t1 = zeros (1, columns (y));
    t2 = reshape (chist(idx > len), size (cutoff));
    t3 = chist(end,:);
    chist = [t1; t2; t3];
  endif

  freq = diff (chist);

  if (norm>0)
    ## Normalise the histogram.
    freq = freq / rows (y) * norm;
  endif

  if (nargout == 2)
    if (arg_is_vector)
      nn = freq';
      xx = x';
    else
      nn = freq;
      xx = x;
    endif
  elseif (nargout == 1)
    if (arg_is_vector)
      xx = x';
    else  
      xx = x;
    endif
    nn =  __bar(x,freq,1,color,strCallerFunc);
  else
    __bar (x, freq, 1, color,strCallerFunc);
  endif

  # ========================================================
	## checkStemArg
  function [y,x,color,nBins,norm] = checkHistArgs(varargin)

    ## default values
    color = "r";
    norm = 0;
    nBins = 10;

    # at least, one argument must be
		# be sure, it's a column vector
		y = varargin{1};
  	y = y(:);

  	if (isreal (y))
      max_val = max (y);
      min_val = min (y);
    else
      error ("hist:checkHistArgs: first argument must be a vector");
    endif
  	# if only one argument, calc x and set nBins
  	if (nargin==1)
      x = [0.5:nBins]'/nBins;
      x = x * (max_val - min_val) + ones(size(x)) * min_val;
    elseif (nargin==2)
      # a new way will be tested .. if more than one argument...
      # scan for what it is...
      # nargin is 2
      if iscolorspec(varargin{2})
        color = varargin{2};
        x = [0.5:nBins]'/nBins;
        x = x * (max_val - min_val) + ones(size(x)) * min_val;
      elseif isscalar(varargin{2})
        nBins = varargin{2};
        if (nBins <= 0)
          error ("hist:checkHistArgs: number of bins must be positive");
        endif
        x = [0.5:nBins]'/nBins;
        x = x * (max_val - min_val) + ones(size(x)) * min_val;
      elseif isreal(varargin{2})
        if isvector(varargin{2})
          x = varargin{2};
          x = x(:);
        endif
      endif # iscolorspec(varargin{2})

    elseif (nargin==3)
      # second argument can be a color definition
      if iscolorspec(varargin{2})
        color = varargin{2};
        # is it a vector?
        if isvector(color)
          arg_is_vector = 1;
        else
          arg_is_vector = 0;
        endif
        if iscolorspec(varargin{3})
          error("hist:checkHistArgs: 2 color specifications found ...! Args 2 & 3")
        else
					if isscalar(varargin{3})
					  nBins = varargin{3};
            x = [0.5:nBins]'/nBins;
        		x = x * (max_val - min_val) + ones(size(x)) * min_val;
			    elseif isvector(varargin{3})
			      x = varargin{3};
					  x = x(:);
					endif # isvector(varargin{3})
        endif # iscolorspec(varargin{3})
      elseif isscalar(varargin{2})
        # can be only nBins
        nBins = varargin{2};
        x = [0.5:nBins]'/nBins;
        x = x * (max_val - min_val) + ones(size(x)) * min_val;
        if iscolorspec(varargin{3})
          color = varargin{3};
        elseif isscalar(varargin{3})
          norm = varargin{3};
          warning ("Argument 2 is taken as bins, argument 3 is taken as norm!")
        elseif isvector(varargin{3})
         error ("This kind of input parameters doesn't make sense!")
        endif # iscolorspec(varargin{3})
      elseif iscolorspec(varargin{3})
        color = varargin{3};
        if isvector(varargin{2})
          x = varargin{2};
          x = x(:);
        endif
      endif # iscolorspec(varargin{2})

    elseif (nargin==4)
    # second argument can be a color definition
      if iscolorspec(varargin{2})
        color = varargin{2};
        # is it a vector?
        if isvector(color)
          arg_is_vector = 1;
        else
          arg_is_vector = 0;
        endif
        if iscolorspec(varargin{3})
          error("hist:checkHistArgs: 2 color specifications found ...! Args 2 & 3")
        else
					if isscalar(varargin{3})
					  nBins = varargin{3};
            x = [0.5:nBins]'/nBins;
        		x = x * (max_val - min_val) + ones(size(x)) * min_val;
        		# varargin{2} = colorspec
        		# varargin{3} = nBins
        		if isscalar(varargin{4})
        		  norm = varargin{4};
      		  else
      		    error ("Check the 4th argument, it doesn't make any sense!")
      		  endif

			    elseif isvector(varargin{3})
						# varargin{2} = color
						# varargin{3} = x data ==> no sense for nBins
			      x = varargin{3};
					  x = x(:);
				    if isscalar(varargin{4})
				      norm = varargin{4};
						else
						  error ("Check the 4th argument, it doesn't make any sense!")
				    endif
					endif # isvector(varargin{3})
        endif # iscolorspec(varargin{3})
      elseif isscalar(varargin{2})
        # can be only nBins
        nBins = varargin{2};
        x = [0.5:nBins]'/nBins;
        x = x * (max_val - min_val) + ones(size(x)) * min_val;
        if iscolorspec(varargin{3})
          color = varargin{3};
          # varargin{2} = nBins
          # varargin{3} = color
          if isscalar(varargin{4})
            norm = varargin{4};
          else
						  error ("Check the 4th argument, it doesn't make any sense!")
          endif
        elseif isscalar(varargin{3})
          norm = varargin{3};
          warning ("Argument 2 is taken as bins, argument 3 is taken as norm!")
          # varargin{2} = nBins
          # varargin{3} = norm
          if iscolorspec(varargin{4})
            color = varargin{4};
          else
						  error ("Check the 4th argument, it doesn't make any sense!")
          endif
        elseif isvector(varargin{3})
         error ("This kind of input parameters doesn't make sense!")
        endif # iscolorspec(varargin{3})
      elseif isvector(varargin{2})
        x = varargin{2};
        x = x(:);
        if iscolorspec(varargin{3})
          color = varargin{3};
          norm = varargin{4};
        elseif isscalar(varargin{3})
				  norm = varargin{3};
					if iscolorspec(varargin{4})
					  color = varargin{4};
					else
					  error("__hist:checkHistArgs: doesn't make any sense!")
					endif
        endif
      endif # iscolorspec(varargin{2})
 		endif

  endfunction
	## END checkHistArg
	# ========================================================

endfunction
