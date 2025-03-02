/****************************************************************************/
// This file is part of the gradLib library originally made by Stian Broen
//
// For more free libraries, please visit <http://broentech.no>
//
// gradLib is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this library.  If not, see <http://www.gnu.org/licenses/>
/****************************************************************************/

// local includes
#include "gradientarrow.h"

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	ctor
/*!
//
//  \param
//
//  \return N/A
//
//  \author Stian Broen
//
//  \date  20.05.2012
//
*/
//f-//////////////////////////////////////////////////////////////////////////
GradientArrow::GradientArrow()
{
   QPolygon area;
   area << QPoint(0,5) << QPoint(5, 0) << QPoint(10,5) << QPoint(10, 20) << QPoint(0,20) << QPoint(0,5);
   setArea(area);
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	dtor
/*!
//
//  \param
//
//  \return N/A
//
//  \author Stian Broen
//
//  \date  20.05.2012
//
*/
//f-//////////////////////////////////////////////////////////////////////////
GradientArrow::~GradientArrow(){}
