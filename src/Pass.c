/* gtkgo v0.0.12 (Pass.c) (November 2022)
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

#include "Pass.h"

/*****************************************************************************/
void Pass (GtkWidget *widget, gpointer data)
/*****************************************************************************/
{
	/* GtkWidget *widget receives either GtkMenuItem *menuitem
	 * or GtkButton *button.
	 */

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	/*** The next 4 lines must be here. ***/
	while (gtk_events_pending())
	{
		gtk_main_iteration();
	}

	if (iOptions == 0) { Play ("click.ogg", 0); }

	if (iFileDialogOpen != 0) { return; }
	if ((iIsComputerB == 1) && (iIsComputerW == 1)) { return; }
	if (iWindowOpen != 0) { return; }

	if (iBusyMakingMove == 0)
	{
		iBusyMakingMove = 1;

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

			SendData (1, "pass");
		} else {
			if (Modulo (iMovesMade, 2) == 0)
			{
				JudgeBoard ('w');
			} else {
				JudgeBoard ('b');
			}

			HistoryPassed[iMovesMade] = 1;
			fScoreWhite = ScoreWhite();
			fScoreBlack = ScoreBlack();
			if (Modulo (iMovesMade, 2) != 0)
			{
				if ((fScoreWhite > fScoreBlack) ||
					(HistoryPassed[iMovesMade - 1] == 1))
				{
					if (fScoreWhite > fScoreBlack)
					{
						iPassLosing = 1;
					}
					EndGame();
				} else {
					if (iIsComputerW == 1)
					{
						Computer ('w');
						JudgeBoard ('b');
					}
				}
			} else {
				if ((fScoreBlack > fScoreWhite) ||
					(HistoryPassed[iMovesMade - 1] == 1))
				{
					if (fScoreBlack > fScoreWhite)
					{
						iPassLosing = 1;
					}
					EndGame();
				} else {
					if (iIsComputerB == 1)
					{
						Computer ('b');
						JudgeBoard ('w');
					}
				}
			}
		}

		iBusyMakingMove = 0;
	}
}
/*****************************************************************************/
