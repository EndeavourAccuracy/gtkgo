/* gtkgo v0.0.12 (WouldSurround.c) (November 2022)
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

#include "WouldSurround.h"

/*****************************************************************************/
int WouldSurround (int iPoint, char cColor)
/*****************************************************************************/
{
	/* Returns 0 if the point is not empty.
	 * Otherwise it returns how many of the opponent's stones would be
	 * surrounded if iPoint would be cColor.
	 */

	int iCounter;
	int iPointLoop;
	char cColorOther;
	char cEmptyType;

	iCounter = 0;

	/*** Temporarily make the point cColor if it is empty. ***/
	switch (Board[iPoint][2])
	{
		case 'e': cEmptyType = 'e'; break;
		case 's': cEmptyType = 's'; break;
		default: return (0);
	}
	Board[iPoint][2] = cColor;

	switch (cColor)
	{
		case 'b': cColorOther = 'w'; break;
		case 'w': cColorOther = 'b'; break;
		default:
			printf ("[FAILED] Strange cColor for WouldSurround(): %c!\n", cColor);
			exit (EXIT_ERROR);
	}

	/*** Count the number of surrounded stones. ***/
	for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
	{
		if (Board[iPointLoop][2] == cColorOther)
		{
			if (CheckSides (iPointLoop, cColorOther, 2) == 15) /*** surrounded ***/
			{
				iCounter++;
			}
		}
	}

	/*** Make the point empty again. ***/
	Board[iPoint][2] = cEmptyType;

	return (iCounter);
}
/*****************************************************************************/
