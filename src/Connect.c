/* gtkgo v0.0.12 (Connect.c) (November 2022)
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

#include "Connect.h"

/*****************************************************************************/
gboolean DestroyConnect (GtkWidget *widget, GdkEvent *event, gpointer data)
/*****************************************************************************/
{
	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (event != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	gtk_widget_destroy (connectwindow);
	iWindowOpen = 0;

	return (TRUE);
}
/*****************************************************************************/
void ConnectCombo (GtkComboBox *widget, gpointer data)
/*****************************************************************************/
{
	char sServerType[100];

	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	snprintf (sServerType, 100, "%s", gtk_combo_box_get_active_id (widget));
	if (strcmp (sServerType, "NNGS") == 0)
	{
		gtk_entry_set_text (GTK_ENTRY (connectentryhost), NNGS_DEFAULT_HOST);
		gtk_entry_set_text (GTK_ENTRY (connectentryport), NNGS_DEFAULT_PORT);
	}
	if (strcmp (sServerType, "IGS") == 0)
	{
		gtk_entry_set_text (GTK_ENTRY (connectentryhost), IGS_DEFAULT_HOST);
		gtk_entry_set_text (GTK_ENTRY (connectentryport), IGS_DEFAULT_PORT);
	}
	gtk_widget_grab_focus (connectentryhost);
}
/*****************************************************************************/
gboolean Connect (GtkWidget *widget, GdkEvent *event, gpointer data)
/*****************************************************************************/
{
	GtkWidget *connectbox;
	GtkWidget *connectgrid;
	GtkWidget *connectentryhostlabel;
	GtkWidget *connectentryportlabel;
	GtkWidget *connectcombotypelabel;
	GtkWidget *connectsep;
	GtkWidget *connectbutton;

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (event != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	if (iFileDialogOpen != 0) { return (FALSE); }
	if ((iIsComputerB == 1) && (iIsComputerW == 1)) { return (FALSE); }
	if (iConnected != 0) { return (FALSE); }

	if (iWindowOpen == 0)
	{
		/*** window ***/
		connectwindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_window_set_transient_for (GTK_WINDOW (connectwindow),
			GTK_WINDOW (optionswindow));
		gtk_window_set_title (GTK_WINDOW (connectwindow), "Internet play");
		g_signal_connect (connectwindow, "delete_event",
			G_CALLBACK (DestroyConnect), NULL);
		gtk_window_set_resizable (GTK_WINDOW (connectwindow), FALSE);
		gtk_container_set_border_width (GTK_CONTAINER (connectwindow), 0);
		gtk_widget_realize (connectwindow);

		/*** box ***/
		connectbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
		gtk_container_set_border_width (GTK_CONTAINER (connectbox), 0);
		gtk_container_add (GTK_CONTAINER (connectwindow), connectbox);
		gtk_widget_show (connectbox);

		/*** grid ***/
		connectgrid = gtk_grid_new();
		gtk_box_pack_start (GTK_BOX (connectbox), connectgrid, TRUE, TRUE, 0);
		gtk_widget_show (connectgrid);

		/*** combo type label ***/
		connectcombotypelabel = gtk_label_new ("type:");
		gtk_label_set_justify (GTK_LABEL (connectcombotypelabel),
			GTK_JUSTIFY_RIGHT);
		gtk_grid_attach (GTK_GRID (connectgrid), connectcombotypelabel,
			0, 0, 1, 1);
		g_object_set (connectcombotypelabel, "margin", 10, NULL);
		gtk_widget_show (connectcombotypelabel);

		/*** combo type ***/
		connectcombotype = gtk_combo_box_text_new();
		gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (connectcombotype),
			"NNGS", "NNGS (No Name Go Server; GPL2+)");
		gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (connectcombotype),
			"IGS", "IGS (Internet Go Server; Proprietary?)");
		gtk_combo_box_set_active (GTK_COMBO_BOX (connectcombotype), 1);
		gtk_grid_attach (GTK_GRID (connectgrid), connectcombotype, 1, 0, 1, 1);
		g_object_set (connectcombotype, "hexpand", TRUE, NULL);
		g_object_set (connectcombotype, "margin", 10, NULL);
		gtk_widget_set_margin_start (connectcombotype, 0);
		gtk_widget_show (connectcombotype);

		/*** entry host label ***/
		connectentryhostlabel = gtk_label_new ("host:");
		gtk_label_set_justify (GTK_LABEL (connectentryhostlabel),
			GTK_JUSTIFY_RIGHT);
		gtk_grid_attach (GTK_GRID (connectgrid), connectentryhostlabel,
			0, 1, 1, 1);
		gtk_widget_set_margin_start (connectentryhostlabel, 10);
		gtk_widget_set_margin_end (connectentryhostlabel, 10);
		gtk_widget_show (connectentryhostlabel);

		/*** entry host ***/
		connectentryhost = gtk_entry_new();
		gtk_entry_set_max_length (GTK_ENTRY (connectentryhost), MAX_HOST);
		gtk_entry_set_text (GTK_ENTRY (connectentryhost), IGS_DEFAULT_HOST);
		gtk_editable_select_region (GTK_EDITABLE (connectentryhost), 0,
			gtk_entry_get_text_length (GTK_ENTRY (connectentryhost)));
		gtk_grid_attach (GTK_GRID (connectgrid), connectentryhost, 1, 1, 1, 1);
		g_object_set (connectentryhost, "hexpand", TRUE, NULL);
		g_object_set (connectentryhost, "vexpand", TRUE, NULL);
		gtk_widget_set_margin_end (connectentryhost, 10);
		gtk_widget_grab_focus (connectentryhost);
		gtk_widget_show (connectentryhost);

		/*** entry port label ***/
		connectentryportlabel = gtk_label_new ("port:");
		gtk_label_set_justify (GTK_LABEL (connectentryportlabel),
			GTK_JUSTIFY_RIGHT);
		gtk_grid_attach (GTK_GRID (connectgrid), connectentryportlabel,
			0, 2, 1, 1);
		g_object_set (connectentryportlabel, "margin", 10, NULL);
		gtk_widget_show (connectentryportlabel);

		/*** entry port ***/
		connectentryport = gtk_entry_new();
		gtk_entry_set_max_length (GTK_ENTRY (connectentryport), 5);
		gtk_entry_set_text (GTK_ENTRY (connectentryport), IGS_DEFAULT_PORT);
		gtk_grid_attach (GTK_GRID (connectgrid), connectentryport, 1, 2, 1, 1);
		g_object_set (connectentryport, "hexpand", TRUE, NULL);
		g_object_set (connectentryport, "vexpand", TRUE, NULL);
		g_object_set (connectentryport, "margin", 10, NULL);
		gtk_widget_set_margin_start (connectentryport, 0);
		gtk_widget_show (connectentryport);

		/*** Must be after the creation of the entry elements. ***/
		g_signal_connect (connectcombotype, "changed",
			G_CALLBACK (ConnectCombo), NULL);

		/*** separator ***/
		connectsep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
		gtk_grid_attach (GTK_GRID (connectgrid), connectsep, 0, 3, 2, 1);
		gtk_widget_show (connectsep);

		/*** button ***/
		connectbutton = gtk_button_new_with_mnemonic ("_Connect");
		g_signal_connect (connectbutton, "clicked",
			G_CALLBACK (InternetGo), NULL);
		gtk_widget_set_can_default (connectbutton, TRUE);
		gtk_window_set_default (GTK_WINDOW (connectwindow), connectbutton);
		gtk_grid_attach (GTK_GRID (connectgrid), connectbutton, 0, 4, 2, 1);
		g_object_set (connectbutton, "margin", 2, NULL);
		gtk_widget_show (connectbutton);

		gtk_widget_show (connectwindow);
		iWindowOpen = 1;
	}

	return (TRUE);
}
/*****************************************************************************/
