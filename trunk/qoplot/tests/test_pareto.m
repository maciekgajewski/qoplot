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

function test_pareto

  # set protocol file name
  rowDate = clock();
  strDiaryFileName = [num2str(rowDate(1)) "-" num2str(rowDate(2)) "-" num2str(rowDate(3)) "-" \
	                    num2str(rowDate(4)) "-" num2str(rowDate(5)) "-" num2str(rowDate(6)) \
											"-pareto_test-protocol.txt"];

  diary(strDiaryFileName) # starts the diary into file

	# test pareto charts
	disp("Test 1:")
	try # test 1
	  y = [1 2 5 3 4];
	  pareto(y);
	  disp("Passed: y = [1 2 5 3 4]; pareto(y)");
	catch
	  disp("Failed: y = [1 2 5 3 4]; pareto(y)");
	  disp(lasterr);
	end_try_catch
	
	disp("Test 2:")
	try # test 2
	  hFig2 = figure;
	  y = [1 2 5 3 4];
	  h = pareto(y);
	  disp("Passed: y = [1 2 5 3 4]; h = pareto(y)");
	catch
	  disp("Passed: y = [1 2 5 3 4]; h = pareto(y)");
	  disp(lasterr);
	end_try_catch
	
	disp("Test 3:")
	try # test 3
	  hFig3 = figure;
	  y = [1 2 10 7 4];
	  x = {"5th","4th","1st","2nd","3rd"};
	  h = pareto(y,x);
	  disp("Passed: y = [1 2 5 3 4]; x = {""1st"",""2nd"",""3rd"",""4th"",""5th""}; h = pareto(y,x)");
	catch
	  disp("Passed: y = [1 2 5 3 4]; x = {""1st"",""2nd"",""3rd"",""4th"",""5th""}; h = pareto(y,x)");
	  disp(lasterr);
	end_try_catch
	
	disp("Test 4:")
	try # test 4
	  hFig4 = figure;
	  y = [1 2 10 7 4];
	  x = [10 20 100 70 40];
	  h = pareto(y,x);
	  disp("Passed: y = [1 2 5 3 4]; x = [10 20 100 70 40]; h = pareto(y,x)");
	catch
	  disp("Passed: y = [1 2 5 3 4]; x = [10 20 100 70 40]; h = pareto(y,x)");
	  disp(lasterr);
	end_try_catch

	diary off
  

endfunction

