/* gtkgo v0.0.12 (TimeLimit.c) (November 2022)
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

#include "TimeLimit.h"

/*****************************************************************************/
gboolean DestroyTime (GtkWidget *widget, GdkEvent *event, gpointer data)
/*****************************************************************************/
{
	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (event != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	gtk_widget_destroy (timewindow);
	iWindowOpen = 0;

	return (TRUE);
}
/*****************************************************************************/
gboolean TimeLimit (GtkWidget *widget, GdkEvent *event, gpointer data)
/*****************************************************************************/
{
	GtkWidget *timebox;
	GtkWidget *timegrid;
	GtkWidget *timelabel;
	GtkWidget *timesep;
	GtkWidget *timebutton;
	/***/
	char sTime[7];

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (event != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	if (iFileDialogOpen != 0) { return (FALSE); }
	if ((iIsComputerB == 1) && (iIsComputerW == 1)) { return (FALSE); }
	if (iConnected != 0)
	{
		Message ("To manually set a time limit, disconnect first.", 3, 0);
		return (FALSE);
	}

	if (iWindowOpen == 0)
	{
		/*** window ***/
		timewindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_window_set_transient_for (GTK_WINDOW (timewindow),
			GTK_WINDOW (optionswindow));
		gtk_window_set_title (GTK_WINDOW (timewindow), "time limit");
		g_signal_connect (timewindow, "delete_event",
			G_CALLBACK (DestroyTime), NULL);
		gtk_window_set_resizable (GTK_WINDOW (timewindow), FALSE);
		gtk_container_set_border_width (GTK_CONTAINER (timewindow), 0);
		gtk_widget_realize (timewindow);

		/*** box ***/
		timebox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
		gtk_container_set_border_width (GTK_CONTAINER (timebox), 0);
		gtk_container_add (GTK_CONTAINER (timewindow), timebox);
		gtk_widget_show (timebox);

		/*** grid ***/
		timegrid = gtk_grid_new();
		gtk_box_pack_start (GTK_BOX (timebox), timegrid, TRUE, TRUE, 0);
		gtk_widget_show (timegrid);

		/*** label ***/
		timelabel = gtk_label_new ("Enter time limit in <m> or <h:m>.");
		gtk_label_set_justify (GTK_LABEL (timelabel), GTK_JUSTIFY_CENTER);
		gtk_grid_attach (GTK_GRID (timegrid), timelabel, 0, 0, 1, 1);
		g_object_set (timelabel, "margin", 10, NULL);
		gtk_widget_show (timelabel);

		/*** Construct sTime. ***/
		iTimeLimitSetM = iTimeLimit;
		if (iTimeLimitSetM > 59)
		{
			iTimeLimitSetH = 0;
			do
			{
				iTimeLimitSetM-=60;
				iTimeLimitSetH++;
			} while (iTimeLimitSetM >= 60);
			if (iTimeLimitSetM < 10)
			{
				snprintf (sTime, 7, "%i:0%i", iTimeLimitSetH, iTimeLimitSetM);
			} else {
				snprintf (sTime, 7, "%i:%i", iTimeLimitSetH, iTimeLimitSetM);
			}
		} else {
			if (iTimeLimitSetM < 10)
			{
				snprintf (sTime, 7, "0%i", iTimeLimitSetM);
			} else {
				snprintf (sTime, 7, "%i", iTimeLimitSetM);
			}
		}

		/*** entry ***/
		timeentry = gtk_entry_new();
		gtk_entry_set_max_length (GTK_ENTRY (timeentry), 6);
		g_signal_connect (timeentry, "activate",
			G_CALLBACK (SetTimeLimit), NULL);
		gtk_entry_set_text (GTK_ENTRY (timeentry), sTime);
		gtk_editable_select_region (GTK_EDITABLE (timeentry), 0,
			gtk_entry_get_text_length (GTK_ENTRY (timeentry)));
		gtk_grid_attach (GTK_GRID (timegrid), timeentry, 0, 1, 1, 1);
		g_object_set (timeentry, "margin", 10, NULL);
		gtk_widget_set_margin_top (timeentry, 0);
		gtk_widget_grab_focus (timeentry);
		gtk_widget_show (timeentry);

		/*** separator ***/
		timesep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
		gtk_grid_attach (GTK_GRID (timegrid), timesep, 0, 2, 1, 1);
		gtk_widget_show (timesep);

		/*** button ***/
		timebutton = gtk_button_new_with_mnemonic ("_OK");
		g_signal_connect (timebutton, "clicked",
		G_CALLBACK (SetTimeLimit), NULL);
		gtk_widget_set_can_default (timebutton, TRUE);
		gtk_window_set_default (GTK_WINDOW (timewindow), timebutton);
		gtk_grid_attach (GTK_GRID (timegrid), timebutton, 0, 3, 1, 1);
		g_object_set (timebutton, "margin", 2, NULL);
		gtk_widget_show (timebutton);

		gtk_widget_show (timewindow);
		iWindowOpen = 1;
	}

	return (TRUE);
}
/*****************************************************************************/
