/* gtkgo v0.0.12 (TheComputer.c) (November 2022)
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

#include "TheComputer.h"

/*****************************************************************************/
void TheComputer (GtkMenuItem *menuitem, gpointer data)
/*****************************************************************************/
{
	char sPFComputer[100];
	char sTitle[MAX_TITLE + 2];
	int iChangeColor;
	int iRes;

	if (menuitem != NULL) { } /*** To prevent (set but) unused warnings. ***/

	if (iFileDialogOpen != 0) { return; }
	if ((iIsComputerB == 1) && (iIsComputerW == 1)) { return; }
	if (iWindowOpen != 0) { return; }

	iChangeColor = GPOINTER_TO_INT (data);

	if (iChangeColor == 1)
	{
		snprintf (sTitle, MAX_TITLE, "%s", "change white");
	} else {
		snprintf (sTitle, MAX_TITLE, "%s", "change black");
	}

	if (iChangeColor == 2)
	{
		/*** black ***/
		if (iIsComputerB == 1)
		{
			snprintf (sPFComputer, 100, PKGDATADIR"computers/%s.%s",
				sPlayerNameB, GAME_NAME);
		} else {
			snprintf (sPFComputer, 100, PKGDATADIR"computers/default2.%s",
				GAME_NAME);
		}
	} else {
		/*** white ***/
		if (iIsComputerW == 1)
		{
			snprintf (sPFComputer, 100, PKGDATADIR"computers/%s.%s",
				sPlayerNameW, GAME_NAME);
		} else {
			snprintf (sPFComputer, 100, PKGDATADIR"computers/default2.%s",
				GAME_NAME);
		}
	}

	/*** dialog ***/
	computerdialogload = gtk_file_chooser_dialog_new (sTitle, NULL,
		GTK_FILE_CHOOSER_ACTION_OPEN,
		"_OK", GTK_RESPONSE_OK,
		"_Cancel", GTK_RESPONSE_CANCEL,
		NULL);
	gtk_window_set_transient_for (GTK_WINDOW (computerdialogload),
		GTK_WINDOW (mainwindow));
	gtk_file_chooser_set_filename (GTK_FILE_CHOOSER (computerdialogload),
		sPFComputer);
	gtk_widget_set_size_request (GTK_WIDGET (computerdialogload), 445, 300);
	g_signal_connect (computerdialogload, "delete_event",
		G_CALLBACK (DestroyTheComputer), NULL);
	gtk_widget_show (computerdialogload);

	iFileDialogOpen = 1;

	/*** Process response. ***/
	iRes = gtk_dialog_run (GTK_DIALOG (computerdialogload));
	if (iRes == GTK_RESPONSE_OK)
	{
		EnableComp (GTK_FILE_CHOOSER (computerdialogload), iChangeColor);
	}
	if (iRes == GTK_RESPONSE_CANCEL)
	{
		DestroyTheComputer (NULL, NULL);
	}
}
/*****************************************************************************/
