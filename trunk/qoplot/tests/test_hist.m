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

function test_hist

  # set protocol file name
  rowDate = clock();
  strDiaryFileName = [num2str(rowDate(1)) "-" num2str(rowDate(2)) "-" num2str(rowDate(3)) "-" \
	                    num2str(rowDate(4)) "-" num2str(rowDate(5)) "-" num2str(rowDate(6)) \
											"-__hist_test-protocol.txt"];

  diary(strDiaryFileName) # starts the diary into file

	# test hist plots
	disp("Test 1: hist:")
	try # test 1
	  x = 1:10;
	  hist(x);
	  disp("Passed: x = 1:10; hist(x)")
	catch
	  disp("Failed: x = 1:10; hist(x)");
	  disp(lasterr);
	end_try_catch
	disp("Please press any button for next test ...")
	pause

	disp("Test 2: hist:")
	try # test 2
	  x = 1:10;
	  hist(x,[2 5 7]);
	  disp("Passed: x = 1:10; h = hist(x,[2 5 7])")
	catch
	  disp("Failed: x = 1:10; h = hist(x,[2 5 7])");
	  disp(lasterr);
	end_try_catch
    disp("Please press any button for next test ...")
	pause

	disp("Test 3:")
	try # test 3
	  x = 1:11;
	  hist(x,[0.1 0.4 0.9]);
	  disp("Passed: x = 1:11; hist(x,[0.1 0.4 0.9];")
	catch
	  disp("Passed: x = 1:11; hist(x,[0.1 0.4 0.9];")
	  disp(lasterr);
	end_try_catch
	disp("Please press any button for next test ...")
	pause

	disp("Test 3.5:")
	try # test 3.5
	  x = 1:11;
	  hist(x,"m");
	  disp("Passed: x = 1:11; hist(x,""m"");")
	catch
	  disp("Passed: x = 1:11; hist(x,""m"");")
	  disp(lasterr);
	end_try_catch
	disp("Please press any button for next test ...")
	pause

	disp("Test 4:")
	try # test 4
	  x = 1:11;
	  hist(x,5);
	  disp("Passed: x = 1:11; hist(x,5);")
	catch
	  disp("Passed: x = 1:11; hist(x,5);")
	  disp(lasterr);
	end_try_catch
	disp("Please press any button for next test ...")
	pause

	disp("Test 5:")
	try # test 5
	  x = 1:7;
	  hist(x,[2 4 6],[0.1 0.4 0.9]);
	  disp("Passed: x = 1:7; hist(x,[2 4 6],[0.1 0.4 0.9]);")
	catch
	  disp("Passed: x = 1:7; hist(x,[2 4 6],[0.1 0.4 0.9]);")
	  disp(lasterr);
	end_try_catch
	disp("Please press any button for next test ...")
	pause

	disp("Test 6:")
	try # test 6
	  x = 1:9;
	  hist(x,[0.1 0.4 0.9],[2 4 6]);
	  disp("Passed: x = 1:9; hist(x,[0.1 0.4 0.9],[2 4 6]);")
	catch
	  disp("Failed: x = 1:9; hist(x,[0.1 0.4 0.9],[2 4 6]);");
	  disp(lasterr);
	end_try_catch
	disp("Please press any button for next test ...")
	pause

	disp("Test 7:")
	try # test 7
	  x = 1:12;
	  hist(x,9,"g");
	  disp("Passed: x = 1:12; hist(x,9,""g"");")
	catch
	  disp("Failed: x = 1:12; hist(x,9,""g"");");
	  disp(lasterr);
	end_try_catch
	disp("Please press any button for next test ...")
	pause

	disp("Test 8:")
	try # test 8
	  x = 1:12;
	  hist(x,"y",9);
	  disp("Passed: x = 1:12; hist(x,""g"",9);")
	catch
	  disp("Failed: x = 1:12; hist(x,""g"",9);");
	  disp(lasterr);
	end_try_catch
	disp("Please press any button for next test ...")
	pause

	disp("Test 9:")
	try # test 9
	  x = 1:12;
	  hist(x,5,9);
	  disp("Passed: x = 1:12; hist(x,5,9);")
	catch
	  disp("Failed: x = 1:12; hist(x,5,9);");
	  disp(lasterr);
	end_try_catch
	disp("Please press any button for next test ...")
	pause

	disp("Test 10:")
	try # test 10
	  x = 1:12;
	  hist(x,[0.5 0.6 0.5],9,1);
	  disp("Passed: x = 1:12; hist(x,[0.5 0.6 0.5],9,1);")
	catch
	  disp("Failed: x = 1:12; hist(x,[0.5 0.6 0.5],9,1);");
	  disp(lasterr);
	end_try_catch
	disp("Please press any button for next test ...")
	pause

	disp("Test 11:")
	try # test 11
	  x = 1:12;
	  hist(x,"c",9,1);
	  disp("Passed: x = 1:12; hist(x,""c"",9,1);")
	catch
	  disp("Failed: x = 1:12; hist(x,""c"",9,1);");
	  disp(lasterr);
	end_try_catch
	disp("Please press any button for next test ...")
	pause

	disp("Test 12:")
	try # test 12
	  x = 1:12;
	  hist(x,[0.5 0.5 0.5],[4 8],1);
	  disp("Passed: x = 1:12; hist(x,[0.5 0.5 0.5],[4 8],1);")
	catch
	  disp("Failed: x = 1:12; hist(x,[0.5 0.5 0.5],[4 8],1);");
	  disp(lasterr);
	end_try_catch
	disp("Please press any button for next test ...")
	pause

	disp("Test 13:")
	try # test 13
	  x = 1:12;
	  hist(x,[4 8],[0.5 0.95 0.5],1);
	  disp("Passed: x = 1:12; hist(x,[4 8],[0.5 0.95 0.5],1);")
	catch
	  disp("Failed: x = 1:12; hist(x,[4 8],[0.5 0.95 0.5],1);");
	  disp(lasterr);
	end_try_catch
	disp("Please press any button for next test ...")
	pause
	
	disp("Test 14:")
	try
	  x = 1:12;
	  [x,n] = hist(x,[4 8],[0.5 0.95 0.5],1);
	  bar(n,x,n(2)-n(1));
	  disp("Passed: x = 1:12; [x,n] = hist(x,[4 8],[0.5 0.95 0.5],1);bar(n,x,n(2)-n(1));")
	catch
	  disp("Failed: x = 1:12; [x,n] = hist(x,[4 8],[0.5 0.95 0.5],1);bar(n,x,n(2)-n(1));");
	  disp(lasterr);
	end_try_catch
	disp("Please press any button for next test ...")
	pause

	diary off
  

endfunction

