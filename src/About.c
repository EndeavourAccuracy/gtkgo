/* gtkgo v0.0.12 (About.c) (November 2022)
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

#include "About.h"

/*****************************************************************************/
void About (GtkMenuItem *menuitem, gpointer data)
/*****************************************************************************/
{
	GtkWidget *aboutdialog;
	GdkPixbuf *abouticon;
	/***/
	char sPFImage[MAX_IMAGE + 2];

	if (menuitem != NULL) { } /*** To prevent (set but) unused warnins. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnins. ***/

	if (iWindowOpen != 0) { return; }

	if (iOptions == 0) { Play ("open.ogg", 0); }

	/*** dialog ***/
	aboutdialog = gtk_about_dialog_new();
	gtk_window_set_transient_for (GTK_WINDOW (aboutdialog),
		GTK_WINDOW (mainwindow));
	gtk_about_dialog_set_program_name (GTK_ABOUT_DIALOG (aboutdialog),
		GAME_NAME);
	gtk_about_dialog_set_version (GTK_ABOUT_DIALOG (aboutdialog), "v"
		GAME_VERSION " (" GAME_MONTHYEAR ")");
	gtk_about_dialog_set_copyright (GTK_ABOUT_DIALOG (aboutdialog), GAME_COPY);
	gtk_about_dialog_set_comments (GTK_ABOUT_DIALOG (aboutdialog), GAME_GOAL);
	gtk_about_dialog_set_license_type (GTK_ABOUT_DIALOG (aboutdialog),
		GTK_LICENSE_GPL_2_0);
	gtk_about_dialog_set_website (GTK_ABOUT_DIALOG (aboutdialog),
		GAME_WEBSITE);
	gtk_about_dialog_set_website_label (GTK_ABOUT_DIALOG (aboutdialog),
		GAME_NAME " website");
	const gchar *authors[] = { GAME_AUTHOR, NULL };
	const gchar *contrib[] = {
		/*** Alphabetical, by last name. ***/
		"Emmanuel Dumas",
		"Joris van Gasteren",
		"Petter Reinholdtsen",
		NULL };
	gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG (aboutdialog), authors);
	gtk_about_dialog_add_credit_section (GTK_ABOUT_DIALOG (aboutdialog),
		"Contributors", contrib);
	snprintf (sPFImage, MAX_IMAGE, "%s",
		PKGDATADIR"png/icons/gnome-gtkgo.png");
	CheckAccess (sPFImage);
	abouticon = gdk_pixbuf_new_from_file (sPFImage, NULL);
	gtk_about_dialog_set_logo (GTK_ABOUT_DIALOG (aboutdialog), abouticon);
	gtk_window_set_title (GTK_WINDOW (aboutdialog), "about");
	gtk_dialog_run (GTK_DIALOG (aboutdialog));

	/*** Always remove the dialog. ***/
	gtk_widget_destroy (aboutdialog);
}
/*****************************************************************************/
