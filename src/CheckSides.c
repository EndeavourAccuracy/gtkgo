/* gtkgo v0.0.12 (CheckSides.c) (November 2022)
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

#include "CheckSides.h"

/*****************************************************************************/
int CheckSides (int iPoint, char cColor, int iType)
/*****************************************************************************/
{
	/* Use iType = 0 to call CheckSides() from within itself.
	 *
	 * iType:
	 * 0, 1, 2 = Returns the total of under (8), above (4), right (2) and
	 * left (1) of iPoint (if of color cColor) where it has no exit.
	 * 3 = Returns the number of stones in the group where iPoint (if of
	 * color cColor) is a part of.
	 *
	 * There is currently no difference between using iType 1 and 2.
	 */

	int iPointLoop;
	int iEmptyType;
	char cColorOther;

	iEmptyType = 0;

	if ((iType > 0) && (iType < 4)) /*** 1, 2, 3 ***/
	{
		iChecked = 0;

		/*** Temporarily make the point cColor if it is empty. ***/
		if (Board[iPoint][2] != cColor)
		{
			switch (Board[iPoint][2])
			{
				case 'e': iEmptyType = 1; break;
				case 's': iEmptyType = 2; break;
			}
			Board[iPoint][2] = cColor;
		}

		for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
		{
			arReturn[iPointLoop] = 0;
			Checked[iPointLoop] = 0;
		}
	}

	if (Checked[iPoint] == 1)
	{
		return (15);
	}
	Checked[iPoint] = 1;
	iChecked++;

	/*** Set cColorOther. ***/
	if (cColor == 'w')
		{ cColorOther = 'b'; }
			else { cColorOther = 'w'; }

	/*** Check left. ***/
	if ((Modulo ((iPoint - 1), 19) == 0) /*** border ***/
		|| (Checked[iPoint - 1] == 2) /*** already checked ***/
		|| ((Modulo ((iPoint - 1), 19) != 0)
			&& (Board[iPoint - 1][2] == cColorOther)) /*** opponent ***/
		|| ((Modulo ((iPoint - 1), 19) != 0)
			&& (Board[iPoint - 1][2] == cColor)
			&& (CheckSides ((iPoint - 1),
			cColor, 0) == 15))) /*** us, but surrounded ***/
	{
		arReturn[iPoint]+=1; /*** The left side has no exit. ***/
	} else {
		Checked[iPoint - 1] = 2; /*** Set left to already checked. ***/
	}

	/*** Check right. ***/
	if ((Modulo ((iPoint), 19) == 0)
		|| (Checked[iPoint + 1] == 2)
		|| ((Modulo ((iPoint), 19) != 0)
			&& (Board[iPoint + 1][2] == cColorOther))
		|| ((Modulo ((iPoint), 19) != 0)
			&& (Board[iPoint + 1][2] == cColor)
			&& (CheckSides ((iPoint + 1), cColor, 0) == 15)))
	{
		arReturn[iPoint]+=2;
	} else {
		Checked[iPoint + 1] = 2;
	}

	/*** Check above. ***/
	if (((iPoint >= 1) && (iPoint <= 19))
		|| (Checked[iPoint - 19] == 2)
		|| ((iPoint > 19)
			&& (Board[iPoint - 19][2] == cColorOther))
		|| ((iPoint > 19)
			&& (Board[iPoint - 19][2] == cColor)
			&& (CheckSides ((iPoint - 19), cColor, 0) == 15)))
	{
		arReturn[iPoint]+=4;
	} else {
		Checked[iPoint - 19] = 2;
	}

	/*** Check under. ***/
	if (((iPoint >= 343) && (iPoint <= 361))
		|| (Checked[iPoint + 19] == 2)
		|| ((iPoint < 343)
			&& (Board[iPoint + 19][2] == cColorOther))
		|| ((iPoint < 343)
			&& (Board[iPoint + 19][2] == cColor)
			&& (CheckSides ((iPoint + 19), cColor, 0) == 15)))
	{
		arReturn[iPoint]+=8;
	} else {
		Checked[iPoint + 19] = 2;
	}

	if ((iType == 1) || (iType == 2)) /*** 1, 2 ***/
	{
		switch (iEmptyType)
		{
			case 1: Board[iPoint][2] = 'e'; break;
			case 2: Board[iPoint][2] = 's'; break;
		}
	}

	if (iType == 3)
	{
		return (iChecked);
	} else {
		return (arReturn[iPoint]);
	}
}
/*****************************************************************************/
