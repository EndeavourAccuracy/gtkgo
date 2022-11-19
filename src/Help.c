/* gtkgo v0.0.12 (Help.c) (November 2022)
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

#include "Help.h"

/*****************************************************************************/
void DestroyHelp (void)
/*****************************************************************************/
{
	/* Using void, but this function is called as:
	 * - void user_function (GtkButton *button, gpointer data)
	 * - gboolean user_function (GtkWidget *widget, GdkEvent *event,
	 * gpointer data)
	 */

	iWindowOpen = 0;
	gtk_widget_destroy (helpwindow);
}
/*****************************************************************************/
void ToggleWrapH (GtkToggleButton *togglebutton, gpointer data)
/*****************************************************************************/
{
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton)) == TRUE)
	{
		/*** lowered ***/
		gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (helptext), GTK_WRAP_WORD_CHAR);
	} else {
		/*** raised ***/
		gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (helptext), GTK_WRAP_NONE);
	}
}
/*****************************************************************************/
gboolean CallHelp (GtkWidget *widget, GdkEvent *event, gpointer data)
/*****************************************************************************/
{
	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (event != NULL) { } /*** To prevent (set but) unused warnings. ***/

	Help (NULL, data);

	return (TRUE);
}
/*****************************************************************************/
void Help (GtkMenuItem *menuitem, gpointer data)
/*****************************************************************************/
{
	/* The help window can be opened from three locations: the Help menu, by
	 * right clicking the board, and from the options window.
	 */

	if (menuitem != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	GtkWidget *helpbox;
	GtkWidget *helpgridtext;
	GtkWidget *helpgridrest;
	GtkWidget *helpscrolled;
	GtkWidget *helpcheckwrap;
	GtkWidget *helpsep;
	GtkWidget *helpbutton;
	GtkTextBuffer *gtkbuffer;
	GtkTextIter gtkiter;
	/***/
	int iHelpFD;
	int iRead;
	char sBuffer[1024];

	if (iFileDialogOpen != 0) { return; }
	if ((iIsComputerB == 1) && (iIsComputerW == 1)) { return; }

	if (iWindowOpen == 0)
	{
		/*** window ***/
		helpwindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_window_set_transient_for (GTK_WINDOW (helpwindow),
			GTK_WINDOW (mainwindow));
		gtk_window_set_title (GTK_WINDOW (helpwindow), "help");
		g_signal_connect (helpwindow, "delete_event",
			G_CALLBACK (DestroyHelp), NULL);
		gtk_window_set_resizable (GTK_WINDOW (helpwindow), TRUE);
		gtk_container_set_border_width (GTK_CONTAINER (helpwindow), 0);
		gtk_widget_realize (helpwindow);

		/*** box ***/
		helpbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
		gtk_container_set_border_width (GTK_CONTAINER (helpbox), 0);
		gtk_container_add (GTK_CONTAINER (helpwindow), helpbox);
		gtk_widget_show (helpbox);

		/*** grid text ***/
		helpgridtext = gtk_grid_new();
		gtk_widget_show (helpgridtext);
		gtk_box_pack_start (GTK_BOX (helpbox), helpgridtext, TRUE, TRUE, 0);

		/*** grid rest ***/
		helpgridrest = gtk_grid_new();
		gtk_widget_show (helpgridrest);
		gtk_box_pack_start (GTK_BOX (helpbox), helpgridrest, FALSE, FALSE, 0);

		/*** scrolled ***/
		helpscrolled = gtk_scrolled_window_new (NULL, NULL);
		gtk_widget_set_size_request (helpscrolled, 535, 266);
		gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (helpscrolled),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		gtk_grid_attach (GTK_GRID (helpgridtext), helpscrolled, 0, 0, 1, 1);
		g_object_set (helpscrolled, "hexpand", TRUE, NULL);
		g_object_set (helpscrolled, "vexpand", TRUE, NULL);
		g_object_set (helpscrolled, "margin", 10, NULL);
		gtk_widget_show (helpscrolled);

		/*** text ***/
		helptext = gtk_text_view_new();
		gtk_text_view_set_editable (GTK_TEXT_VIEW (helptext), FALSE);
		gtk_text_view_set_monospace (GTK_TEXT_VIEW (helptext), TRUE);
		gtk_container_add (GTK_CONTAINER (helpscrolled), helptext);
		gtk_widget_show (helptext);

		/*** check wrap ***/
		helpcheckwrap = gtk_check_button_new_with_label ("wrap");
		gtk_grid_attach (GTK_GRID (helpgridrest), helpcheckwrap, 0, 0, 1, 1);
		g_object_set (helpcheckwrap, "margin", 10, NULL);
		gtk_widget_set_margin_top (helpcheckwrap, 0);
		g_signal_connect (helpcheckwrap, "toggled",
			G_CALLBACK (ToggleWrapH), NULL);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (helpcheckwrap), FALSE);
		gtk_widget_show (helpcheckwrap);

		/*** separator ***/
		helpsep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
		gtk_grid_attach (GTK_GRID (helpgridrest), helpsep, 0, 1, 1, 1);
		g_object_set (helpsep, "hexpand", TRUE, NULL);
		gtk_widget_show (helpsep);

		/*** button ***/
		helpbutton = gtk_button_new_with_mnemonic ("_Close");
		g_signal_connect (helpbutton, "clicked",
			G_CALLBACK (DestroyHelp), NULL);
		gtk_widget_set_can_default (helpbutton, TRUE);
		gtk_window_set_default (GTK_WINDOW (helpwindow), helpbutton);
		gtk_grid_attach (GTK_GRID (helpgridrest), helpbutton, 0, 2, 1, 1);
		g_object_set (helpbutton, "hexpand", TRUE, NULL);
		g_object_set (helpbutton, "margin", 2, NULL);
		gtk_widget_show (helpbutton);

		/*** The following could also be done with g_file_get_contents(). ***/
		iHelpFD = open (PKGDATADIR"docs/README.txt", O_RDONLY, 0600);
		if (iHelpFD == -1)
		{
			Message ("Could not open README.txt file.", 3, 0);
		} else {
			gtkbuffer = gtk_text_buffer_new (NULL);
			do {
				iRead = read (iHelpFD, sBuffer, 1024);
				gtkbuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (helptext));
				gtk_text_buffer_get_end_iter (gtkbuffer, &gtkiter);
				gtk_text_buffer_insert (gtkbuffer, &gtkiter, sBuffer, iRead);
			} while (iRead == 1024);
		}
		close (iHelpFD);

		gtk_widget_show (helpwindow);
		iWindowOpen = 1;

		if (iOptions == 0) { Play ("open.ogg", 0); }
	}
}
/*****************************************************************************/
