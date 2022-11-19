/* gtkgo v0.0.12 (MainWindow.c) (November 2022)
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

#include "MainWindow.h"

/*****************************************************************************/
void SizeAllocate (GtkWidget *widget, GdkRectangle *allocation, gpointer data)
/*****************************************************************************/
{
	/*** Currently does nothing. ***/

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (allocation != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

/***
	gtk_widget_queue_draw (GTK_WIDGET (mainwindow));
***/
}
/*****************************************************************************/
gboolean KeyPress (GtkWidget *widget, GdkEventKey *event, gpointer data)
/*****************************************************************************/
{
	int iButton;

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	/*** Alt+Enter ***/
	if ((event->state == GDK_MOD1_MASK) &&
		((strcmp (gdk_keyval_name (event->keyval), "Return") == 0) ||
		(strcmp (gdk_keyval_name (event->keyval), "KP_Enter") == 0)))
	{
		switch (iPSize)
		{
			case 0: iPSize = 30; break; /*** from fullscreen ***/
			default: iPSize = 0; break; /*** to fullscreen ***/
		}
		gtk_widget_destroy (mainwindow);
		for (iButton = 1; iButton <= POINTS; iButton++)
		{
			maineventboxes[iButton] = NULL;
			mainim[iButton] = NULL;
		}
		MainWindow();
		ReStart (2);
	}

	return (TRUE);
}
/*****************************************************************************/
void ButtonTop (GtkWidget **button, int iButtonWidth,
	int iTopPlace, GCallback GC, char *sName)
/*****************************************************************************/
{
	float fScale;
	char sPFSkin[200];
	GtkWidget *mainimbutton;
	GdkPixbuf *pixbuf;

	/*** button ***/
	*button = gtk_button_new();
	gtk_style_context_add_class (gtk_widget_get_style_context
		(GTK_WIDGET (*button)), "mainbutton");
	if ((iPSize == 0) || (iPSize >= 30))
	{
		fScale = 1;
	} else {
		fScale = (float)iPSize / 30;
	}
	gtk_widget_set_size_request (*button, iButtonWidth * fScale, 30 * fScale);
	gtk_grid_attach (GTK_GRID (maingridmenubar), *button, iTopPlace, 1, 1, 1);
	g_signal_connect (*button, "clicked", G_CALLBACK (GC), NULL);
	gtk_widget_show (*button);

	/*** image ***/
	snprintf (sPFSkin, 200, PKGDATADIR"skins/%s/%s.png", sCurrentSkin, sName);
	CheckAccess (sPFSkin);
	pixbuf = gdk_pixbuf_new_from_file_at_scale (sPFSkin, -1,
		24 * fScale, TRUE, NULL);
	mainimbutton = gtk_image_new_from_pixbuf (pixbuf);
	g_object_unref (pixbuf);
	gtk_container_add (GTK_CONTAINER (*button), mainimbutton);
	gtk_widget_show (mainimbutton);

	gtk_widget_set_tooltip_text (*button, sName);
}
/*****************************************************************************/
void MainWindow (void)
/*****************************************************************************/
{
	GtkWidget *menubar;
	GtkWidget *menuimage;
	GdkPixbuf *mainicon;
	/***/
	GtkWidget *menu_game;
	GtkWidget *menuitemmain_game;
	GtkWidget *menuitem_restart;
	GtkWidget *menuitem_pass;
	GtkWidget *menuitem_hint;
	GtkWidget *menuitem_undo;
	GtkWidget *menuitem_quit;
	/***/
	GtkWidget *menu_settings;
	GtkWidget *menuitemmain_settings;
	GtkWidget *menuitem_skin;
	GtkWidget *menuitem_resize;
	GtkWidget *menuitem_options;
	/***/
	GtkWidget *menu_help;
	GtkWidget *menuitemmain_help;
	GtkWidget *menuitem_help;
	GtkWidget *menuitem_about;
	/***/
	GtkWidget *mainbox1;
	GtkWidget *mainbox2;
	GtkWidget *mainbox3;
	GtkWidget *mainbox4;
	GtkWidget *mainbox5;
	/***/
	char sPFImage[MAX_IMAGE + 2];

	/*** window ***/
	mainwindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	snprintf (sPFImage, MAX_IMAGE, "%s", PKGDATADIR"png/icons/gnome-gtkgo.png");
	CheckAccess (sPFImage);
	mainicon = gdk_pixbuf_new_from_file (sPFImage, NULL);
	gtk_window_set_icon (GTK_WINDOW (mainwindow), mainicon);
	gtk_window_set_mnemonics_visible (GTK_WINDOW (mainwindow), TRUE);
	gtk_window_set_title (GTK_WINDOW (mainwindow),
		GAME_NAME " v" GAME_VERSION " (" GAME_MONTHYEAR ")");
	g_signal_connect (mainwindow, "delete_event",
		G_CALLBACK (Quit), NULL);
	g_signal_connect (mainwindow, "key-press-event",
		G_CALLBACK (KeyPress), NULL);
	g_signal_connect (mainwindow, "size-allocate",
		G_CALLBACK (SizeAllocate), NULL);
	gtk_container_set_border_width (GTK_CONTAINER (mainwindow), 0);
	gtk_widget_realize (mainwindow);

	/*** box area ***/
	mainbox1 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width (GTK_CONTAINER (mainbox1), 0);
	g_object_set (mainbox1, "hexpand", TRUE, NULL);
	g_object_set (mainbox1, "vexpand", TRUE, NULL);
	gtk_container_add (GTK_CONTAINER (mainwindow), mainbox1);
	gtk_widget_show (mainbox1);

	/*** menubar box ***/
	mainbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_set_border_width (GTK_CONTAINER (mainbox2), 0);
	gtk_box_pack_start (GTK_BOX (mainbox1), mainbox2, FALSE, FALSE, 0);
	gtk_widget_show (mainbox2);

	/*** frame box ***/
	mainbox3 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_style_context_add_class (gtk_widget_get_style_context
		(GTK_WIDGET (mainbox3)), "bgwhite");
	gtk_container_set_border_width (GTK_CONTAINER (mainbox3), 0);
	gtk_box_pack_start (GTK_BOX (mainbox1), mainbox3, TRUE, TRUE, 0);
	gtk_widget_show (mainbox3);

	/*** frame ***/
	mainframe = gtk_aspect_frame_new (NULL, 0, 0, 1, FALSE);
	gtk_style_context_add_class (gtk_widget_get_style_context
		(GTK_WIDGET (mainframe)), "frame");
	g_object_set (mainframe, "shadow-type", GTK_SHADOW_NONE, NULL);
	gtk_box_pack_start (GTK_BOX (mainbox3), mainframe, TRUE, TRUE, 0);
	gtk_widget_show (mainframe);

	/*** go box on frame ***/
	mainbox4 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_set (mainbox4, "hexpand", TRUE, NULL);
	g_object_set (mainbox4, "vexpand", TRUE, NULL);
	gtk_container_set_border_width (GTK_CONTAINER (mainbox4), 0);
	gtk_container_add (GTK_CONTAINER (mainframe), mainbox4);
	gtk_widget_show (mainbox4);

	/*** statusbars box ***/
	mainbox5 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_set_border_width (GTK_CONTAINER (mainbox5), 0);
	gtk_box_pack_start (GTK_BOX (mainbox1), mainbox5, FALSE, FALSE, 0);
	gtk_widget_show (mainbox5);

	/*** menubar grid ***/
	maingridmenubar = gtk_grid_new();
	gtk_widget_show (maingridmenubar);
	gtk_box_pack_start (GTK_BOX (mainbox2), maingridmenubar, TRUE, TRUE, 0);

	/*** points grid ***/
	maingridpoints = gtk_grid_new();
	g_object_set (maingridpoints, "hexpand", TRUE, NULL);
	g_object_set (maingridpoints, "vexpand", TRUE, NULL);
	gtk_box_pack_start (GTK_BOX (mainbox4), maingridpoints, TRUE, TRUE, 0);
	gtk_widget_show (maingridpoints);

	/*** statusbars grid ***/
	maingridstatusbars = gtk_grid_new();
	gtk_widget_show (maingridstatusbars);
	gtk_box_pack_start (GTK_BOX (mainbox5), maingridstatusbars, TRUE, TRUE, 0);

	menubar = gtk_menu_bar_new();

/* GTK+ more or less deprecated images on menu items, but I still
 * want to use them. I don't want warnings about it. I used
 * gtk3-icon-browser to get an overview of GTK+ icons.
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

	/*** Game menu. ***/
	menu_game = gtk_menu_new();
	menuitemmain_game = gtk_menu_item_new_with_mnemonic ("_Game");
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitemmain_game), menu_game);
	/***/
	menuitem_restart = gtk_image_menu_item_new_with_mnemonic ("Re_start");
	menuimage = gtk_image_new_from_icon_name ("document-new",
		GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (menuitem_restart),
		GTK_WIDGET (menuimage));
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_game), menuitem_restart);
	g_signal_connect (G_OBJECT (menuitem_restart), "activate",
		G_CALLBACK (CallReStart), NULL);
	/***/
	menuitem_pass = gtk_image_menu_item_new_with_mnemonic ("_Pass");
	menuimage = gtk_image_new_from_icon_name ("process-stop",
		GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (menuitem_pass),
		GTK_WIDGET (menuimage));
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_game), menuitem_pass);
	g_signal_connect (G_OBJECT (menuitem_pass), "activate",
		G_CALLBACK (Pass), NULL);
	/***/
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_game),
		gtk_separator_menu_item_new());
	/***/
	menuitem_hint = gtk_image_menu_item_new_with_mnemonic ("_Hint");
	menuimage = gtk_image_new_from_icon_name ("edit-redo",
		GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (menuitem_hint),
		GTK_WIDGET (menuimage));
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_game), menuitem_hint);
	g_signal_connect (G_OBJECT (menuitem_hint), "activate",
		G_CALLBACK (Hint), NULL);
	/***/
	menuitem_undo = gtk_image_menu_item_new_with_mnemonic ("_Undo");
	menuimage = gtk_image_new_from_icon_name ("edit-undo",
		GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (menuitem_undo),
		GTK_WIDGET (menuimage));
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_game), menuitem_undo);
	g_signal_connect (G_OBJECT (menuitem_undo), "activate",
		G_CALLBACK (Undo), NULL);
	/***/
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_game),
		gtk_separator_menu_item_new());
	/***/
	menuitem_quit = gtk_image_menu_item_new_with_mnemonic ("_Quit");
	menuimage = gtk_image_new_from_icon_name ("application-exit",
		GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (menuitem_quit),
		GTK_WIDGET (menuimage));
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_game), menuitem_quit);
	g_signal_connect (G_OBJECT (menuitem_quit), "activate",
		G_CALLBACK (CallQuit), NULL);
	/***/
	gtk_menu_shell_append (GTK_MENU_SHELL (menubar), menuitemmain_game);

	/*** Settings menu. ***/
	menu_settings = gtk_menu_new();
	menuitemmain_settings = gtk_menu_item_new_with_mnemonic ("_Settings");
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitemmain_settings),
		menu_settings);
	/***/
	menuitem_skin = gtk_image_menu_item_new_with_mnemonic ("S_kin...");
	menuimage = gtk_image_new_from_icon_name ("preferences-desktop-theme",
		GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (menuitem_skin),
		GTK_WIDGET (menuimage));
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_settings), menuitem_skin);
	g_signal_connect (G_OBJECT (menuitem_skin), "activate",
		G_CALLBACK (Skin), NULL);
	/***/
	menuitem_resize = gtk_image_menu_item_new_with_mnemonic ("_Resize");
	menuimage = gtk_image_new_from_icon_name ("view-fullscreen",
		GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (menuitem_resize),
		GTK_WIDGET (menuimage));
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_settings), menuitem_resize);
	g_signal_connect (G_OBJECT (menuitem_resize), "activate",
		G_CALLBACK (ReSize), NULL);
	/***/
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_settings),
		gtk_separator_menu_item_new());
	/***/
	menuitem_options = gtk_image_menu_item_new_with_mnemonic ("_Options...");
	menuimage = gtk_image_new_from_icon_name ("preferences-other",
		GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (menuitem_options),
		GTK_WIDGET (menuimage));
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_settings), menuitem_options);
	g_signal_connect (G_OBJECT (menuitem_options), "activate",
		G_CALLBACK (Options), NULL);
	/***/
	gtk_menu_shell_append (GTK_MENU_SHELL (menubar), menuitemmain_settings);

	/*** Help menu. ***/
	menu_help = gtk_menu_new();
	gtk_widget_set_hexpand (menu_help, TRUE);
	gtk_widget_set_halign (menu_help, GTK_ALIGN_FILL);
	menuitemmain_help = gtk_menu_item_new_with_mnemonic ("_Help");
	g_object_set (menuitemmain_help, "right_justified", TRUE, NULL);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitemmain_help),
		menu_help);
	/***/
	menuitem_help = gtk_image_menu_item_new_with_mnemonic ("H_elp...");
	menuimage = gtk_image_new_from_icon_name ("accessories-dictionary",
		GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (menuitem_help),
		GTK_WIDGET (menuimage));
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_help), menuitem_help);
	g_signal_connect (G_OBJECT (menuitem_help), "activate",
		G_CALLBACK (Help), NULL);
	/***/
	menuitem_about = gtk_image_menu_item_new_with_mnemonic ("_About...");
	menuimage = gtk_image_new_from_icon_name ("help-about",
		GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (menuitem_about),
		GTK_WIDGET (menuimage));
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_help), menuitem_about);
	g_signal_connect (menuitem_about, "activate",
		G_CALLBACK (About), NULL);
	/***/
	gtk_menu_shell_append (GTK_MENU_SHELL (menubar), menuitemmain_help);

#pragma GCC diagnostic pop

	gtk_widget_show_all (menubar);
	g_object_set (menubar, "hexpand", TRUE, NULL);
	gtk_grid_attach (GTK_GRID (maingridmenubar), menubar, 0, 0, 8, 1);

	ButtonTop (&mainbutton1, 140, 0, (GCallback) Pass, "pass");
	ButtonTop (&mainbutton2, 250, 1, (GCallback) CallReStart, "restart");
	ButtonTop (&mainbutton3, 30, 2, (GCallback) Skin, "skin");
	ButtonTop (&mainbutton4, 30, 3, (GCallback) Options, "options");
	ButtonTop (&mainbutton5, 30, 4, (GCallback) Undo, "undo");
	ButtonTop (&mainbutton6, 30, 5, (GCallback) CallHint, "hint");
	ButtonTop (&mainbutton7, 30, 6, (GCallback) ReSize, "resize");
	ButtonTop (&mainbutton8, 30, 7, (GCallback) CallQuit, "quit");

	/*** Statusbar. ***/
	if ((iPSize == 0) || (iPSize >= 30))
	{
		/*** color ***/
		mainstatbarcolor = gtk_statusbar_new();
		gtk_style_context_add_class (gtk_widget_get_style_context
			(GTK_WIDGET (mainstatbarcolor)), "cssstatusbarl");
		g_object_set (mainstatbarcolor, "margin", 2, NULL);
		g_object_set (mainstatbarcolor, "halign", GTK_ALIGN_CENTER, NULL);
		gtk_grid_attach (GTK_GRID (maingridstatusbars), mainstatbarcolor,
			0, 0, 1, 1);
		gtk_widget_show (mainstatbarcolor);

		/*** to move ***/
		mainstatbartomove = gtk_statusbar_new();
		gtk_style_context_add_class (gtk_widget_get_style_context
			(GTK_WIDGET (mainstatbartomove)), "cssstatusbarl");
		g_object_set (mainstatbartomove, "margin", 2, NULL);
		gtk_grid_attach (GTK_GRID (maingridstatusbars), mainstatbartomove,
			0, 1, 1, 1);
		gtk_widget_show (mainstatbartomove);

		/*** black ***/
		mainstatbarblack = gtk_statusbar_new();
		gtk_style_context_add_class (gtk_widget_get_style_context
			(GTK_WIDGET (mainstatbarblack)), "cssstatusbarr");
		g_object_set (mainstatbarblack, "hexpand", TRUE, NULL);
		g_object_set (mainstatbarblack, "margin", 2, NULL);
		gtk_grid_attach (GTK_GRID (maingridstatusbars), mainstatbarblack,
			1, 0, 1, 1);
		gtk_widget_show (mainstatbarblack);

		/*** white ***/
		mainstatbarwhite = gtk_statusbar_new();
		gtk_style_context_add_class (gtk_widget_get_style_context
			(GTK_WIDGET (mainstatbarwhite)), "cssstatusbarr");
		g_object_set (mainstatbarwhite, "hexpand", TRUE, NULL);
		g_object_set (mainstatbarwhite, "margin", 2, NULL);
		g_object_set (mainstatbarwhite, "margin-top", 0, NULL);
		gtk_grid_attach (GTK_GRID (maingridstatusbars), mainstatbarwhite,
			1, 1, 1, 1);
		gtk_widget_show (mainstatbarwhite);

		StatusBar();
	}

	/*** Apply the iPSize window size. ***/
	switch (iPSize)
	{
		case 0: /*** fullscreen ***/
			gtk_window_set_resizable (GTK_WINDOW (mainwindow), TRUE);
			break;
		case 24:
			/*** NOT scalable ***/
			gtk_window_set_resizable (GTK_WINDOW (mainwindow), FALSE);
			gtk_widget_set_size_request (mainbox4, (19 * 24), (19 * 24));
			break;
		case 15:
			/*** NOT scalable ***/
			gtk_window_set_resizable (GTK_WINDOW (mainwindow), FALSE);
			gtk_widget_set_size_request (mainbox4, (19 * 15), (19 * 15));
			break;
		default:
			gtk_window_set_resizable (GTK_WINDOW (mainwindow), TRUE);
			GtkRequisition minimum, natural;
			int iMenuBarH, iStatusBarH;
			gtk_widget_get_preferred_size (maingridmenubar, &minimum, &natural);
			iMenuBarH = natural.height;
			gtk_widget_get_preferred_size (maingridstatusbars, &minimum, &natural);
			iStatusBarH = natural.height;
			gtk_window_set_default_size (GTK_WINDOW (mainwindow),
				(19 * iPSize), (19 * iPSize) + iMenuBarH + iStatusBarH);
			break;
	}

	/*** Center window. ***/
	gtk_window_set_position (GTK_WINDOW (mainwindow), GTK_WIN_POS_CENTER);
}
/*****************************************************************************/
