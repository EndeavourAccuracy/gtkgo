/* gtkgo v0.0.12 (SaveDialog.c) (November 2022)
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

#include "SaveDialog.h"

/*****************************************************************************/
void SaveDialog (void)
/*****************************************************************************/
{
	int iRes;

	if (iOptions == 0) { Play ("open.ogg", 0); }

	/*** dialog ***/
	savedialog = gtk_file_chooser_dialog_new ("save SGF", NULL,
		GTK_FILE_CHOOSER_ACTION_SAVE,
		"_OK", GTK_RESPONSE_OK,
		"_Cancel", GTK_RESPONSE_CANCEL,
		NULL);
	gtk_window_set_transient_for (GTK_WINDOW (savedialog),
		GTK_WINDOW (mainwindow));
	gtk_widget_set_size_request (GTK_WIDGET (savedialog), 445, 300);
	gtk_file_chooser_set_do_overwrite_confirmation
		(GTK_FILE_CHOOSER (savedialog), TRUE);
	gtk_file_chooser_set_current_name
		(GTK_FILE_CHOOSER (savedialog), GAME_NAME ".sgf");
	gtk_widget_show (savedialog);

	iFileDialogOpen = 1;

	/*** Process user response. ***/
	iRes = gtk_dialog_run (GTK_DIALOG (savedialog));
	if (iRes == GTK_RESPONSE_OK)
	{
		switch (iQuitRestartType)
		{
			case 1:
			case 3:
				ReallyQuit(); break;
			case 2:
				ReallyReStart(); break;
		}
	}

	/*** Always close the dialog. ***/
	DestroySaveDialog();
}
/*****************************************************************************/
