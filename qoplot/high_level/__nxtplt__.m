## Copyright (C) 2006 Bruno Roggeri
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

function newa=__nxtplt__(opt_command)
## the optional command is launched if we'll be working on new axes
newa=0;

if ~isempty(get(0,'children'))
  if ~isempty(get(gcf(),"children"))
    if strcmp(get(gca(),'nextplot'),'replace')
      cla();
      newa = 1;
      if nargin == 1
	eval(opt_command);
      endif
    endif
  endif
else
  newa = 1;
  if nargin == 1
    eval(opt_command);
  endif
endif
endfunction
