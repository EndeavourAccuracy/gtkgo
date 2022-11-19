/* gtkgo v0.0.12 (ChangePoint.c) (November 2022)
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

#include "ChangePoint.h"

/*****************************************************************************/
int ChangePoint (int iPoint, char cColor)
/*****************************************************************************/
{
	/* Returns 1 if iPoint was successfully changed to
	 * cColor ('b' for black, 'w' for white, 'e' for empty).
	 * Returns 0 if it was not.
	 */

	int iChanged;
	int iPointLoop;
	char sLatest[2 + 2];
	char sMessage[MAX_MESSAGE + 2];

	iChanged = 1;

	if ((HistoryLastRemoved[iMovesMade] == iPoint) &&
		(WouldSurround (iPoint, cColor) == 1))
	{
		return (0);
	}

	/*** If necessary, avoid the border. ***/
	if ((iMoveNotSide == 1) && (iMoveAlt != 1))
	{
		if ((Modulo ((iPoint - 1), 19) == 0) ||
			(Modulo (iPoint, 19) == 0) ||
			(iPoint <= 19) ||
			(iPoint >= 343))
		{
			return (0);
		}
	}

	/*** If necessary, avoid your own territory. ***/
	if ((iMoveNotOwn == 1) && (iMoveAlt != 1))
	{
		if (FreePlace (iPoint, cColor, '!') == 1)
		{
			return (0);
		}
	}

	/*** If necessary, avoid the opponent's territory. ***/
	if ((iMoveNotOther == 1) && (iMoveAlt != 1))
	{
		if (FreePlace (iPoint, cColor, '.') == 1)
		{
			return (0);
		}
	}

	/*** Change empty to color. ***/
	if ((cColor == 'b') || (cColor == 'w'))
	{
		if ((Board[iPoint][2] == 'e') || (Board[iPoint][2] == 's'))
		{
			if ((CheckSides (iPoint, cColor, 1) != 15) ||
				((NotSuicide (iPoint, cColor) == 1) &&
				(CheckSides (iPoint, cColor, 1) == 15)))
			{
				if (iLatest == 1)
					{ snprintf (sLatest, 2, "%s", "l"); }
						else { snprintf (sLatest, 2, "%s", ""); }
				snprintf (Board[iPoint], MAX_I, "%c%c%c%s",
					Board[iPoint][0], Board[iPoint][1], cColor, sLatest);
			} else {
				Message ("Suicides (self-captures) are forbidden.", 3, 0);
				iChanged = 0;
			}
		} else {
			snprintf (sMessage, MAX_MESSAGE, "Point %s is not empty.",
				PointToPlace (2, iPoint));
			Message (sMessage, 3, 0);
			iChanged = 0;
		}
	}

	/*** Change color to empty. ***/
	if (cColor == 'e')
	{
		if ((strcmp (Board[iPoint], "mmw") == 0) ||
			(strcmp (Board[iPoint], "mmb") == 0) ||
			(strcmp (Board[iPoint], "mmwl") == 0) ||
			(strcmp (Board[iPoint], "mmbl") == 0))
		{
			if ((iPoint == 61) || (iPoint == 67) || (iPoint == 73) ||
				(iPoint == 175) || (iPoint == 181) || (iPoint == 187) ||
				(iPoint == 289) || (iPoint == 295) || (iPoint == 301))
			{
				snprintf (Board[iPoint], MAX_I, "%s", "mms");
			} else {
				snprintf (Board[iPoint], MAX_I, "%s", "mme");
			}
		}
		if ((strcmp (Board[iPoint], "ltw") == 0) ||
			(strcmp (Board[iPoint], "ltb") == 0) ||
			(strcmp (Board[iPoint], "ltwl") == 0) ||
			(strcmp (Board[iPoint], "ltbl") == 0))
			{ snprintf (Board[iPoint], MAX_I, "%s", "lte"); }
		if ((strcmp (Board[iPoint], "luw") == 0) ||
			(strcmp (Board[iPoint], "lub") == 0) ||
			(strcmp (Board[iPoint], "luwl") == 0) ||
			(strcmp (Board[iPoint], "lubl") == 0))
			{ snprintf (Board[iPoint], MAX_I, "%s", "lue"); }
		if ((strcmp (Board[iPoint], "rtw") == 0) ||
			(strcmp (Board[iPoint], "rtb") == 0) ||
			(strcmp (Board[iPoint], "rtwl") == 0) ||
			(strcmp (Board[iPoint], "rtbl") == 0))
			{ snprintf (Board[iPoint], MAX_I, "%s", "rte"); }
		if ((strcmp (Board[iPoint], "ruw") == 0) ||
			(strcmp (Board[iPoint], "rub") == 0) ||
			(strcmp (Board[iPoint], "ruwl") == 0) ||
			(strcmp (Board[iPoint], "rubl") == 0))
			{ snprintf (Board[iPoint], MAX_I, "%s", "rue"); }
		if ((strcmp (Board[iPoint], "lmw") == 0) ||
			(strcmp (Board[iPoint], "lmb") == 0) ||
			(strcmp (Board[iPoint], "lmwl") == 0) ||
			(strcmp (Board[iPoint], "lmbl") == 0))
			{ snprintf (Board[iPoint], MAX_I, "%s", "lme"); }
		if ((strcmp (Board[iPoint], "mtw") == 0) ||
			(strcmp (Board[iPoint], "mtb") == 0) ||
			(strcmp (Board[iPoint], "mtwl") == 0) ||
			(strcmp (Board[iPoint], "mtbl") == 0))
			{ snprintf (Board[iPoint], MAX_I, "%s", "mte"); }
		if ((strcmp (Board[iPoint], "rmw") == 0) ||
			(strcmp (Board[iPoint], "rmb") == 0) ||
			(strcmp (Board[iPoint], "rmwl") == 0) ||
			(strcmp (Board[iPoint], "rmbl") == 0))
			{ snprintf (Board[iPoint], MAX_I, "%s", "rme"); }
		if ((strcmp (Board[iPoint], "muw") == 0) ||
			(strcmp (Board[iPoint], "mub") == 0) ||
			(strcmp (Board[iPoint], "muwl") == 0) ||
			(strcmp (Board[iPoint], "mubl") == 0))
			{ snprintf (Board[iPoint], MAX_I, "%s", "mue"); }
	}

	if (iChanged == 1)
	{
		/*** Remove our "latest" marker from non-iPoint stones. ***/
		for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
		{
			if ((Board[iPointLoop][3] == 'l') && (Board[iPointLoop][2] == cColor) &&
				(iPoint != iPointLoop))
			{
				Board[iPointLoop][3] = '\0';
				ChangePixmap (iPointLoop);
			}
		}

		/*** Update the image. ***/
		ChangePixmap (iPoint);

		iRemoved = 0;

		/*** Set iLastMove* and play a move sound. ***/
		switch (cColor)
		{
			case 'b':
				iLastMoveB = iPoint;
				if (iOptions == 0) { Play ("blackm.ogg", 0); }
				break;
			case 'w':
				iLastMoveW = iPoint;
				if (iOptions == 0) { Play ("whitem.ogg", 0); }
				break;
		}

		iMoveMade = 1;
	}

	/* If necessary, send the computer-generated hint to the
	 * Internet opponent.
	 */
	if ((iConnected == 1) && (iSendHint == 1))
	{
		SendData (1, PointToPlace (2, iPoint));
	}

	return (iChanged);
}
/*****************************************************************************/
