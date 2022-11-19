/* gtkgo v0.0.12 (Message.c) (November 2022)
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

#include "Message.h"

/*****************************************************************************/
void Message (char *sText, int iShowQuit, int iType)
/*****************************************************************************/
{
	/* iShowQuit:
	 * 0 = Stores sText to sSaveMes.
	 * 1 = Show sText (and optionally sSaveMes), quit.
	 * 2 = Show sSaveMes, quit.
	 * 3 = Show sText.
	 * 4 = Show sText. Only used when selecting dead stones.
	 *
	 * iType:
	 * 0 = error/bad
	 * 1 = correct/good/ok
	 */

	GtkWidget *messagebox;
	GtkWidget *messagegrid;
	GtkWidget *messagelabel;
	GtkWidget *messagesep;
	GtkWidget *messagebutton;
	GtkWidget *messageim;
	/***/
	char sMessage[MAX_MESSAGE + 2];
	char sPFImage[MAX_IMAGE + 2];

	if ((iShowQuit != 0) && (iWindowOpen == 0))
	{
		if (iOptions == 0) { Play ("open.ogg", 0); }

		switch (iShowQuit)
		{
			case 1:
				if (iStoreMes == 1)
				{
					snprintf (sMessage, MAX_MESSAGE, "\n%s\n%s\n", sSaveMes, sText);
				} else {
					snprintf (sMessage, MAX_MESSAGE, "\n%s\n", sText);
				}
				break;
			case 2:
				snprintf (sMessage, MAX_MESSAGE, "\n%s\n", sSaveMes);
				break;
			case 3:
			case 4:
				snprintf (sMessage, MAX_MESSAGE, "\n%s\n", sText);
				break;
		}

		/*** window ***/
		messagewindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_window_set_transient_for (GTK_WINDOW (messagewindow),
			GTK_WINDOW (mainwindow));
		gtk_window_set_position (GTK_WINDOW (messagewindow), GTK_WIN_POS_CENTER);
		gtk_window_set_title (GTK_WINDOW (messagewindow), "message");
		g_signal_connect (messagewindow, "delete_event",
			G_CALLBACK (DestroyMessage), NULL);
		gtk_window_set_resizable (GTK_WINDOW (messagewindow), FALSE);
		gtk_container_set_border_width (GTK_CONTAINER (messagewindow), 0);
		gtk_widget_realize (messagewindow);

		/*** box ***/
		messagebox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
		gtk_container_set_border_width (GTK_CONTAINER (messagebox), 0);
		gtk_container_add (GTK_CONTAINER (messagewindow), messagebox);
		gtk_widget_show (messagebox);

		/*** grid ***/
		messagegrid = gtk_grid_new();
		gtk_widget_show (messagegrid);
		gtk_box_pack_start (GTK_BOX (messagebox), messagegrid, TRUE, TRUE, 0);

		/*** image ***/
		if (iType == 0)
		{
			snprintf (sPFImage, MAX_IMAGE, "%s", PKGDATADIR"png/error.png");
		} else {
			snprintf (sPFImage, MAX_IMAGE, "%s", PKGDATADIR"png/correct.png");
		}
		CheckAccess (sPFImage);
		messageim = gtk_image_new_from_file (sPFImage);
		gtk_grid_attach (GTK_GRID (messagegrid), messageim, 0, 0, 1, 1);
		g_object_set (messageim, "margin", 5, NULL);
		gtk_widget_show (messageim);

		/*** label ***/
		messagelabel = gtk_label_new (sMessage);
		gtk_label_set_text (GTK_LABEL (messagelabel), sMessage);
		gtk_label_set_justify (GTK_LABEL (messagelabel), GTK_JUSTIFY_CENTER);
		gtk_grid_attach (GTK_GRID (messagegrid), messagelabel, 1, 0, 1, 1);
		gtk_widget_set_margin_end (messagelabel, 5);
		gtk_widget_show (messagelabel);

		/*** separator ***/
		messagesep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
		gtk_grid_attach (GTK_GRID (messagegrid), messagesep, 0, 1, 2, 1);
		gtk_widget_show (messagesep);

		/*** button ***/
		messagebutton = gtk_button_new_with_mnemonic ("_OK");
		g_signal_connect (messagebutton, "clicked",
			G_CALLBACK (DestroyMessage), NULL);
		gtk_widget_set_can_default (messagebutton, TRUE);
		gtk_window_set_default (GTK_WINDOW (messagewindow), messagebutton);
		gtk_grid_attach (GTK_GRID (messagegrid), messagebutton, 0, 2, 2, 1);
		g_object_set (messagebutton, "margin", 2, NULL);
		gtk_widget_show (messagebutton);

		gtk_widget_show (messagewindow);
		iWindowOpen = 1;
		if ((iShowQuit != 3) && (iShowQuit != 4))
		{
			iQuitAfterMessage = 1;
		}
	} else {
		iStoreMes = 1;
		snprintf (sSaveMes, MAX_MESSAGE, "%s", sText);
	}
}
/*****************************************************************************/
