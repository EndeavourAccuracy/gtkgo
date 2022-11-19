/* gtkgo v0.0.12 (Where.c) (November 2022)
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

#include "Where.h"

/*****************************************************************************/
int Where (int iAbove, int iUnder, int iRight, int iLeft)
/*****************************************************************************/
{
	int iRandom;

	if ((iAbove == 1) && (iUnder == 0) && (iRight == 0) && (iLeft == 0))
		return (1);
	if ((iAbove == 0) && (iUnder == 1) && (iRight == 0) && (iLeft == 0))
		return (2);
	if ((iAbove == 0) && (iUnder == 0) && (iRight == 1) && (iLeft == 0))
		return (3);
	if ((iAbove == 0) && (iUnder == 0) && (iRight == 0) && (iLeft == 1))
		return (4);
	if ((iAbove == 1) && (iUnder == 1) && (iRight == 0) && (iLeft == 0))
		return (1 + (int) (2.0 * rand() / (RAND_MAX + 1.0)));
	if ((iAbove == 0) && (iUnder == 1) && (iRight == 1) && (iLeft == 0))
		return (2 + (int) (2.0 * rand() / (RAND_MAX + 1.0)));
	if ((iAbove == 0) && (iUnder == 0) && (iRight == 1) && (iLeft == 1))
		return (3 + (int) (2.0 * rand() / (RAND_MAX + 1.0)));
	if ((iAbove == 1) && (iUnder == 0) && (iRight == 1) && (iLeft == 0))
	{
		iRandom = 1 + (int) (2.0 * rand() / (RAND_MAX + 1.0));
		if (iRandom == 1) return (1);
		if (iRandom == 2) return (3);
	}
	if ((iAbove == 0) && (iUnder == 1) && (iRight == 0) && (iLeft == 1))
	{
		iRandom = 1 + (int) (2.0 * rand() / (RAND_MAX + 1.0));
		if (iRandom == 1) return (2);
		if (iRandom == 2) return (4);
	}
	if ((iAbove == 1) && (iUnder == 0) && (iRight == 0) && (iLeft == 1))
	{
		iRandom = 1 + (int) (2.0 * rand() / (RAND_MAX + 1.0));
		if (iRandom == 1) return (1);
		if (iRandom == 2) return (4);
	}
	if ((iAbove == 1) && (iUnder == 1) && (iRight == 1) && (iLeft == 0))
		return (1 + (int) (3.0 * rand() / (RAND_MAX + 1.0)));
	if ((iAbove == 1) && (iUnder == 1) && (iRight == 0) && (iLeft == 1))
	{
		iRandom = 1 + (int) (3.0 * rand() / (RAND_MAX + 1.0));
		if (iRandom == 1) return (1);
		if (iRandom == 2) return (2);
		if (iRandom == 3) return (4);
	}
	if ((iAbove == 1) && (iUnder == 0) && (iRight == 1) && (iLeft == 1))
	{
		iRandom = 1 + (int) (3.0 * rand() / (RAND_MAX + 1.0));
		if (iRandom == 1) return (1);
		if (iRandom == 2) return (3);
		if (iRandom == 3) return (4);
	}
	if ((iAbove == 0) && (iUnder == 1) && (iRight == 1) && (iLeft == 1))
		return (2 + (int) (3.0 * rand() / (RAND_MAX + 1.0)));
	if ((iAbove == 1) && (iUnder == 1) && (iRight == 1) && (iLeft == 1))
		return (1 + (int) (4.0 * rand() / (RAND_MAX + 1.0)));

	return (0);
}
/*****************************************************************************/
