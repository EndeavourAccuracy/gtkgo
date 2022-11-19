/* gtkgo v0.0.12 (PixmapOnPoint.c) (November 2022)
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

#include "PixmapOnPoint.h"

/*****************************************************************************/
gboolean DrawCallback (GtkWidget *widget, cairo_t *cr, gpointer data)
/*****************************************************************************/
{
	GdkPixbuf *pixbuf;
	GtkAllocation* alloc;
	GtkRequisition minimum, natural;
	/***/
	int iWidth, iHeight, iGoH;
	int iPoint;
	int iMenuBarH, iStatusBarH;

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/

	iPoint = GPOINTER_TO_INT (data);

	/*** Calculate the width and height. ***/
	alloc = g_new (GtkAllocation, 1);
	gtk_widget_get_allocation (mainim[iPoint], alloc);
	iWidth = alloc->width;
	iHeight = alloc->height;
	g_free (alloc);

	/*** Draw the scaled pixbuf. ***/
	pixbuf = gdk_pixbuf_scale_simple (pixbuforig[iPoint],
		iWidth, iHeight, GDK_INTERP_HYPER);
	gdk_cairo_set_source_pixbuf (cr, pixbuf, 0, 0);
	g_object_unref (pixbuf);
	cairo_paint (cr);

	/*** Add margins to center the go grid. ***/
	gtk_widget_get_preferred_size (maingridmenubar, &minimum, &natural);
	iMenuBarH = natural.height;
	gtk_widget_get_preferred_size (maingridstatusbars, &minimum, &natural);
	iStatusBarH = natural.height;
	if (iPSize != 0)
	{
		gtk_window_get_size (GTK_WINDOW (mainwindow), &iWidth, &iHeight);
	} else {
		iWidth = gdk_screen_get_width (screen);
		iHeight = gdk_screen_get_height (screen);
	}
	iGoH = iHeight - iMenuBarH - iStatusBarH;
	if (iWidth > iGoH)
	{
		/*** horizontal ***/
		gtk_widget_set_margin_start (mainframe, (iWidth - iGoH) / 2);
		gtk_widget_set_margin_end (mainframe, (iWidth - iGoH) / 2);
		gtk_widget_set_margin_top (mainframe, 0);
		gtk_widget_set_margin_bottom (mainframe, 0);
	} else {
		/*** vertical ***/
		gtk_widget_set_margin_start (mainframe, 0);
		gtk_widget_set_margin_end (mainframe, 0);
		gtk_widget_set_margin_top (mainframe, (iGoH - iWidth) / 2);
		gtk_widget_set_margin_bottom (mainframe, (iGoH - iWidth) / 2);
	}

	return (TRUE);
}
/*****************************************************************************/
void PopUpMenu (GtkWidget *widget, GdkEvent *event)
/*****************************************************************************/
{
	GtkWidget *menuitem;
	GtkWidget *menu;
	GdkEventButton *eventbutton;

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/

	eventbutton = (GdkEventButton *)event;
	menu = gtk_menu_new();

	menuitem = gtk_menu_item_new_with_label ("Hint");
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
	g_signal_connect (menuitem, "activate", G_CALLBACK (Hint), NULL);
	gtk_widget_show (menuitem);

	menuitem = gtk_menu_item_new_with_label ("Undo");
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
	g_signal_connect (menuitem, "activate", G_CALLBACK (Undo), NULL);
	gtk_widget_show (menuitem);

	menuitem = gtk_menu_item_new_with_label ("Help...");
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
	g_signal_connect (menuitem, "activate", G_CALLBACK (Help), NULL);
	gtk_widget_show (menuitem);

	menuitem = gtk_menu_item_new_with_label ("About...");
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
	g_signal_connect (menuitem, "activate", G_CALLBACK (About), NULL);
	gtk_widget_show (menuitem);

	gtk_menu_popup (GTK_MENU (menu), NULL, NULL, NULL, NULL,
		eventbutton->button, eventbutton->time);
}
/*****************************************************************************/
gboolean MenuOrMove (GtkWidget *widget, GdkEvent *event, gpointer data)
/*****************************************************************************/
{
	GdkEventButton *eventbutton;

	eventbutton = (GdkEventButton *)event;

	switch (eventbutton->button)
	{
		case 1: /*** left ***/
			MakeMove (widget, event, GINT_TO_POINTER (data)); break;
		case 3: /*** right ***/
			PopUpMenu (widget, event); break;
	}

	return (TRUE);
}
/*****************************************************************************/
void PixmapOnPoint (int iPoint)
/*****************************************************************************/
{
	GdkDisplay *display;
	/***/
	char cCoorX;
	int iXaxis, iYaxis;
	char sPFPoint[200];
	char sCoor[MAX_COOR];

	iXaxis = iPoint % 19;
	if (iXaxis == 0) { iXaxis = 19; }
	iYaxis = ((iPoint - 1) / 19) + 1;

	if (mainim[iPoint] != NULL)
	{
		gtk_container_remove (GTK_CONTAINER (maineventboxes[iPoint]),
			GTK_WIDGET (mainim[iPoint]));
	}

	if (maineventboxes[iPoint] == NULL)
	{
		maineventboxes[iPoint] = gtk_event_box_new();
		gtk_grid_attach (GTK_GRID (maingridpoints), maineventboxes[iPoint],
			iXaxis - 1, iYaxis - 1, 1, 1);
		g_object_set (maineventboxes[iPoint], "hexpand", TRUE, NULL);
		g_object_set (maineventboxes[iPoint], "vexpand", TRUE, NULL);
		gtk_widget_set_halign (maineventboxes[iPoint], GTK_ALIGN_FILL);
		gtk_widget_set_valign (maineventboxes[iPoint], GTK_ALIGN_FILL);
		gtk_widget_realize (maineventboxes[iPoint]);
		display = gdk_display_get_default();
		gdk_window_set_cursor (gtk_widget_get_window (maineventboxes[iPoint]),
			gdk_cursor_new_for_display (display, GDK_DOT));
		gtk_widget_show (maineventboxes[iPoint]);
	}

	/*** pixbuf ***/
	if ((iLatest == 0) && (Board[iPoint][3] == 'l'))
	{
		snprintf (sPFPoint, 200, PKGDATADIR"skins/%s/%c%c%c.png", sCurrentSkin,
			Board[iPoint][0], Board[iPoint][1], Board[iPoint][2]);
	} else {
		snprintf (sPFPoint, 200, PKGDATADIR"skins/%s/%s.png", sCurrentSkin,
			Board[iPoint]);
	}
	CheckAccess (sPFPoint);
	pixbuforig[iPoint] = gdk_pixbuf_new_from_file (sPFPoint, NULL);

	/*** drawing area ***/
	mainim[iPoint] = gtk_drawing_area_new();
	g_signal_connect (maineventboxes[iPoint], "button_press_event",
		G_CALLBACK (MenuOrMove), GINT_TO_POINTER (iPoint));
	g_signal_connect (mainim[iPoint], "draw",
		G_CALLBACK (DrawCallback), GINT_TO_POINTER (iPoint));
	gtk_container_add (GTK_CONTAINER (maineventboxes[iPoint]),
		mainim[iPoint]);
	gtk_widget_show (mainim[iPoint]);

	/*** tooltip ***/
	if (iXaxis > 8) { iXaxis++; } /*** Skip I. ***/
	cCoorX = 64 + iXaxis;
	snprintf (sCoor, MAX_COOR, "%c%i (%i/%s)", cCoorX, 20 - iYaxis, iPoint,
		PointToPlace (1, iPoint));
	gtk_widget_set_tooltip_text (maineventboxes[iPoint], sCoor);
}
/*****************************************************************************/
