/* gtkgo v0.0.12 (EnableComp.c) (November 2022)
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

#include "EnableComp.h"

/*****************************************************************************/
void EnableComp (GtkFileChooser *chooser, int iChangeColor)
/*****************************************************************************/
{
	/* Change the black (iChangeColor 2) or white (iChangeColor 1)
	 * player to the go-computer in chooser.
	 */

	char *sPFLong;
	char sExtension[10];
	char sComputerName[MAX_PLAYER_NAME];
	int iLengthExtension;
	int iLengthFile;
	char sPFComputer[100];
	int iChangeComputer;

	iChangeComputer = 0;

	sPFLong = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (chooser));
	iLengthExtension = strlen (strrchr (sPFLong, '.')) - 1;
	iLengthFile = strlen (strrchr (sPFLong, '/')) - 1;
	substr (sPFLong, strlen (sPFLong) - iLengthExtension,
		iLengthExtension, sExtension);
	if (strcmp (sExtension, GAME_NAME) == 0)
	{
		/*** Assemble sComputerName and sPFComputer. ***/
		substr (sPFLong, strlen (sPFLong) - iLengthFile,
			iLengthFile - 1 - iLengthExtension, sComputerName);
		snprintf (sPFComputer, 100, PKGDATADIR"computers/%s.%s",
			sComputerName, GAME_NAME);

		if (iChangeColor == 2)
		{
			if ((open (sPFComputer, O_RDONLY, 0600) != -1) &&
				(strcmp (sComputerName, sPlayerNameB) != 0) &&
				(strcmp (sComputerName, "") != 0))
			{
				snprintf (sPlayerNameB, MAX_PLAYER_NAME, "%s", sComputerName);
				iIsComputerB = 1;
				iChangeComputer = 1;
			}
		} else {
			if ((open (sPFComputer, O_RDONLY, 0600) != -1) &&
				(strcmp (sComputerName, sPlayerNameW) != 0) &&
				(strcmp (sComputerName, "") != 0))
			{
				snprintf (sPlayerNameW, MAX_PLAYER_NAME, "%s", sComputerName);
				iIsComputerW = 1;
				iChangeComputer = 1;
			}
		}
	} else {
		Message ("Extension is not ." GAME_NAME, 3, 0);
	}

	DestroyTheComputer (NULL, NULL);
	if (iFileDialogOpen == 1)
	{
		DestroyOptions (NULL, NULL);
	}

	if (iChangeComputer == 1)
	{
		StatusBar();
		if ((iMovesMade > 0) && ((iIsComputerB != 1) || (iIsComputerW != 1)))
		{
			iQuitRestartType = 2;
			AskSave();
		} else {
			if ((iIsComputerB == 1) && (iIsComputerW != 1))
			{
				Computer ('b');
				JudgeBoard ('w');
			}
		}
	}

	/*** Both players are computers. ***/
	if ((iIsComputerB == 1) && (iIsComputerW == 1))
	{
		iHandicapStart = iHandicap;
		if (iMovesMade > 1)
		{
			iMovesMade = 0;
			ReallyReStart();
		}

		/*** Make computer turns until a window opens. ***/
		do {
			/*** Start with white, because of DoHandicap(). ***/
			Computer ('w');
			JudgeBoard ('b');
			if (iWindowOpen != 1)
			{
				Computer ('b');
				JudgeBoard ('w');
			}
		} while (iWindowOpen != 1);
	}
}
/*****************************************************************************/
