/* gtkgo v0.0.12 (AskSave.c) (November 2022)
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

#include "AskSave.h"

/*****************************************************************************/
void AskSave (void)
/*****************************************************************************/
{
	GtkWidget *yesnobox;
	GtkWidget *yesnogrid;
	GtkWidget *yesnoeventyes;
	GtkWidget *yesnoeventno;
	GtkWidget *yesnoim;
	/***/
	char sPFImage[MAX_IMAGE + 2];

	/*** window ***/
	yesnowindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_transient_for (GTK_WINDOW (yesnowindow),
		GTK_WINDOW (mainwindow));
	gtk_window_set_title (GTK_WINDOW (yesnowindow), "save SGF?");
	if ((iQuitRestartType != 3) && ((iIsComputerB != 1) || (iIsComputerW != 1)))
	{
		/*** Close yesnowindow. ***/
		g_signal_connect (yesnowindow, "delete_event",
			G_CALLBACK (DestroyYesNo), GINT_TO_POINTER (0));
	} else {
		/*** Show save SGF dialog. ***/
		g_signal_connect (yesnowindow, "delete_event",
			G_CALLBACK (DestroyYesNo), GINT_TO_POINTER (1));
	}
	gtk_window_set_resizable (GTK_WINDOW (yesnowindow), FALSE);
	gtk_container_set_border_width (GTK_CONTAINER (yesnowindow), 0);
	gtk_widget_realize (yesnowindow);

	/*** box ***/
	yesnobox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width (GTK_CONTAINER (yesnobox), 0);
	gtk_container_add (GTK_CONTAINER (yesnowindow), yesnobox);
	gtk_widget_show (yesnobox);

	/*** grid ***/
	yesnogrid = gtk_grid_new();
	gtk_box_pack_start (GTK_BOX (yesnobox), yesnogrid, TRUE, TRUE, 0);
	gtk_widget_show (yesnogrid);

	/*** "yes" box ***/
	yesnoeventyes = gtk_event_box_new();
	gtk_widget_set_size_request (yesnoeventyes, 100, 30);
	gtk_grid_attach (GTK_GRID (yesnogrid), yesnoeventyes, 0, 0, 1, 1);
	/*** Show save SGF dialog. ***/
	g_signal_connect (yesnoeventyes, "button_press_event",
		G_CALLBACK (DestroyYesNo), GINT_TO_POINTER (1));
	gtk_widget_show (yesnoeventyes);

	/*** "yes" image ***/
	snprintf (sPFImage, MAX_IMAGE, "%s", PKGDATADIR"png/yes.png");
	CheckAccess (sPFImage);
	yesnoim = gtk_image_new_from_file (sPFImage);
	gtk_container_add (GTK_CONTAINER (yesnoeventyes), yesnoim);
	gtk_widget_show (yesnoim);

	/*** "no" box ***/
	yesnoeventno = gtk_event_box_new();
	gtk_widget_set_size_request (yesnoeventno, 100, 30);
	gtk_grid_attach (GTK_GRID (yesnogrid), yesnoeventno, 1, 0, 1, 1);
	if ((iQuitRestartType == 1) || (iQuitRestartType == 3))
	{
		/*** Close yesnowindow and quit. ***/
		g_signal_connect (yesnoeventno, "button_press_event",
			G_CALLBACK (DestroyYesNo), GINT_TO_POINTER (3));
	}
	if (iQuitRestartType == 2)
	{
		/*** Close yesnowindow and restart. ***/
		g_signal_connect (yesnoeventno, "button_press_event",
			G_CALLBACK (DestroyYesNo), GINT_TO_POINTER (2));
	}
	gtk_widget_show (yesnoeventno);

	/*** "no" image ***/
	snprintf (sPFImage, MAX_IMAGE, "%s", PKGDATADIR"png/no.png");
	CheckAccess (sPFImage);
	yesnoim = gtk_image_new_from_file (sPFImage);
	gtk_container_add (GTK_CONTAINER (yesnoeventno), yesnoim);
	gtk_widget_show (yesnoim);

	iWindowOpen = 1;
	gtk_widget_show (yesnowindow);
	if (iOptions == 0) { Play ("open.ogg", 0); }
}
/*****************************************************************************/
