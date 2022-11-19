/* gtkgo v0.0.12 (Human.c) (November 2022)
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

#include "Human.h"

/*****************************************************************************/
gboolean DestroyHuman (GtkWidget *widget, GdkEvent *event, gpointer data)
/*****************************************************************************/
{
	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (event != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	gtk_widget_destroy (humwindow);
	iWindowOpen = 0;

	return (TRUE);
}
/*****************************************************************************/
void ActivateHuman (GtkWidget *widget, gpointer data)
/*****************************************************************************/
{
	/* GtkWidget *widget receives either GtkEntry *entry
	 * or GtkButton *button.
	 */

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	if (iChangeColorHuman == 1)
	{
		snprintf (sPlayerNameW, MAX_PLAYER_NAME, "%s", gtk_entry_get_text
			(GTK_ENTRY (humentry)));
		if (strcmp (sPlayerNameW, "") == 0)
			{ snprintf (sPlayerNameW, MAX_PLAYER_NAME, "%s", "unknown"); }
		iIsComputerW = 0;
	} else {
		snprintf (sPlayerNameB, MAX_PLAYER_NAME, "%s", gtk_entry_get_text
			(GTK_ENTRY (humentry)));
		if (strcmp (sPlayerNameB, "") == 0)
			{ snprintf (sPlayerNameB, MAX_PLAYER_NAME, "%s", "unknown"); }
		iIsComputerB = 0;
	}

	gtk_widget_destroy (humwindow);
	iWindowOpen = 0;
	StatusBar();
}
/*****************************************************************************/
void Human (GtkMenuItem *menuitem, gpointer data)
/*****************************************************************************/
{
	GtkWidget *humbox;
	GtkWidget *humgrid;
	GtkWidget *humsep;
	GtkWidget *humbutton;

	if (menuitem != NULL) { } /*** To prevent (set but) unused warnings. ***/

	if (iFileDialogOpen != 0) { return; }
	if ((iIsComputerB == 1) && (iIsComputerW == 1)) { return; }

	if (iWindowOpen == 0)
	{
		iChangeColorHuman = GPOINTER_TO_INT (data);

		/*** window ***/
		humwindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_window_set_transient_for (GTK_WINDOW (humwindow),
			GTK_WINDOW (optionswindow));
		if (iChangeColorHuman == 1)
		{
			gtk_window_set_title (GTK_WINDOW (humwindow), "change white");
		} else {
			gtk_window_set_title (GTK_WINDOW (humwindow), "change black");
		}
		g_signal_connect (humwindow, "delete_event",
			G_CALLBACK (DestroyHuman), NULL);
		gtk_window_set_resizable (GTK_WINDOW (humwindow), FALSE);
		gtk_container_set_border_width (GTK_CONTAINER (humwindow), 0);
		gtk_widget_realize (humwindow);

		/*** box ***/
		humbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
		gtk_container_set_border_width (GTK_CONTAINER (humbox), 0);
		gtk_container_add (GTK_CONTAINER (humwindow), humbox);
		gtk_widget_show (humbox);

		/*** grid ***/
		humgrid = gtk_grid_new();
		gtk_box_pack_start (GTK_BOX (humbox), humgrid, TRUE, TRUE, 0);
		gtk_widget_show (humgrid);

		/*** entry ***/
		humentry = gtk_entry_new();
		gtk_entry_set_max_length (GTK_ENTRY (humentry), MAX_PLAYER_NAME);
		g_signal_connect (humentry, "activate",
			G_CALLBACK (ActivateHuman), NULL);
		if ((iChangeColorHuman == 1) && (iIsComputerW == 0))
		{
			gtk_entry_set_text (GTK_ENTRY (humentry), sPlayerNameW);
			gtk_editable_select_region (GTK_EDITABLE (humentry),
				0, gtk_entry_get_text_length (GTK_ENTRY (humentry)));
		}
		if ((iChangeColorHuman == 2) && (iIsComputerB == 0))
		{
			gtk_entry_set_text (GTK_ENTRY (humentry), sPlayerNameB);
			gtk_editable_select_region (GTK_EDITABLE (humentry),
				0, gtk_entry_get_text_length (GTK_ENTRY (humentry)));
		}
		gtk_grid_attach (GTK_GRID (humgrid), humentry, 0, 0, 1, 1);
		g_object_set (humentry, "hexpand", TRUE, NULL);
		g_object_set (humentry, "vexpand", TRUE, NULL);
		g_object_set (humentry, "margin", 10, NULL);
		gtk_widget_grab_focus (humentry);
		gtk_widget_show (humentry);

		/*** separator ***/
		humsep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
		gtk_grid_attach (GTK_GRID (humgrid), humsep, 0, 1, 1, 1);
		gtk_widget_show (humsep);

		/*** button ***/
		humbutton = gtk_button_new_with_mnemonic ("_OK");
		g_signal_connect (humbutton, "clicked",
			G_CALLBACK (ActivateHuman), NULL);
		gtk_widget_set_can_default (humbutton, TRUE);
		gtk_window_set_default (GTK_WINDOW (humwindow), humbutton);
		gtk_grid_attach (GTK_GRID (humgrid), humbutton, 0, 2, 1, 1);
		g_object_set (humbutton, "margin", 2, NULL);
		gtk_widget_show (humbutton);

		gtk_widget_show (humwindow);
		iWindowOpen = 1;
	}
}
/*****************************************************************************/
