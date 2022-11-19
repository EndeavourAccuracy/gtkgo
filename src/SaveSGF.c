/* gtkgo v0.0.12 (SaveSGF.c) (November 2022)
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

#include "SaveSGF.h"

/*****************************************************************************/
void SaveSGF (void)
/*****************************************************************************/
{
	int iSaveFD;
	int iMoveLoop;
	int iPointLoop;
	int iDoneB;
	int iStoreB;
	int iDoneW;
	int iStoreW;
	char sFilename[100];
	char sToWrite[250];
	char sMessage[MAX_MESSAGE + 2];

	iDoneB = 0;
	iStoreB = 0;
	iDoneW = 0;
	iStoreW = 0;

	if (iSaveMatch == 1)
	{
		gtk_widget_destroy (yesnowindow);
		iWindowOpen = 0;
	}

	snprintf (sFilename, 100, "%s", gtk_file_chooser_get_filename
		(GTK_FILE_CHOOSER (savedialog)));
	iSaveFD = open (sFilename, O_CREAT|O_TRUNC|O_WRONLY, 0600);
	if (iSaveFD == -1)
	{
		Message ("Saving unsuccessfull.", 0, 0);
	} else {
		snprintf (sToWrite, 250, "%s", "(\n;GM[1]\nFF[4]\nRU[Japanese]\nSZ[19]\n");
		write (iSaveFD, sToWrite, strlen (sToWrite));
		snprintf (sToWrite, 250, "HA[%i]\n", iHandicapStart);
		write (iSaveFD, sToWrite, strlen (sToWrite));
		write (iSaveFD, "KM[5.5]\n", 8);
		snprintf (sToWrite, 250, "PB[%s]\n", sPlayerNameB);
		write (iSaveFD, sToWrite, strlen (sToWrite));
		snprintf (sToWrite, 250, "PW[%s]\n", sPlayerNameW);
		write (iSaveFD, sToWrite, strlen (sToWrite));
		snprintf (sToWrite, 250, "GN[%s/W vs %s/B]\n", sPlayerNameW, sPlayerNameB);
		write (iSaveFD, sToWrite, strlen (sToWrite));
		snprintf (sToWrite, 250, "AP[%s:%s]\n", GAME_NAME, GAME_VERSION);
		write (iSaveFD, sToWrite, strlen (sToWrite));
		if ((iQuitRestartType == 1) || (iQuitRestartType == 2))
		{
			if ((iTimeLeftBS <= 0) && (iTimeLeftBM == 0) && (iTimeLeftBH == 0))
			{
				write (iSaveFD, "RE[W+Time]\n", 11);
			} else if ((iTimeLeftWS <= 0) && (iTimeLeftWM == 0) &&
				(iTimeLeftWH == 0))
			{
				write (iSaveFD, "RE[B+Time]\n", 11);
			} else {
				write (iSaveFD, "RE[W+Resign]\n", 13);
			}
		} else {
			fScoreWhite = ScoreWhite();
			fScoreBlack = ScoreBlack();
			if (fScoreWhite > fScoreBlack)
			{
				snprintf (sToWrite, 250, "RE[W+%.1f]\n", fScoreWhite - fScoreBlack);
				write (iSaveFD, sToWrite, strlen (sToWrite));
			}
			if (fScoreWhite < fScoreBlack)
			{
				snprintf (sToWrite, 250, "RE[B+%.1f]\n", fScoreBlack - fScoreWhite);
				write (iSaveFD, sToWrite, strlen (sToWrite));
			}
			if (fScoreWhite == fScoreBlack)
			{
				write (iSaveFD, "RE[0]\n", 6);
			}
		}
		snprintf (sToWrite, 250, "TM[%i]\n", (iTimeLimit * 60));
		write (iSaveFD, sToWrite, strlen (sToWrite));
		switch (iHandicapStart)
		{
			case 2: write (iSaveFD, ";AB[dd];AB[pp]", 14); break;
			case 3: write (iSaveFD, ";AB[dd];AB[pp];AB[pd]", 21); break;
			case 4: write (iSaveFD, ";AB[dd];AB[pp];AB[pd];AB[dp]", 28); break;
			case 5: write (iSaveFD, ";AB[dd];AB[pp];AB[pd];AB[dp];AB[jj]", 35);
				break;
			case 6: write (iSaveFD, ";AB[dd];AB[pp];AB[pd];AB[dp];AB[dj];AB[pj]",
				42); break;
			case 7: write (iSaveFD, ";AB[dd];AB[pp];AB[pd];AB[dp];AB[dj];AB[pj]"
				";AB[jj]", 49);
		}
		if (iHandicapStart >= 8)
		{
			write (iSaveFD, ";AB[dd];AB[pp];AB[pd];AB[dp];AB[dj];AB[pj]"
				";AB[jd];AB[jp]", 56);
		}
		if (iHandicapStart >= 9)
		{
			write (iSaveFD, ";AB[jj]", 7);
		}
		if (iHandicapStart >= 10)
		{
			write (iSaveFD, ";AB[cc]\n", 7);
		}
		if (iHandicapStart >= 11)
		{
			write (iSaveFD, "\n;AB[qq]", 8);
		}
		if (iHandicapStart >= 12)
		{
			write (iSaveFD, ";AB[qc]", 7);
		}
		if (iHandicapStart >= 13)
		{
			write (iSaveFD, ";AB[cq]", 7);
		}
		if (iHandicapStart >= 14)
		{
			write (iSaveFD, ";AB[gg]", 7);
		}
		if (iHandicapStart >= 15)
		{
			write (iSaveFD, ";AB[mm]", 7);
		}
		if (iHandicapStart >= 16)
		{
			write (iSaveFD, ";AB[mg]", 7);
		}
		if (iHandicapStart == 17)
		{
			write (iSaveFD, ";AB[gm]", 7);
		}
		if (iHandicapStart >= 2)
		{
			write (iSaveFD, "\n", 1);
		}
		for (iMoveLoop = 0; iMoveLoop <= iMovesMade; iMoveLoop++)
		{
			if ((iQuitRestartType == 3) ||
				((iQuitRestartType != 3) && (iMoveLoop != iMovesMade)))
			{
				if (HistoryPassed[iMoveLoop] == 1)
				{
					if (((cColorFirstPlayer == 'b') && (Modulo (iMoveLoop, 2) == 0))
						|| ((cColorFirstPlayer == 'w') && (Modulo (iMoveLoop, 2) != 0)))
					{
						write (iSaveFD, ";W[]", 4);
					} else {
						write (iSaveFD, ";B[]", 4);
					}
				} else {
					for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
					{
						if (HistoryMoves[iMoveLoop][iPointLoop][3] == 'l')
						{
							if (((HistoryMoves[iMoveLoop][iPointLoop][2] == 'b') &&
								(((cColorFirstPlayer == 'b') &&
								(Modulo (iMoveLoop, 2) != 0)) ||
								((cColorFirstPlayer == 'w') &&
								(Modulo (iMoveLoop, 2) == 0)))) &&
								(iPointLoop != iDoneB))
							{
								snprintf (sToWrite, 250, ";B[%s]",
									PointToPlace (1, iPointLoop));
								write (iSaveFD, sToWrite, strlen (sToWrite));
								iStoreB = iPointLoop;
							}
							if (((HistoryMoves[iMoveLoop][iPointLoop][2] == 'w') &&
								(((cColorFirstPlayer == 'b') &&
								(Modulo (iMoveLoop, 2) == 0)) ||
								((cColorFirstPlayer == 'w') &&
								(Modulo (iMoveLoop, 2) != 0)))) &&
								(iPointLoop != iDoneW))
							{
								snprintf (sToWrite, 250, ";W[%s]",
									PointToPlace (1, iPointLoop));
								write (iSaveFD, sToWrite, strlen (sToWrite));
								iStoreW = iPointLoop;
							}
						}
					}
					if (iMoveLoop >= 1)
					{
						if (((cColorFirstPlayer == 'b') && (Modulo (iMoveLoop, 2) == 0))
							|| ((cColorFirstPlayer == 'w') && (Modulo (iMoveLoop, 2) != 0)))
						{
							snprintf (sToWrite, 250, "WL[%i]", HistoryTime[iMoveLoop]);
							write (iSaveFD, sToWrite, strlen (sToWrite));
						} else {
							snprintf (sToWrite, 250, "BL[%i]", HistoryTime[iMoveLoop]);
							write (iSaveFD, sToWrite, strlen (sToWrite));
						}
					}
					iDoneB = iStoreB;
					iDoneW = iStoreW;
				}
				if ((Modulo (iMoveLoop, 5) == 0) && (iMoveLoop != 0))
				{
					write (iSaveFD, "\n", 1);
				}
			}
		}
		write (iSaveFD, "\n)\n", 3);
		close (iSaveFD);

		snprintf (sMessage, MAX_MESSAGE, "%s successfully saved.", sFilename);

		Message (sMessage, 0, 1);
	}
}
/*****************************************************************************/
