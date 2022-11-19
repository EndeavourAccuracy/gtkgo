/* gtkgo v0.0.12 (Undo.c) (November 2022)
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

#include "Undo.h"

/*****************************************************************************/
void Undo (GtkWidget *widget, gpointer data)
/*****************************************************************************/
{
	/* Undo can be triggered from four locations: the Game menu, the
	 * pop-up menu, the top button, and in response to server input.
	 *
	 * GtkWidget *widget receives either GtkMenuItem *menuitem
	 * or GtkButton *button.
	 */

	int iPointLoop;
	int iUndo;
	int iAllow;

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	iUndo = 1;

	iAllow = 0;
	/*** no computers [0], handicap, 2+ moves ***/
	if ((iIsComputerW == 0) && (iIsComputerB == 0) &&
		(iHandicapStart > 0) && (iMovesMade >= 2)) { iAllow = 1; }
	/*** white computer [2], handicap, 4+ moves ***/
	if ((iIsComputerW == 1) && (iIsComputerB == 0) &&
		(iHandicapStart > 0) && (iMovesMade >= 4)) { iAllow = 1; }
	/*** black computer [1], handicap, 3+ moves ***/
	if ((iIsComputerW == 0) && (iIsComputerB == 1) &&
		(iHandicapStart > 0) && (iMovesMade >= 3)) { iAllow = 1; }
	/*** no computers [0], no handicap, 1+ moves ***/
	if ((iIsComputerW == 0) && (iIsComputerB == 0) &&
		(iHandicapStart == 0) && (iMovesMade >= 1)) { iAllow = 1; }
	/*** white computer [1], no handicap, 2+ moves ***/
	if ((iIsComputerW == 1) && (iIsComputerB == 0) &&
		(iHandicapStart == 0) && (iMovesMade >= 2)) { iAllow = 1; }
	/*** black computer [2], no handicap, 3+ moves ***/
	if ((iIsComputerW == 0) && (iIsComputerB == 1) &&
		(iHandicapStart == 0) && (iMovesMade >= 3)) { iAllow = 1; }
	if (iAllow == 0) { iUndo = 0; }

	if (iWindowOpen != 0) { iUndo = 0; }
	if (iFileDialogOpen != 0) { iUndo = 0; }

	if (iConnected == 1)
	{
		if ((Modulo (iMovesMade, 2) == 0) && (iInternetWeAreBlack == 0))
		{
			Message ("It is black's turn.", 3, 0);
			iUndo = 0;
		}
		if ((Modulo (iMovesMade, 2) != 0) && (iInternetWeAreBlack == 1))
		{
			Message ("It is white's turn.", 3, 0);
			iUndo = 0;
		}
	}

	/*** iAllowUndo overrides all disabling conditions. ***/
	if (iAllowUndo == 1) { iUndo = 1; }

	if (iUndo == 1)
	{
		if (iOptions == 0) { Play ("click.ogg", 0); }

		if ((iConnected == 1) && (iAllowUndo != 1))
		{
			SendData (1, "undo");
		}

		if ((iIsComputerW == 0) && (iIsComputerB == 0))
		{
			iMovesMade-=1;
		} else {
			iMovesMade-=2;
		}

		if (Modulo (iMovesMade, 2) == 0)
		{
			iOutOfTimeAtW = HistoryTime[iMovesMade] + (unsigned)time(&tmTime);
			iOutOfTimeAtB = HistoryTime[iMovesMade - 1] + (unsigned)time(&tmTime);
		} else {
			iOutOfTimeAtB = HistoryTime[iMovesMade] + (unsigned)time(&tmTime);
			if (iMovesMade > 1)
			{
				iOutOfTimeAtW = HistoryTime[iMovesMade - 1] + (unsigned)time(&tmTime);
			} else {
				iOutOfTimeAtW = (iTimeLimit * 60) + (unsigned)time(&tmTime);
			}
		}

		iTurnStartTime = (unsigned)time(&tmTime);
		iTimeLeftBSCalc = iOutOfTimeAtB - (unsigned)time(&tmTime);
		iTimeLeftWSCalc = iOutOfTimeAtW - (unsigned)time(&tmTime);

		iCapturedW = HistoryCapturedW[iMovesMade];
		iCapturedB = HistoryCapturedB[iMovesMade];

		for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
		{
			if ((HistoryMoves[iMovesMade][iPointLoop][3] == 'l') &&
				(HistoryMoves[iMovesMade][iPointLoop][2] == 'b'))
			{
				iLastMoveB = iPointLoop;
			}
			if ((HistoryMoves[iMovesMade][iPointLoop][3] == 'l') &&
				(HistoryMoves[iMovesMade][iPointLoop][2] == 'w'))
			{
				iLastMoveW = iPointLoop;
			}
			if (strcmp (HistoryMoves[iMovesMade][iPointLoop],
				Board[iPointLoop]) != 0)
			{
				if (HistoryMoves[iMovesMade][iPointLoop][3] != 'l')
				{
					snprintf (Board[iPointLoop], MAX_I, "%s",
						HistoryMoves[iMovesMade][iPointLoop]);
				} else {
					if (iLatest == 0)
					{
						snprintf (Board[iPointLoop], MAX_I, "%c%c%c",
							HistoryMoves[iMovesMade][iPointLoop][0],
							HistoryMoves[iMovesMade][iPointLoop][1],
							HistoryMoves[iMovesMade][iPointLoop][2]);
					} else {
						snprintf (Board[iPointLoop], MAX_I, "%s",
							HistoryMoves[iMovesMade][iPointLoop]);
					}
				}

				iMoveAlt = 1;
				ChangePixmap (iPointLoop);
				iMoveAlt = 0;
			}
		}
		StatusBar();
	}
}
/*****************************************************************************/
