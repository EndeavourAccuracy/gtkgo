/* gtkgo v0.0.12 (StatusBar.c) (November 2022)
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

#include "StatusBar.h"

/*****************************************************************************/
void StatusBar (void)
/*****************************************************************************/
{
	char sStatusBar[200];

	if (((iPSize == 0) || (iPSize >= 30)) &&
		((iWindowOpen == 0) || (iSelectDead == 1)))
	{
		if (iSelectDead == 0)
		{
			if (iMovesMade >= 1)
			{
				if (Modulo (iMovesMade, 2) == 0)
				{
					iTimeLeftWSCalc = iOutOfTimeAtW - (unsigned)time(&tmTime);
				} else {
					iTimeLeftBSCalc = iOutOfTimeAtB - (unsigned)time(&tmTime);
				}
				iTimeLeftBH = 0;
				iTimeLeftBM = 0;
				iTimeLeftBS = iTimeLeftBSCalc;
				if (iTimeLeftBS > 59)
				{
					do
					{
						iTimeLeftBS-=60;
						iTimeLeftBM++;
					} while (iTimeLeftBS >= 60);
				}
				if (iTimeLeftBM > 59)
				{
					do
					{
						iTimeLeftBM-=60;
						iTimeLeftBH++;
					} while (iTimeLeftBM >= 60);
				}
				iTimeLeftWH = 0;
				iTimeLeftWM = 0;
				iTimeLeftWS = iTimeLeftWSCalc;
				if (iTimeLeftWS > 59)
				{
					do
					{
						iTimeLeftWS-=60;
						iTimeLeftWM++;
					} while (iTimeLeftWS >= 60);
				}
				if (iTimeLeftWM > 59)
				{
					do
					{
						iTimeLeftWM-=60;
						iTimeLeftWH++;
					} while (iTimeLeftWM >= 60);
				}
			} else {
				iTimeLeftBS = 0;
				iTimeLeftBM = iTimeLimit;
				iTimeLeftBH = 0;
				if (iTimeLeftBM > 59)
				{
					iTimeLeftBH = 0;
					do
					{
						iTimeLeftBM-=60;
						iTimeLeftBH++;
					} while (iTimeLeftBM >= 60);
				}
				iTimeLeftWS = iTimeLeftBS;
				iTimeLeftWM = iTimeLeftBM;
				iTimeLeftWH = iTimeLeftBH;
			}
			if (((iTimeLeftBS <= 0) && (iTimeLeftBM == 0) && (iTimeLeftBH == 0)) ||
				((iTimeLeftWS <= 0) && (iTimeLeftWM == 0) && (iTimeLeftWH == 0)))
			{
				iQuitRestartType = 3;
				AskSave();
				if (iTimeLeftBS < 0)
				{
					iTimeLeftBS = 0;
				}
				if (iTimeLeftWS < 0)
				{
					iTimeLeftWS = 0;
				}
			}

			if (iTimeLeftBS < 10)
			{
				snprintf (sTimeLeftBS, 7, "0%i", iTimeLeftBS);
			} else {
				snprintf (sTimeLeftBS, 7, "%i", iTimeLeftBS);
			}

			if (iTimeLeftBM < 10)
			{
				snprintf (sTimeLeftBM, 7, "0%i", iTimeLeftBM);
			} else {
				snprintf (sTimeLeftBM, 7, "%i", iTimeLeftBM);
			}

			if (iTimeLeftBH != 0)
			{
				snprintf (sTimeLeftBH, 7, "%i:", iTimeLeftBH);
			} else {
				snprintf (sTimeLeftBH, 7, "%s", "");
			}

			if (iTimeLeftWS < 10)
			{
				snprintf (sTimeLeftWS, 7, "0%i", iTimeLeftWS);
			} else {
				snprintf (sTimeLeftWS, 7, "%i", iTimeLeftWS);
			}

			if (iTimeLeftWM < 10)
			{
				snprintf (sTimeLeftWM, 7, "0%i", iTimeLeftWM);
			} else {
				snprintf (sTimeLeftWM, 7, "%i", iTimeLeftWM);
			}

			if (iTimeLeftWH != 0)
			{
				snprintf (sTimeLeftWH, 7, "%i:", iTimeLeftWH);
			} else {
				snprintf (sTimeLeftWH, 7, "%s", "");
			}
		}

		fScoreBlack = ScoreBlack();

		if (iIsComputerB == 1)
		{
			snprintf (sStatusBar, 200, " Black computer %s has score %.1f"
				" (%i captures) and %s%s:%s time left.", sPlayerNameB, fScoreBlack,
				iCapturedW, sTimeLeftBH, sTimeLeftBM, sTimeLeftBS);
		} else {
			snprintf (sStatusBar, 200, " Black player %s has score %.1f"
				" (%i captures) and %s%s:%s time left.", sPlayerNameB, fScoreBlack,
				iCapturedW, sTimeLeftBH, sTimeLeftBM, sTimeLeftBS);
		}

		gtk_statusbar_push (GTK_STATUSBAR (mainstatbarblack), 1, sStatusBar);

		fScoreWhite = ScoreWhite();

		if (iIsComputerW == 1)
		{
			snprintf (sStatusBar, 200, " White computer %s has score %.1f"
				" (%i captures) and %s%s:%s time left.", sPlayerNameW, fScoreWhite,
				iCapturedB, sTimeLeftWH, sTimeLeftWM, sTimeLeftWS);
		} else {
			snprintf (sStatusBar, 200, " White player %s has score %.1f"
				" (%i captures) and %s%s:%s time left.", sPlayerNameW, fScoreWhite,
				iCapturedB, sTimeLeftWH, sTimeLeftWM, sTimeLeftWS);
		}

		gtk_statusbar_push (GTK_STATUSBAR (mainstatbarwhite), 1, sStatusBar);

		if (Modulo (iMovesMade, 2) == 0)
		{
			gtk_statusbar_push (GTK_STATUSBAR (mainstatbarcolor), 1, "black");
		} else {
			gtk_statusbar_push (GTK_STATUSBAR (mainstatbarcolor), 1, "white");
		}

		gtk_statusbar_push (GTK_STATUSBAR (mainstatbartomove), 1, "to move");
	}
}
/*****************************************************************************/
