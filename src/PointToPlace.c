/* gtkgo v0.0.12 (PointToPlace.c) (November 2022)
 * Copyright (C) 1998-2022 Norbert de Jonge <nlmdejonge@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this game; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#include "PointToPlace.h"

/*****************************************************************************/
char* PointToPlace (int iType, int iPoint)
/*****************************************************************************/
{
	/* Returns the selected iPoint in SGF (iType = 1) or
	 * go format (iType = 2).
	 */

	char sPlaceX[5], sPlaceY[5];
	int iCountX, iCountY;

	/*** Convert iPoint to iCountX and iCountY. ***/
	iCountY = 1;
	iCountX = iPoint;
	while (iCountX > 19)
	{
		iCountX-=19;
		iCountY++;
	}

	switch (iType)
	{
		case 1:
			snprintf (sPlaceX, MAX_I, "%c", (96 + iCountX)); /*** a-s ***/
			snprintf (sPlaceY, MAX_I, "%c", (96 + iCountY)); /*** a-s ***/
			break;
		case 2:
			if (iCountX > 8) { iCountX++; } /*** Skip I. ***/
			snprintf (sPlaceX, MAX_I, "%c", (64 + iCountX)); /*** A-S ***/
			snprintf (sPlaceY, MAX_I, "%i", (20 - iCountY)); /*** 19-1 ***/
			break;
		default:
			printf ("[ WARN ] Unknown iType for PointToPlace(): %i!\n", iType);
			snprintf (sPlaceX, MAX_I, "%s", "?");
			snprintf (sPlaceY, MAX_I, "%s", "?");
	}

	snprintf (sBoardPlace, MAX_I, "%s%s", sPlaceX, sPlaceY);

	return (sBoardPlace);
}
/*****************************************************************************/
