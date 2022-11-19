/* gtkgo v0.0.12 (FreePlace.c) (November 2022)
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

#include "FreePlace.h"

/*****************************************************************************/
int FreePlace (int iPoint, char cColor, char cType)
/*****************************************************************************/
{
	/* Returns 1 if iPoint (if cColor) is cType.
	 * Returns 0 if iPoint (if cColor) is not cType.
	 *
	 * cType:
	 * 'F' = Random free place, with all sides unoccupied.
	 * 'f' = Same as 'F', but touches color cColor at northeast, ... just ones.
	 * '!' = In own territory.
	 * '.' = In opponent's territory.
	 * 'M' = Random free place, but touches at least one point of color cColor.
	 */

	int iFree;
	int iOwn;
	char cColorOther;

	iFree = 0;

	switch (cColor)
	{
		case 'b': cColorOther = 'w'; break;
		case 'w': cColorOther = 'b'; break;
		default:
			/*** This fallback needs a better solution. ***/
			cColorOther = 'b'; break;
	}

	if (cType == 'F')
	{
		iFree = 0;
		if ((Modulo ((iPoint - 1), 19) != 0) && (Modulo (iPoint, 19) != 0)
			&& (iPoint >= 20) && (iPoint <= 342))
		{
			if (((Board[iPoint - 20][2] == 's') ||
				(Board[iPoint - 20][2] == 'e'))
			&& ((Board[iPoint - 19][2] == 's') ||
				(Board[iPoint - 19][2] == 'e'))
			&& ((Board[iPoint - 18][2] == 's') ||
				(Board[iPoint - 18][2] == 'e'))
			&& ((Board[iPoint - 1][2] == 's') ||
				(Board[iPoint - 1][2] == 'e'))
			&& ((Board[iPoint + 1][2] == 's') ||
				(Board[iPoint + 1][2] == 'e'))
			&& ((Board[iPoint + 18][2] == 's') ||
				(Board[iPoint + 18][2] == 'e'))
			&& ((Board[iPoint + 19][2] == 's') ||
				(Board[iPoint + 19][2] == 'e'))
			&& ((Board[iPoint + 20][2] == 's') ||
				(Board[iPoint + 20][2] == 'e'))
			&& (Board[iPoint][2] != 'b') && (Board[iPoint][2] != 'w'))
			{
				iFree = 1;
			}
		}
	}

	if (cType == 'f')
	{
		iFree = 0;
		iOwn = 0;
		if (Modulo ((iPoint - 1), 19) != 0)
		{
			if ((Board[iPoint - 1][2] == 's') || (Board[iPoint - 1][2] == 'e'))
			{
				iFree++;
			}
			if (iPoint >= 21)
			{
				if (Board[iPoint - 20][2] == cColor)
					iOwn++;
			}
			if (iPoint <= 342)
			{
				if (Board[iPoint + 18][2] == cColor)
					iOwn++;
			}
		} else iFree++;
		if (Modulo (iPoint, 19) != 0)
		{
			if ((Board[iPoint + 1][2] == 's') || (Board[iPoint + 1][2] == 'e'))
			{
				iFree++;
			}
			if (iPoint >= 20)
			{
				if (Board[iPoint - 18][2] == cColor)
					iOwn++;
			}
			if (iPoint <= 343)
			{
				if (Board[iPoint + 20][2] == cColor)
					iOwn++;
			}
		} else iFree++;
		if (iPoint >= 20)
		{
			if ((Board[iPoint - 19][2] == 's') ||
				(Board[iPoint - 19][2] == 'e'))
				iFree++;
		} else iFree++;
		if (iPoint <= 342)
		{
			if ((Board[iPoint + 19][2] == 's') ||
				(Board[iPoint + 19][2] == 'e'))
				iFree++;
		} else iFree++;
		if ((iOwn == 1)
		&& (iFree == 4)
		&& (Board[iPoint][2] != 'b')
		&& (Board[iPoint][2] != 'w'))
		{
			iFree = 1;
		} else {
			iFree = 0;
		}
	}

	if (cType == '!')
	{
		iFree = 0;
		if (Modulo ((iPoint - 1), 19) != 0)
		{
			if (Board[iPoint - 1][2] == cColor)
			{
				iFree++;
			}
		} else iFree++;
		if (Modulo (iPoint, 19) != 0)
		{
			if (Board[iPoint + 1][2] == cColor)
			{
				iFree++;
			}
		} else iFree++;
		if (iPoint >= 20)
		{
			if (Board[iPoint - 19][2] == cColor)
				iFree++;
		} else iFree++;
		if (iPoint <= 342)
		{
			if (Board[iPoint + 19][2] == cColor)
				iFree++;
		} else iFree++;
		if (((iFree == 3) || (iFree == 4))
			&& (NotSuicide (iPoint, cColorOther) == 0)
			&& (Board[iPoint][2] != 'b')
			&& (Board[iPoint][2] != 'w'))
		{
			iFree = 1;
		} else {
			iFree = 0;
		}
	}

	if (cType == '.')
	{
		iFree = 0;
		if (Modulo ((iPoint - 1), 19) != 0)
		{
			if (Board[iPoint - 1][2] == cColorOther)
			{
				iFree++;
			}
		} else iFree++;
		if (Modulo (iPoint, 19) != 0)
		{
			if (Board[iPoint + 1][2] == cColorOther)
			{
				iFree++;
			}
		} else iFree++;
		if (iPoint >= 20)
		{
			if (Board[iPoint - 19][2] == cColorOther)
				iFree++;
		} else iFree++;
		if (iPoint <= 342)
		{
			if (Board[iPoint + 19][2] == cColorOther)
				iFree++;
		} else iFree++;
		if ((iFree > 1)
		&& (Board[iPoint][2] != 'b')
		&& (Board[iPoint][2] != 'w'))
		{
			iFree = 1;
		} else {
			iFree = 0;
		}
	}

	if (cType == 'M')
	{
		iFree = 0;
		if (Modulo ((iPoint - 1), 19) != 0)
		{
			if (Board[iPoint - 1][2] == cColor)
				iFree++;
		}
		if (Modulo (iPoint, 19) != 0)
		{
			if (Board[iPoint + 1][2] == cColor)
				iFree++;
		}
		if (iPoint >= 20)
		{
			if (Board[iPoint - 19][2] == cColor)
				iFree++;
		}
		if (iPoint <= 342)
		{
			if (Board[iPoint + 19][2] == cColor)
				iFree++;
		}
		if ((iFree > 1)
		&& (Board[iPoint][2] != 'b')
		&& (Board[iPoint][2] != 'w'))
		{
			iFree = 1;
		} else {
			iFree = 0;
		}
	}

	return (iFree);
}
/*****************************************************************************/
