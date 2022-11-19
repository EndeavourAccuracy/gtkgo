/* gtkgo v0.0.12 (ReallyQuit.c) (November 2022)
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

#include "ReallyQuit.h"

/*****************************************************************************/
void ReallyQuit (void)
/*****************************************************************************/
{
	/* Not a parameter, but it uses iQuitRestartType:
	 * 1 = Resigned. Show winner. AskSave "no" will quit.
	 * 2 = AskSave "no" will restart.
	 * 3 = Out of time. Or, selecting dead stones. Show winner.
	 * AskSave "no" will quit.
	 * 4 = No moves were made. Do not show winner.
	 */

	char sMessage[MAX_MESSAGE + 2];
	char sToWrite[250];

	/*** Resigned. ***/
	if (iQuitRestartType == 1)
	{
		/*** Black resigned. ***/
		if (((iIsComputerW == 1) && (iIsComputerB == 0)) ||
			((iIsComputerW == 0) && (iIsComputerB == 0) &&
			(Modulo (iMovesMade, 2) == 0)) ||
			((iIsComputerW == 1) && (iIsComputerB == 1) &&
			(Modulo (iMovesMade, 2) == 0)))
		{
			JudgeBoard ('w');

			/*** Save, then show (two) messages. ***/
			if (iSaveMatch == 1) { SaveSGF(); }
			snprintf (sMessage, MAX_MESSAGE, "%s/W wins (resign).", sPlayerNameW);
			Message (sMessage, 1, 1);
		}

		/*** White resigned. ***/
		if (((iIsComputerB == 1) && (iIsComputerW == 0)) ||
			((iIsComputerB == 0) && (iIsComputerW == 0) &&
			(Modulo (iMovesMade, 2) != 0)) ||
			((iIsComputerB == 1) && (iIsComputerW == 1) &&
			(Modulo (iMovesMade, 2) != 0)))
		{
			JudgeBoard ('b');

			/*** Save, then show (two) messages. ***/
			if (iSaveMatch == 1) { SaveSGF(); }
			snprintf (sMessage, MAX_MESSAGE, "%s/B wins (resign).", sPlayerNameB);
			Message (sMessage, 1, 1);
		}
	}

	if (iQuitRestartType == 3)
	{
		/*** Out of time. ***/
		if (((iTimeLeftBS <= 0) && (iTimeLeftBM == 0) && (iTimeLeftBH == 0)) ||
			((iTimeLeftWS <= 0) && (iTimeLeftWM == 0) && (iTimeLeftWH == 0)))
		{
			/*** Save, then show (two) messages. ***/
			if (iSaveMatch == 1) { SaveSGF(); }
			/*** Black out of time. ***/
			if ((iTimeLeftBS <= 0) && (iTimeLeftBM == 0) && (iTimeLeftBH == 0))
			{
				snprintf (sMessage, MAX_MESSAGE, "%s/W wins (time).", sPlayerNameW);
			}
			/*** White out of time. ***/
			if ((iTimeLeftWS <= 0) && (iTimeLeftWM == 0) && (iTimeLeftWH == 0))
			{
				snprintf (sMessage, MAX_MESSAGE, "%s/B wins (time).", sPlayerNameB);
			}
			Message (sMessage, 1, 1);
		} else {
			if ((Modulo (iMovesMade, 2) == 0) &&
				((iIsComputerB == 0) || (iIsComputerW == 0)))
			{
				JudgeBoard ('w');
				if (iPassLosing == 1)
				{
					HistoryPassed[iMovesMade] = 1;
				}
			}
			if ((Modulo (iMovesMade, 2) != 0) &&
				((iIsComputerB == 0) || (iIsComputerW == 0)))
			{
				JudgeBoard ('b');
				if (iPassLosing == 1)
				{
					HistoryPassed[iMovesMade] = 1;
				}
			}

			/*** Black wins. ***/
			if (fScoreBlack > fScoreWhite)
			{
				/*** Save, then show (two) messages. ***/
				if (iSaveMatch == 1) { SaveSGF(); }
				snprintf (sMessage, MAX_MESSAGE, "%s/B wins (+%.1f).", sPlayerNameB,
					fScoreBlack - fScoreWhite);
				Message (sMessage, 1, 1);
			}

			/*** White wins. ***/
			if (fScoreBlack < fScoreWhite)
			{
				/*** Save, then show (two) messages. ***/
				if (iSaveMatch == 1) { SaveSGF(); }
				snprintf (sMessage, MAX_MESSAGE, "%s/W wins (+%.1f).", sPlayerNameW,
					fScoreWhite - fScoreBlack);
				Message (sMessage, 1, 1);
			}

			/*** Tie. ***/
			if (fScoreBlack == fScoreWhite)
			{
				/*** Save, then show (two) messages. ***/
				if (iSaveMatch == 1) { SaveSGF(); }
				Message ("Same scores (0).", 1, 1);
			}
		}
	}

	/*** Save the current configuration. ***/
	iConfigFD = open (sConfigFile, O_CREAT|O_TRUNC|O_WRONLY, 0600);
	if (iConfigFD != -1)
	{
		snprintf (sToWrite, 250, "# %s skin/time settings.\n\n", GAME_NAME);
		write (iConfigFD, sToWrite, strlen (sToWrite));
		snprintf (sToWrite, 250, "%s\n", sCurrentSkin);
		write (iConfigFD, sToWrite, strlen (sToWrite));
		snprintf (sToWrite, 250, "%i\n", iOptionsX);
		write (iConfigFD, sToWrite, strlen (sToWrite));
		snprintf (sToWrite, 250, "%i\n", iTimeLimit);
		write (iConfigFD, sToWrite, strlen (sToWrite));
		close (iConfigFD);
	}

	if (iQuitRestartType == 4)
	{
		exit (EXIT_NORMAL);
	}
}
/*****************************************************************************/
