/* gtkgo v0.0.12 (Options.c) (November 2022)
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

#include "Options.h"

/*****************************************************************************/
gboolean ChangeHandicap (GtkWidget *widget, GdkEvent *event, gpointer data)
/*****************************************************************************/
{
	GdkEventButton *button;

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	button = (GdkEventButton *)event;
	switch (button->button)
	{
		case 1: Handicap (GINT_TO_POINTER (1)); break; /*** left ***/
		case 3: Handicap (GINT_TO_POINTER (2)); break; /*** right ***/
	}

	return (TRUE);
}
/*****************************************************************************/
gboolean PlayerPopUp (GtkWidget *widget, GdkEvent *event, gpointer data)
/*****************************************************************************/
{
	GdkEventButton *button;

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (event != NULL) { } /*** To prevent (set but) unused warnings. ***/

	if (iFileDialogOpen != 0) { return (FALSE); }
	if (iConnected != 0) { return (FALSE); }
	if (iWindowOpen != 0) { return (FALSE); }
	if ((iIsComputerB == 1) && (iIsComputerW == 1)) { return (FALSE); }

	button = (GdkEventButton *)event;
	gtk_menu_popup (GTK_MENU (data), NULL, NULL, NULL, NULL,
		button->button, button->time);

	return (TRUE);
}
/*****************************************************************************/
void CreateButtonBox (GtkWidget **button, GtkWidget **image, char *sImageP,
	int iWidth, GCallback GC, gpointer gwid,
	int iPlaceX, int iPlaceY, int iPlaceW)
/*****************************************************************************/
{
	char sX[MAX_X + 2];
	char sImage[MAX_IMAGE + 2];

	/*** button ***/
	*button = gtk_event_box_new();
	gtk_widget_set_size_request (*button, iWidth, 30);
	gtk_grid_attach (GTK_GRID (optionsgrid), *button,
		iPlaceX, iPlaceY, iPlaceW, 1);
	g_signal_connect (*button, "button_press_event",
		G_CALLBACK (GC), GTK_WIDGET (gwid));
	gtk_widget_show (*button);

	/*** image ***/
	switch (iOptionsX)
	{
		case 0: snprintf (sX, MAX_X, "%s", ""); break;
		case 1: snprintf (sX, MAX_X, "%s", "x"); break;
	}
	snprintf (sImage, MAX_IMAGE, PKGDATADIR"png/options%s/%s.png", sX, sImageP);
	CheckAccess (sImage);
	*image = gtk_image_new_from_file (sImage);
	gtk_container_add (GTK_CONTAINER (*button), *image);
	gtk_widget_show (*image);
}
/*****************************************************************************/
void Options (GtkWidget *widget, gpointer data)
/*****************************************************************************/
{
	/* GtkWidget *widget receives either GtkMenuItem *menuitem
	 * or GtkButton *button.
	 */

	GtkWidget *optionsbox;
	GtkWidget *menuwhite;
	GtkWidget *menublack;
	GtkWidget *menuitems;
	/***/
	char sImageP[200];

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	if (iFileDialogOpen != 0) { return; }
	if (iWindowOpen != 0) { return; }

	if (iOptions == 0)
	{
		Play ("options.ogg", 1);

		/*** window ***/
		optionswindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title (GTK_WINDOW (optionswindow), "options");
		g_signal_connect (optionswindow, "delete_event",
			G_CALLBACK (DestroyOptions), NULL);
		gtk_window_set_resizable (GTK_WINDOW (optionswindow), FALSE);
		gtk_container_set_border_width (GTK_CONTAINER (optionswindow), 0);
		gtk_widget_realize (optionswindow);

		/*** box ***/
		optionsbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
		gtk_container_set_border_width (GTK_CONTAINER (optionsbox), 0);
		gtk_container_add (GTK_CONTAINER (optionswindow), optionsbox);
		gtk_widget_show (optionsbox);

		/*** grid ***/
		optionsgrid = gtk_grid_new();
		gtk_widget_show (optionsgrid);
		gtk_box_pack_start (GTK_BOX (optionsbox), optionsgrid, TRUE, TRUE, 0);

		/*** menu for white ***/
		menuwhite = gtk_menu_new();
		menuitems = gtk_menu_item_new_with_label ("human player");
		gtk_menu_shell_append (GTK_MENU_SHELL (menuwhite), menuitems);
		g_signal_connect (menuitems, "activate",
			G_CALLBACK (Human), GINT_TO_POINTER (1));
		gtk_widget_show (menuitems);
		menuitems = gtk_menu_item_new_with_label ("go-computer");
		gtk_menu_shell_append (GTK_MENU_SHELL (menuwhite), menuitems);
		g_signal_connect (menuitems, "activate",
			G_CALLBACK (TheComputer), GINT_TO_POINTER (1));
		gtk_widget_show (menuitems);

		/*** menu for black ***/
		menublack = gtk_menu_new();
		menuitems = gtk_menu_item_new_with_label ("human player");
		gtk_menu_shell_append (GTK_MENU_SHELL (menublack), menuitems);
		g_signal_connect (menuitems, "activate",
			G_CALLBACK (Human), GINT_TO_POINTER (2));
		gtk_widget_show (menuitems);
		menuitems = gtk_menu_item_new_with_label ("go-computer");
		gtk_menu_shell_append (GTK_MENU_SHELL (menublack), menuitems);
		g_signal_connect (menuitems, "activate",
			G_CALLBACK (TheComputer), GINT_TO_POINTER (2));
		gtk_widget_show (menuitems);

		CreateButtonBox (&optionsbutton1, &optionsim1, "1", 200,
			(GCallback) PlayerPopUp, GTK_WIDGET (menuwhite), 0, 0, 2);
		CreateButtonBox (&optionsbutton2, &optionsim2, "2", 200,
			(GCallback) PlayerPopUp, GTK_WIDGET (menublack), 0, 1, 2);
		CreateButtonBox (&optionsbutton3, &optionsim3, "3", 200,
			(GCallback) Connect, NULL, 0, 2, 2);
		CreateButtonBox (&optionsbutton4, &optionsim4, "4", 200,
			(GCallback) TimeLimit, NULL, 0, 3, 2);
		CreateButtonBox (&optionsbutton5, &optionsim5, "5", 180,
			(GCallback) CallHelp, NULL, 0, 4, 1);
		CreateButtonBox (&optionsbutton5b, &optionsim5b, "5b", 20,
			(GCallback) OptionsX, NULL, 1, 4, 1);
		CreateButtonBox (&optionsbutton6, &optionsim6, "6", 180,
			(GCallback) Tooltips, NULL, 0, 5, 1);
		if (iTooltips == 1)
		{
			CreateButtonBox (&optionsbutton6b, &optionsim6b, "6on", 20,
				(GCallback) Tooltips, NULL, 1, 5, 1);
		} else {
			CreateButtonBox (&optionsbutton6b, &optionsim6b, "6off", 20,
				(GCallback) Tooltips, NULL, 1, 5, 1);
		}
		CreateButtonBox (&optionsbutton7, &optionsim7, "7", 180,
			(GCallback) Latest, NULL, 0, 6, 1);
		if (iLatest == 1)
		{
			CreateButtonBox (&optionsbutton7b, &optionsim7b, "7on", 20,
				(GCallback) Latest, NULL, 1, 6, 1);
		} else {
			CreateButtonBox (&optionsbutton7b, &optionsim7b, "7off", 20,
				(GCallback) Latest, NULL, 1, 6, 1);
		}
		CreateButtonBox (&optionsbutton8, &optionsim8, "8", 180,
			(GCallback) Sound, NULL, 0, 7, 1);
		if (iSound == 1)
		{
			CreateButtonBox (&optionsbutton8b, &optionsim8b, "8on", 20,
				(GCallback) Sound, NULL, 1, 7, 1);
		} else {
			CreateButtonBox (&optionsbutton8b, &optionsim8b, "8off", 20,
				(GCallback) Sound, NULL, 1, 7, 1);
		}
		CreateButtonBox (&optionsbutton9, &optionsim9, "9", 180,
			(GCallback) ChangeHandicap, NULL, 0, 8, 1);
		snprintf (sImageP, 200, "9%i", iHandicap);
		CreateButtonBox (&optionsbutton9b, &optionsim9b, sImageP, 20,
			(GCallback) ChangeHandicap, NULL, 1, 8, 1);

		gtk_widget_show (optionswindow);
		iOptions = 1;
	} else {
		/*** Bring the options window to the foreground. ***/
		gtk_window_present (GTK_WINDOW (optionswindow));
	}
}
/*****************************************************************************/
