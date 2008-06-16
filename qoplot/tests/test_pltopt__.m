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


## Author: mds mailto:michaelschmid@users.sourceforge.net
## $Revision$, $Date$

function test_pltopt__

  # set protocol file name
  rowDate = clock();
  strDiaryFileName = [num2str(rowDate(1)) "-" num2str(rowDate(2)) "-" num2str(rowDate(3)) "-" \
	                    num2str(rowDate(4)) "-" num2str(rowDate(5)) "-" num2str(rowDate(6)) \
											"-__pltopt__test-protocol.txt"];

  diary(strDiaryFileName) # starts the diary into file
	disp("This test will call some other tests which create the")
	disp("apropriate test protocols!")
	disp("Check the protocols to see if some error occured!")
	disp("Following protocols should be created:")
	disp("    stem")

	# don't close diary command with "diary off"... error will occure..

	# test plot command


	# test stem plots
	test_stem;

  

endfunction

