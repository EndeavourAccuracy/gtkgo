/* gtkgo v0.0.12 (NotSuicide.c) (November 2022)
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

#include "NotSuicide.h"

/*****************************************************************************/
int NotSuicide (int iPoint, char cColor)
/*****************************************************************************/
{
	/* Checks if placing a stone of cColor at iPoint would surround (capture)
	 * at least one neighboring stone of the opponent. If so, a stone of
	 * cColor may be placed at iPoint even if CheckSides() returns 15.
	 */

	int iReturn;
	int iEmptyType;
	char cColorOther;

	iEmptyType = 0;
	iReturn = 0;

	if (cColor == 'b')
	{
		cColorOther = 'w';
	} else {
		cColorOther = 'b';
	}

	if (Board[iPoint][2] != cColor)
	{
		if (Board[iPoint][2] == 'e')
		{
			iEmptyType = 1;
		}
		if (Board[iPoint][2] == 's')
		{
			iEmptyType = 2;
		}
		if ((iEmptyType == 1) || (iEmptyType == 2))
		{
			snprintf (Board[iPoint], MAX_I, "%c%c%c", Board[iPoint][0],
				Board[iPoint][1], cColor);
		}
	}

	/*** left ***/
	if (Modulo (iPoint - 1, 19) != 0)
	{
		if (Board[iPoint - 1][2] == cColorOther)
		{
			if (CheckSides (iPoint - 1, cColorOther, 1) == 15)
				iReturn = 1;
		}
	}

	/*** right ***/
	if (Modulo (iPoint, 19) != 0)
	{
		if (Board[iPoint + 1][2] == cColorOther)
		{
			if (CheckSides (iPoint + 1, cColorOther, 1) == 15)
				iReturn = 1;
		}
	}

	/*** above ***/
	if (iPoint >= 20)
	{
		if (Board[iPoint - 19][2] == cColorOther)
		{
			if (CheckSides (iPoint - 19, cColorOther, 1) == 15)
				iReturn = 1;
		}
	}

	/*** under ***/
	if (iPoint <= 342)
	{
		if (Board[iPoint + 19][2] == cColorOther)
		{
			if (CheckSides (iPoint + 19, cColorOther, 1) == 15)
				iReturn = 1;
		}
	}

	if (iEmptyType == 1)
	{
		snprintf (Board[iPoint], MAX_I, "%c%c%c", Board[iPoint][0],
			Board[iPoint][1], 'e');
	}
	if (iEmptyType == 2)
	{
		snprintf (Board[iPoint], MAX_I, "%c%c%c", Board[iPoint][0],
			Board[iPoint][1], 's');
	}

	return (iReturn);
}
/*****************************************************************************/
