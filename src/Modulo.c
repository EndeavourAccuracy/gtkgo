/* gtkgo v0.0.12 (Modulo.c) (November 2022)
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

#include "Modulo.h"

/*****************************************************************************/
int Modulo (int iOne, int iTwo)
/*****************************************************************************/
{
	int iTemp;

	do {
		iTemp = iOne - iTwo;
		iOne = iTemp;
	} while (iOne > 0);
	if (iOne == 0)
	{
		return (0);
	} else {
		return (iOne + iTwo);
	}
}
/*****************************************************************************/
