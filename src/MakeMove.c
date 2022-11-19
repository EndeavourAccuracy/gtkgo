/* gtkgo v0.0.12 (MakeMove.c) (November 2022)
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

#include "MakeMove.h"

/*****************************************************************************/
void MakeMove (GtkWidget *widget, GdkEvent *event, gpointer data)
/*****************************************************************************/
{
	int iPoint;

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (event != NULL) { } /*** To prevent (set but) unused warnings. ***/

	/*** The next 4 lines must be here. ***/
	while (gtk_events_pending())
	{
		gtk_main_iteration();
	}

	iPoint = GPOINTER_TO_INT (data);

	if (iSelectDead != 1)
	{
		if (iFileDialogOpen != 0) { return; }
		if ((iIsComputerB == 1) && (iIsComputerW == 1)) { return; }
		if (iWindowOpen != 0) { return; }
	}

	if (iBusyMakingMove == 0)
	{
		iBusyMakingMove = 1;

		if (iSelectDead == 1)
		{
			if (((Board[iPoint][2] == 'e') || (Board[iPoint][2] == 's')) &&
				((HistoryMoves[iMovesMade][iPoint][2] == 'b') ||
				(HistoryMoves[iMovesMade][iPoint][2] == 'w')))
			{
				/*** add ***/
				Board[iPoint][2] = HistoryMoves[iMovesMade][iPoint][2];
				if (iLatest == 1)
				{
					Board[iPoint][3] = HistoryMoves[iMovesMade][iPoint][3];
				}
				ChangePixmap (iPoint);
			} else if ((Board[iPoint][2] == 'b') || (Board[iPoint][2] == 'w')) {
				/*** remove ***/
				switch (iPoint)
				{
					case 61: Board[iPoint][2] = 's'; break;
					case 67: Board[iPoint][2] = 's'; break;
					case 73: Board[iPoint][2] = 's'; break;
					case 175: Board[iPoint][2] = 's'; break;
					case 181: Board[iPoint][2] = 's'; break;
					case 187: Board[iPoint][2] = 's'; break;
					case 289: Board[iPoint][2] = 's'; break;
					case 295: Board[iPoint][2] = 's'; break;
					case 301: Board[iPoint][2] = 's'; break;
					default: Board[iPoint][2] = 'e'; break;
				}
				if (Board[iPoint][3] == 'l')
				{
					Board[iPoint][3] = '\0';
				}
				ChangePixmap (iPoint);
			}
		}

		if (iSelectDead != 1)
		{
			if (iConnected == 1)
			{
				if ((Modulo (iMovesMade, 2) == 0) && (iInternetWeAreBlack == 0))
				{
					Message ("It is black's turn.", 3, 0);
					iBusyMakingMove = 0;
					return;
				}
				if ((Modulo (iMovesMade, 2) != 0) && (iInternetWeAreBlack == 1))
				{
					Message ("It is white's turn.", 3, 0);
					iBusyMakingMove = 0;
					return;
				}

				SendData (1, PointToPlace (2, iPoint));
			} else {
				iMoveMade = 0;
				iMoveAlt = 1;
				if (Modulo (iMovesMade, 2) == 0)
				{
					ChangePoint (iPoint, 'b');
				} else {
					ChangePoint (iPoint, 'w');
				}
				iMoveAlt = 0;
				if (iMoveMade == 1)
				{
					if (((iMovesMade == 0) || (iMovesMade == 1)) && (iJustRestarted == 1))
					{
						iHandicapStart = iHandicap;
						iJustRestarted = 0;
					}
					if ((iIsComputerB == 1) || (iIsComputerW == 1))
					{
						if (Modulo (iMovesMade, 2) == 0)
						{
							JudgeBoard ('w');
							Computer ('w');
							JudgeBoard ('b');
						} else {
							JudgeBoard ('b');
							Computer ('b');
							JudgeBoard ('w');
						}
					} else {
						if (Modulo (iMovesMade, 2) == 0)
						{
							JudgeBoard ('w');
						} else {
							JudgeBoard ('b');
						}
					}
				}
			}
		}

		iBusyMakingMove = 0;
		StatusBar();
	}
}
/*****************************************************************************/
