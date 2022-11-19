/* gtkgo v0.0.12 (JudgeBoard.c) (November 2022)
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

#include "JudgeBoard.h"

/*****************************************************************************/
void JudgeBoard (char cColorOther)
/*****************************************************************************/
{
	/*** cColorOther is the opponent's color. ***/

	int iLookForColor;
	int iRemoveLoop;
	int iPointLoop;
	int iRemoveDone;

	iRemoveDone = 0;

	/*** Remove stones that are surrounded. ***/
	for (iLookForColor = 1; iLookForColor <= POINTS; iLookForColor++)
	{
		if (Board[iLookForColor][2] == cColorOther)
		{
			if (CheckSides (iLookForColor, cColorOther, 2) == 15)
			{
				iRemoved = 0;
				for (iRemoveLoop = 1; iRemoveLoop <= POINTS; iRemoveLoop++)
				{
					if (Checked[iRemoveLoop] == 1) /*** Surrounded. ***/
					{
						if (cColorOther == 'b')
						{
							iCapturedB++;
						} else {
							iCapturedW++;
						}
						iMoveAlt = 1;
						ChangePoint (iRemoveLoop, 'e');
						iMoveAlt = 0;
						iRemoveDone = iRemoveLoop;
						iRemoved++;
						StatusBar();
					}
				}
			}
		}
	}

	/*** Increase the moves counter. ***/
	iMovesMade++;

	if (iMovesMade == 1)
	{
		/*** Store the color of the player who moved first. ***/
		switch (cColorOther)
		{
			case 'b': cColorFirstPlayer = 'w'; break;
			case 'w': cColorFirstPlayer = 'b'; break;
		}

		/*** Set time limit variables. ***/
		iOutOfTimeAtB = (iTimeLimit * 60) + (unsigned)time(&tmTime);
		iOutOfTimeAtW = (iTimeLimit * 60) + (unsigned)time(&tmTime);
		iTimeLeftBSCalc = iTimeLimit * 60;
		iTimeLeftWSCalc = iTimeLimit * 60;
	} else {
		if (Modulo (iMovesMade, 2) == 0)
		{
			iOutOfTimeAtB+=(unsigned)time(&tmTime) - iTurnStartTime;
		} else {
			iOutOfTimeAtW+=(unsigned)time(&tmTime) - iTurnStartTime;
		}
	}

	iTurnStartTime = (unsigned)time(&tmTime);

	if (iRemoved == 1)
	{
		HistoryLastRemoved[iMovesMade] = iRemoveDone;
	} else {
		HistoryLastRemoved[iMovesMade] = 0;
	}
	HistoryCapturedW[iMovesMade] = iCapturedW;
	HistoryCapturedB[iMovesMade] = iCapturedB;

	for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
	{
		if (((cColorOther == 'b') && (iPointLoop == iLastMoveW) &&
			(Board[iPointLoop][3] != 'l')) ||
			((cColorOther == 'w') && (iPointLoop == iLastMoveB) &&
			(Board[iPointLoop][3] != 'l')))
		{
			Board[iPointLoop][3] = 'l';
		}
		snprintf (HistoryMoves[iMovesMade][iPointLoop], MAX_I, "%s",
			Board[iPointLoop]);
	}

	if (cColorOther == 'w')
	{
		HistoryTime[iMovesMade] = iOutOfTimeAtB - (unsigned)time(&tmTime);
	} else {
		HistoryTime[iMovesMade] = iOutOfTimeAtW - (unsigned)time(&tmTime);
	}

	if (HistoryTime[iMovesMade] < 0)
	{
		HistoryTime[iMovesMade] = 0;
	}

	if ((iIsComputerB == 0) || (iIsComputerW == 0))
	{
		HistoryPassed[iMovesMade] = 0;
	}

	/*** Update the statusbar. ***/
	StatusBar();

	while (gtk_events_pending())
	{
		gtk_main_iteration();
	}
}
/*****************************************************************************/
