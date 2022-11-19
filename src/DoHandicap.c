/* gtkgo v0.0.12 (DoHandicap.c) (November 2022)
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

#include "DoHandicap.h"

/*****************************************************************************/
void DoHandicap (void)
/*****************************************************************************/
{
	int iPointLoop;

	iJustRestarted = 1;

	/*** Clear the board. ***/
	for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
	{
		if ((Board[iPointLoop][2] == 'w') || (Board[iPointLoop][2] == 'b'))
		{
			ChangePoint (iPointLoop, 'e');
		}
	}

	if ((iHandicap == 0) && (iIsComputerB == 1))
	{
		Computer ('b');
		JudgeBoard ('w');
	}

	/*** Top right, only for Internet play. ***/
	if ((iHandicap == 1) && (iConnected == 1))
	{
		snprintf (Board[73], MAX_I, "%s", "mmb"); ChangePixmap (73);
	}

	if (iHandicap == 2)
	{
		snprintf (Board[73], MAX_I, "%s", "mmb"); ChangePixmap (73);
		snprintf (Board[289], MAX_I, "%s", "mmb"); ChangePixmap (289);
	}

	if (iHandicap == 3)
	{
		snprintf (Board[61], MAX_I, "%s", "mmb"); ChangePixmap (61);
		snprintf (Board[73], MAX_I, "%s", "mmb"); ChangePixmap (73);
		snprintf (Board[289], MAX_I, "%s", "mmb"); ChangePixmap (289);
	}

	if (iHandicap == 4)
	{
		snprintf (Board[61], MAX_I, "%s", "mmb"); ChangePixmap (61);
		snprintf (Board[301], MAX_I, "%s", "mmb"); ChangePixmap (301);
		snprintf (Board[73], MAX_I, "%s", "mmb"); ChangePixmap (73);
		snprintf (Board[289], MAX_I, "%s", "mmb"); ChangePixmap (289);
	}

	if (iHandicap == 5)
	{
		snprintf (Board[61], MAX_I, "%s", "mmb"); ChangePixmap (61);
		snprintf (Board[301], MAX_I, "%s", "mmb"); ChangePixmap (301);
		snprintf (Board[73], MAX_I, "%s", "mmb"); ChangePixmap (73);
		snprintf (Board[289], MAX_I, "%s", "mmb"); ChangePixmap (289);
		snprintf (Board[181], MAX_I, "%s", "mmb"); ChangePixmap (181);
	}

	if (iHandicap == 6)
	{
		snprintf (Board[61], MAX_I, "%s", "mmb"); ChangePixmap (61);
		snprintf (Board[301], MAX_I, "%s", "mmb"); ChangePixmap (301);
		snprintf (Board[73], MAX_I, "%s", "mmb"); ChangePixmap (73);
		snprintf (Board[289], MAX_I, "%s", "mmb"); ChangePixmap (289);
		snprintf (Board[175], MAX_I, "%s", "mmb"); ChangePixmap (175);
		snprintf (Board[187], MAX_I, "%s", "mmb"); ChangePixmap (187);
	}

	if (iHandicap == 7)
	{
		snprintf (Board[61], MAX_I, "%s", "mmb"); ChangePixmap (61);
		snprintf (Board[301], MAX_I, "%s", "mmb"); ChangePixmap (301);
		snprintf (Board[73], MAX_I, "%s", "mmb"); ChangePixmap (73);
		snprintf (Board[289], MAX_I, "%s", "mmb"); ChangePixmap (289);
		snprintf (Board[175], MAX_I, "%s", "mmb"); ChangePixmap (175);
		snprintf (Board[187], MAX_I, "%s", "mmb"); ChangePixmap (187);
		snprintf (Board[181], MAX_I, "%s", "mmb"); ChangePixmap (181);
	}

	if (iHandicap >= 8)
	{
		snprintf (Board[61], MAX_I, "%s", "mmb"); ChangePixmap (61);
		snprintf (Board[301], MAX_I, "%s", "mmb"); ChangePixmap (301);
		snprintf (Board[73], MAX_I, "%s", "mmb"); ChangePixmap (73);
		snprintf (Board[289], MAX_I, "%s", "mmb"); ChangePixmap (289);
		snprintf (Board[175], MAX_I, "%s", "mmb"); ChangePixmap (175);
		snprintf (Board[187], MAX_I, "%s", "mmb"); ChangePixmap (187);
		snprintf (Board[67], MAX_I, "%s", "mmb"); ChangePixmap (67);
		snprintf (Board[295], MAX_I, "%s", "mmb"); ChangePixmap (295);
	}

	if (iHandicap >= 9)
	{
		snprintf (Board[181], MAX_I, "%s", "mmb"); ChangePixmap (181);
	}

	if (iHandicap >= 10)
	{
		snprintf (Board[41], MAX_I, "%s", "mmb"); ChangePixmap (41);
	}

	if (iHandicap >= 11)
	{
		snprintf (Board[321], MAX_I, "%s", "mmb"); ChangePixmap (321);
	}

	if (iHandicap >= 12)
	{
		snprintf (Board[55], MAX_I, "%s", "mmb"); ChangePixmap (55);
	}

	if (iHandicap >= 13)
	{
		snprintf (Board[307], MAX_I, "%s", "mmb"); ChangePixmap (307);
	}

	if (iHandicap >= 14)
	{
		snprintf (Board[121], MAX_I, "%s", "mmb"); ChangePixmap (121);
	}

	if (iHandicap >= 15)
	{
		snprintf (Board[241], MAX_I, "%s", "mmb"); ChangePixmap (241);
	}

	if (iHandicap >= 16)
	{
		snprintf (Board[127], MAX_I, "%s", "mmb"); ChangePixmap (127);
	}

	if (iHandicap == 17)
	{
		snprintf (Board[235], MAX_I, "%s", "mmb"); ChangePixmap (235);
	}

	iLastMoveB = 1000;

	if (iHandicap != 0)
	{
		JudgeBoard ('w');
	} else {
		iHandicapStart = 0;
		StatusBar();
	}

	if ((iHandicap != 0) && (iIsComputerW == 1))
	{
		Computer ('w');
		JudgeBoard ('b');
	}
}
/*****************************************************************************/
