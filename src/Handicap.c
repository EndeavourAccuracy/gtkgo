/* gtkgo v0.0.12 (Handicap.c) (November 2022)
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

#include "Handicap.h"

/*****************************************************************************/
void Handicap (gpointer data)
/*****************************************************************************/
{
	char sPFImage[200];

	if (iFileDialogOpen != 0) { return; }
	if (iWindowOpen != 0) { return; }
	if (iConnected != 0) { return; }

	if (iHandicapDone == 1)
	{
		iHandicapDone = 0;

		/*** Modify the handicap. ***/
		if (GPOINTER_TO_INT (data) == 1)
		{
			iHandicap++;
			if (iHandicap == 1) { iHandicap = 2; }
			if (iHandicap == 18) { iHandicap = 0; }
		} else {
			iHandicap--;
			if (iHandicap == 1) { iHandicap = 0; }
			if (iHandicap == -1) { iHandicap = 17; }
		}

		/*** Modify the image. ***/
		gtk_container_remove (GTK_CONTAINER (optionsbutton9b),
			GTK_WIDGET (optionsim9b));
		if (iOptionsX == 1)
		{
			snprintf (sPFImage, 200, PKGDATADIR"png/optionsx/9%i.png", iHandicap);
		} else {
			snprintf (sPFImage, 200, PKGDATADIR"png/options/9%i.png", iHandicap);
		}
		CheckAccess (sPFImage);
		optionsim9b = gtk_image_new_from_file (sPFImage);
		gtk_container_add (GTK_CONTAINER (optionsbutton9b), optionsim9b);
		gtk_widget_show (optionsim9b);

		while (gtk_events_pending())
		{
			gtk_main_iteration();
		}

		/*** Modify the board, if necessary. ***/
		if (((iMovesMade <= 1) && (iIsComputerW == 0)) ||
			((iMovesMade <= 2) && (iIsComputerW == 1)))
		{
			iMovesMade = 0;
			DoHandicap();
		}

		iHandicapDone = 1;
	}
}
/*****************************************************************************/
