/* gtkgo v0.0.12 (MyLand.c) (November 2022)
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

#include "MyLand.h"

/*****************************************************************************/
int MyLand (char cColor)
/*****************************************************************************/
{
	int iPointLoop;
	int iReturnScore;
	int iCheckChanged;
	int arCheck[POINTS + 2];

	iReturnScore = 0;

	for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
	{
		arCheck[iPointLoop] = 0;
	}

	for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
	{
		if ((Board[iPointLoop][2] == 'e') || (Board[iPointLoop][2] == 's'))
		{
			if ((Board[iPointLoop - 1][2] == 'b') ||
				(Board[iPointLoop + 1][2] == 'b') ||
				(Board[iPointLoop - 19][2] == 'b') ||
				(Board[iPointLoop + 19][2] == 'b'))
			{
				arCheck[iPointLoop]+=1;
			}
			if ((Board[iPointLoop - 1][2] == 'w') ||
				(Board[iPointLoop + 1][2] == 'w') ||
				(Board[iPointLoop - 19][2] == 'w') ||
				(Board[iPointLoop + 19][2] == 'w'))
			{
				arCheck[iPointLoop]+=2;
			}
		} else {
			if (Board[iPointLoop][2] == 'b')
			{
				arCheck[iPointLoop] = 4;
			}
			if (Board[iPointLoop][2] == 'w')
			{
				arCheck[iPointLoop] = 5;
			}
		}
	}

	/*** Make every 0 connecting 1 -> 1 ***/
	do
	{
		iCheckChanged = 0;
		for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
		{
			if (arCheck[iPointLoop] == 1)
			{
				if ((arCheck[iPointLoop - 1] == 0) &&
					(Modulo (iPointLoop - 1, 19) != 0))
				{
					arCheck[iPointLoop - 1] = 1;
					iCheckChanged = 1;
				}
				if ((arCheck[iPointLoop + 1] == 0) && (Modulo (iPointLoop, 19) != 0))
				{
					arCheck[iPointLoop + 1] = 1;
					iCheckChanged = 1;
				}
				if ((arCheck[iPointLoop - 19] == 0) && (iPointLoop > 19))
				{
					arCheck[iPointLoop - 19] = 1;
					iCheckChanged = 1;
				}
				if ((arCheck[iPointLoop + 19] == 0) && (iPointLoop < 343))
				{
					arCheck[iPointLoop + 19] = 1;
					iCheckChanged = 1;
				}
			}
		}
	} while (iCheckChanged != 0);

	/*** Make every 0 connecting 2 -> 2 ***/
	do
	{
		iCheckChanged = 0;
		for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
		{
			if (arCheck[iPointLoop] == 2)
			{
				if ((arCheck[iPointLoop - 1] == 0) &&
					(Modulo (iPointLoop - 1, 19) != 0))
				{
					arCheck[iPointLoop - 1] = 2;
					iCheckChanged = 1;
				}
				if ((arCheck[iPointLoop + 1] == 0) && (Modulo (iPointLoop, 19) != 0))
				{
					arCheck[iPointLoop + 1] = 2;
					iCheckChanged = 1;
				}
				if ((arCheck[iPointLoop - 19] == 0) && (iPointLoop > 19))
				{
					arCheck[iPointLoop - 19] = 2;
					iCheckChanged = 1;
				}
				if ((arCheck[iPointLoop + 19] == 0) && (iPointLoop < 343))
				{
					arCheck[iPointLoop + 19] = 2;
					iCheckChanged = 1;
				}
			}
		}
	} while (iCheckChanged != 0);

	/*** Make every 1 connecting 2 -> 3 ***/
	do
	{
		iCheckChanged = 0;
		for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
		{
			if (arCheck[iPointLoop] == 1)
			{
				if ((arCheck[iPointLoop - 1] == 2) &&
					(Modulo (iPointLoop - 1, 19) != 0))
				{
					arCheck[iPointLoop - 1] = 3;
					iCheckChanged = 1;
				}
				if ((arCheck[iPointLoop + 1] == 2) && (Modulo (iPointLoop, 19) != 0))
				{
					arCheck[iPointLoop + 1] = 3;
					iCheckChanged = 1;
				}
				if ((arCheck[iPointLoop - 19] == 2) && (iPointLoop > 19))
				{
					arCheck[iPointLoop - 19] = 3;
					iCheckChanged = 1;
				}
				if ((arCheck[iPointLoop + 19] == 2) && (iPointLoop < 343))
				{
					arCheck[iPointLoop + 19] = 3;
					iCheckChanged = 1;
				}
			}
		}
	} while (iCheckChanged != 0);

	/*** Make every 0, 1 and 2 connecting 3 -> 3 ***/
	do
	{
		iCheckChanged = 0;
		for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
		{
			if (arCheck[iPointLoop] == 3)
			{
				if ((arCheck[iPointLoop - 1] < 3) &&
					(Modulo (iPointLoop - 1, 19) != 0))
				{
					arCheck[iPointLoop - 1] = 3;
					iCheckChanged = 1;
				}
				if ((arCheck[iPointLoop + 1] < 3) && (Modulo (iPointLoop, 19) != 0))
				{
					arCheck[iPointLoop + 1] = 3;
					iCheckChanged = 1;
				}
				if ((arCheck[iPointLoop - 19] < 3) && (iPointLoop > 19))
				{
					arCheck[iPointLoop - 19] = 3;
					iCheckChanged = 1;
				}
				if ((arCheck[iPointLoop + 19] < 3) && (iPointLoop < 343))
				{
					arCheck[iPointLoop + 19] = 3;
					iCheckChanged = 1;
				}
			}
		}
	} while (iCheckChanged != 0);

	for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
	{
		if (cColor == 'b')
		{
			if (arCheck[iPointLoop] == 1)
			{
				iReturnScore++;
			}
		}
		if (cColor == 'w')
		{
			if (arCheck[iPointLoop] == 2)
			{
				iReturnScore++;
			}
		}
	}
	return (iReturnScore);
}
/*****************************************************************************/
