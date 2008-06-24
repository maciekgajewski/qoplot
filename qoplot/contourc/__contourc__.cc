/* Contour lines for function evaluated on a grid.
    Copyright (C) 2004 Shai Ayal

  Adapted to an oct file from the stand alone contourl by Victro Munoz
  Copyright (C) 2004 Victor Munoz

  Improvements to avoid losing a contour
  Copyright (C) 2007 Kai Habel

  Based on contour plot routine (plcont.c) in PLPlot package
  http://plplot.org/

  Copyright (C) 1995, 2000, 2001 Maurice LeBrun
  Copyright (C) 2000, 2002 Joao Cardoso
  Copyright (C) 2000, 2001, 2002, 2004  Alan W. Irwin
  Copyright (C) 2004  Andrew Ross

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Library Public License as published
  by the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Library General Public License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

*/

#include "oct.h"
#include <cfloat>
static Matrix this_contour;
static Matrix contourc;
static int elem;

// this is the quanta in which we increase this_contour
#define CONTOUR_QUANT 50

/**********************************************************************
  cl_add_point(x,y);

  Add a coordinate point (x,y) to this_contour

**********************************************************************/
void
cl_add_point (double x, double y)
{
  if (elem % CONTOUR_QUANT == 0)
    this_contour = this_contour.append (Matrix (2, CONTOUR_QUANT, 0));

  this_contour (0, elem) = x;
  this_contour (1, elem) = y;
  elem++;
}

/**********************************************************************

  cl_end_contour();

  Adds contents of current contour to contourc.
this_contour.cols () - 1;
**********************************************************************/

void
cl_end_contour ()
{
  if (elem > 2)
    {
      this_contour (1, 0) = elem - 1;
      contourc = contourc.append (this_contour.extract_n (0, 0, 2, elem));
    }
  this_contour = Matrix ();
  elem = 0;
}

/**********************************************************************

  cl_start_contour(flev,x,y);

  Start a new contour, and adds contents of current one to contourc

**********************************************************************/

void
cl_start_contour (double flev, double x, double y)
{
  cl_end_contour ();
  this_contour.resize (2, 0);
  cl_add_point (flev, flev);
  cl_add_point (x, y);
}

void
cl_drawcn (RowVector & X, RowVector & Y, Matrix & Z, double flev,
	   int krow, int kcol, double lastx, double lasty, int startedge,
	   charMatrix & ipts)
{
  int kx = 0, lx = Z.cols () - 1, ky = 0, ly = Z.rows () - 1;

  double f[4];
  double px[4], py[4], locx[4], locy[4];
  int iedge[4];
  int i, j, k, num, inext, kcolnext, krownext;
  bool first;

  px[0] = X (krow + 1);
  px[1] = X (krow);
  px[2] = X (krow);
  px[3] = X (krow + 1);
  py[0] = Y (kcol);
  py[1] = Y (kcol);
  py[2] = Y (kcol + 1);
  py[3] = Y (kcol + 1);

  f[0] = Z (krow + 1, kcol) - flev;
  f[1] = Z (krow, kcol) - flev;
  f[2] = Z (krow, kcol + 1) - flev;
  f[3] = Z (krow + 1, kcol + 1) - flev;
  /*facet point naming convention

   ^    0---3
   |    |   |
   row  1---2
        col->
  */
  
  /* To avoid any trouble with contours crossing
   * a corner (f[i] = 0, set all corners close to zero
   * to small value DBL_EPSILON
   */
  for (unsigned int i = 0; i < 4; i++)
  {
    if (fabs(f[i]) < DBL_EPSILON)
      f[i] = DBL_EPSILON;
  }
  for (unsigned int i = 0, j = 1; i < 4; i++, j = (j + 1) % 4)
  {
      iedge[i] = (f[i] * f[j] > 0.0) ? -1 : 1;
      /*facet egde naming convention
        *--3--*
        |     |
        0     2
        |     |
        *--1--*
      */
  }

  bool cond1 = (f[0] * f[1] < 0.0) && (f[2] * f[3] < 0.0);
  bool cond2 = (f[1] * f[2] < 0.0) && (f[3] * f[0] < 0.0);
  if ( cond1 && cond2)
  {
    if (ipts (krow, kcol) == 0)
    {
      // mark square for 2nd pass
      ipts (krow, kcol) = 2;
    }
    else
    {
      // second time, mark as done
      ipts (krow, kcol) = 1;
    }
  }
  else
    // Mark this square as done
    ipts (krow, kcol) = 1;

  // Check if no contour has been crossed; all edges == -1
  if (iedge[0] + iedge[1] + iedge[2] + iedge[3] == -4)
  {
    return;
  }

  // Check if this is a completely flat square - in which case
  // ignore it
  if ((fabs(f[0]) < DBL_EPSILON) && (fabs(f[1]) < DBL_EPSILON) &&
      (fabs(f[2]) < DBL_EPSILON) && (fabs(f[3]) < DBL_EPSILON))
  {
    return;
  }

  // Calculate intersection points
  num = 0;
  if (startedge < 0)
    first = true;
  else
  {
    locx[num] = lastx;
    locy[num] = lasty;
    num++;
    first = false;
  }
  // cycle trough all edges beginning with startedge
  for (k = 0, i = (startedge < 0 ? 0 : startedge); k < 4;
       k++, i = (i + 1) % 4)
  {
    if (i == startedge)
    {
      if (ipts (krow, kcol) == 2)
        ipts (krow, kcol) += startedge;
      continue;
    }

    if (iedge[i] == 1)
    {
      // contour crosses current edge
      j = (i + 1) % 4;
      locx[num] = (px[i] * fabs (f[j]) + px[j] * fabs (f[i])) / fabs (f[j] - f[i]);
      locy[num] = (py[i] * fabs (f[j]) + py[j] * fabs (f[i])) / fabs (f[j] - f[i]);
      // If this is the start of the contour then move to the point
      if (first)
      {
        cl_start_contour (flev, locx[num], locy[num]);
        first = false;
      }
      else
      {
        // Link to the next point on the contour
        cl_add_point (locx[num], locy[num]);
        inext = (i + 2) % 4;
        // Need to follow contour into next facets
        kcolnext = kcol;
        krownext = krow;
        if (i == 0)
          kcolnext--;      // <-- move left
        else if (i == 1)
          krownext--;      // v   move down
        else if (i == 2)
          kcolnext++;       // --> move right
        else if (i == 3)
          krownext++;      // ^   move up

        // check if we still within the matrix limits
        // and next facet is not marked as done
        // --> contine with next facet
        if ((kcolnext >= kx) && (kcolnext < lx) && (krownext >= ky) && (krownext < ly))
        {
          if (ipts (krownext, kcolnext) == 0)
          {
            // next facet not marked yet
            cl_drawcn (X, Y, Z, flev, krownext, kcolnext,
                       locx[num], locy[num], inext, ipts);
          }
          else if (ipts (krownext, kcolnext) >= 2)
          {
            // we've been at next facet
            // check that we haven't crossed edge i previously
            if (ipts (krownext, kcolnext) - 2 != inext)
              cl_drawcn (X, Y, Z, flev, krownext, kcolnext,
                         locx[num], locy[num], inext, ipts);
          }
        }
        first = true;
        num++;
      }
    }
  }
}

bool check_edge(Matrix &Z, unsigned int r, unsigned int c, double lvl, bool isrow) 
{
  double chk;
  if (isrow)
    chk = (Z(r, c) - lvl) * (Z(r, c+1) - lvl);
  else
    chk = (Z(r, c) - lvl) * (Z(r+1, c) - lvl);
  if (chk <= 0.0)
    return true;
  else
    return false;
}

void cl_cntr (RowVector & X, RowVector & Y, Matrix & Z, double lvl)
{
  unsigned int r, c, nr = Z.rows(), nc = Z.cols();
  charMatrix ipts (nr, nc, 0);

  // find contours who starts at the edge
  for (c = 0; c < nc - 1; c++)
  {
    if (check_edge(Z, 0, c, lvl, true) && (ipts (0, c) != 1))
      cl_drawcn (X, Y, Z, lvl, 0, c, 0.0, 0.0, -2, ipts);
    if (check_edge(Z, nr-1, c, lvl, true) && (ipts (nr-2, c) != 1))
      cl_drawcn (X, Y, Z, lvl, nr-2, c, 0.0, 0.0, -2, ipts);
  }
  for (r = 0; r < nr - 1; r++)
  {
    if (check_edge(Z, r, 0, lvl, false) && (ipts (r, 0) != 1))
      cl_drawcn (X, Y, Z, lvl, r, 0, 0.0, 0.0, -2, ipts);
    if (check_edge(Z, r, nc-1, lvl, false) && (ipts (r, nc-2) != 1))
      cl_drawcn (X, Y, Z, lvl, r, nc-2, 0.0, 0.0, -2, ipts);
  }

  // continue with interior facets
  for (r = 0; r < nr - 1; r++)
    for (c = 0; c < nc - 1; c++)
      if (ipts (r, c) != 1)
        cl_drawcn (X, Y, Z, lvl, r, c, 0.0, 0.0, -2, ipts);
}

DEFUN_DLD (__contourc__, args, nargout, "")
{
  octave_value_list retval;
  int nargin = args.length ();

  if (nargin != 4)
    {
      error ("must have 4 inputs (x,y,z,levels)");
      return retval;
    }

  RowVector X = args (0).row_vector_value ();
  RowVector Y = args (1).row_vector_value ();
  Matrix Z = args (2).matrix_value ().transpose ();
  RowVector L = args (3).row_vector_value ();

  contourc.resize (2, 0);
  for (int i = 0; i < L.length (); i++)
    {
      cl_cntr (X, Y, Z, L (i));
    }
  cl_end_contour ();

  retval (0) = contourc;
  return retval;
}
