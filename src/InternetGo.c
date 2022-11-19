/* gtkgo v0.0.12 (InternetGo.c) (November 2022)
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

#include "InternetGo.h"

/*****************************************************************************/
void ScrollToEnd (GtkWidget *widget, GdkRectangle *allocation, gpointer data)
/*****************************************************************************/
{
	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (allocation != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	internetadj = gtk_scrolled_window_get_vadjustment
		(GTK_SCROLLED_WINDOW (internetscrolled));
	gtk_adjustment_set_value (internetadj,
		gtk_adjustment_get_upper (internetadj));
}
/*****************************************************************************/
void CloseSocket (void)
/*****************************************************************************/
{
	/* Using void, but this function is called as:
	 * - gboolean user_function (GtkWidget *widget, GdkEvent *event,
	 * gpointer data)
	 * - void user_function (GtkButton *button, gpointer data)
	 */

	iConnected = 0;
	/*** ReceiveData() will now remove the internetwindow and close iSockFD. ***/
}
/*****************************************************************************/
void ToggleWrap (GtkToggleButton *togglebutton, gpointer data)
/*****************************************************************************/
{
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton)) == TRUE)
	{
		/*** lowered ***/
		gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (internettext),
			GTK_WRAP_WORD_CHAR);
	} else {
		/*** raised ***/
		gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (internettext), GTK_WRAP_NONE);
	}
}
/*****************************************************************************/
struct in_addr *atoaddr (char *address)
/*****************************************************************************/
{
	struct hostent *host;
	static struct in_addr saddr;

	saddr.s_addr = inet_addr (address);
	if (saddr.s_addr != INADDR_NONE)
	{
		return (&saddr);
	}
	host = gethostbyname (address);
	if (host != NULL)
	{
		return ((struct in_addr *) *host->h_addr_list);
	}
	saddr.s_addr = inet_addr ("666.666.666.666");
	return (&saddr);
}
/*****************************************************************************/
void InternetGo (GtkButton *button, gpointer data)
/*****************************************************************************/
{
	GtkWidget *internetbox;
	GtkWidget *internetgridtext;
	GtkWidget *internetgridbottom;
	GtkWidget *internetcheckwrap;
	GtkWidget *internetsep;
	GtkWidget *internetbutton;
	/***/
	struct sockaddr_in sockaddrin;
	struct in_addr *inaddr;
	const char *sHostInput;
	int iPortInput;
	int iError;
	char sError[100];
	char sHost[MAX_HOST + 2];
	char sServerType[100];

	if (button != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	if (iFileDialogOpen != 0) { return; }

	if (iConnected == 0)
	{
		/*** Obtain the host, port and type. ***/
		sHostInput = gtk_entry_get_text (GTK_ENTRY (connectentryhost));
		snprintf (sHost, MAX_HOST, "%s", sHostInput);
		inaddr = atoaddr (sHost);
		iPortInput = atoi (gtk_entry_get_text (GTK_ENTRY (connectentryport)));
		snprintf (sServerType, 100, "%s",
			gtk_combo_box_get_active_id (GTK_COMBO_BOX (connectcombotype)));

		gtk_widget_destroy (connectwindow);
		iWindowOpen = 0;

		bzero ((char *)&sockaddrin, sizeof (sockaddrin));
		sockaddrin.sin_family = AF_INET;
		sockaddrin.sin_addr.s_addr = inet_addr (inet_ntoa (*inaddr));
		sockaddrin.sin_port = htons (iPortInput);

		if ((iSockFD = socket (AF_INET, SOCK_STREAM, 0)) < 0)
		{
			Message ("Unable to open socket.", 3, 0);
		}
		iError = connect (iSockFD, (struct sockaddr *)&sockaddrin, sizeof
			(sockaddrin));
		if (iError < 0)
		{
			snprintf (sError, 100, "Unable to connect to host (%s).", strerror
				(errno));
			Message (sError, 3, 0);
		} else {
			fcntl (iSockFD, F_SETFL, O_NONBLOCK);
			iIsComputerB = 0;
			snprintf (sPlayerNameB, MAX_PLAYER_NAME, "%s", "unknown");
			iIsComputerW = 0;
			snprintf (sPlayerNameW, MAX_PLAYER_NAME, "%s", "unknown");
			StatusBar();

			if (iOptions == 0) { Play ("open.ogg", 0); }

			/*** window ***/
			internetwindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
			gtk_window_set_transient_for (GTK_WINDOW (internetwindow),
				GTK_WINDOW (optionswindow));
			gtk_window_set_title (GTK_WINDOW (internetwindow), "Internet window");
			g_signal_connect (internetwindow, "delete_event",
				G_CALLBACK (CloseSocket), NULL);
			gtk_window_set_resizable (GTK_WINDOW (internetwindow), TRUE);
			gtk_container_set_border_width (GTK_CONTAINER (internetwindow), 0);
			gtk_widget_realize (internetwindow);

			/*** box ***/
			internetbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
			gtk_container_set_border_width (GTK_CONTAINER (internetbox), 0);
			gtk_container_add (GTK_CONTAINER (internetwindow), internetbox);
			gtk_widget_show (internetbox);

			/*** grid text ***/
			internetgridtext = gtk_grid_new();
			gtk_widget_show (internetgridtext);
			gtk_box_pack_start (GTK_BOX (internetbox), internetgridtext,
				TRUE, TRUE, 0);

			/*** grid bottom ***/
			internetgridbottom = gtk_grid_new();
			gtk_widget_show (internetgridbottom);
			gtk_box_pack_start (GTK_BOX (internetbox), internetgridbottom,
				FALSE, FALSE, 0);

			/*** scrolled ***/
			internetscrolled = gtk_scrolled_window_new (NULL, NULL);
			gtk_widget_set_size_request (internetscrolled, 550, 460);
			gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (internetscrolled),
				GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
			g_signal_connect (internetscrolled, "size-allocate",
				G_CALLBACK (ScrollToEnd), NULL);
			gtk_grid_attach (GTK_GRID (internetgridtext), internetscrolled,
				0, 0, 1, 1);
			g_object_set (internetscrolled, "hexpand", TRUE, NULL);
			g_object_set (internetscrolled, "vexpand", TRUE, NULL);
			g_object_set (internetscrolled, "margin", 10, NULL);
			gtk_widget_show (internetscrolled);

			/*** text ***/
			internettext = gtk_text_view_new();
			gtk_text_view_set_editable (GTK_TEXT_VIEW (internettext), FALSE);
			gtk_text_view_set_monospace (GTK_TEXT_VIEW (internettext), TRUE);
			gtk_container_add (GTK_CONTAINER (internetscrolled), internettext);
			gtk_widget_show (internettext);

			/*** text buffer, tag ***/
			internettextbuffer = gtk_text_buffer_new (NULL);
			gtk_text_buffer_create_tag (internettextbuffer, "red_fg",
				"foreground", "red", NULL);
			gtk_text_view_set_buffer (GTK_TEXT_VIEW (internettext),
				internettextbuffer);

			/*** check wrap ***/
			internetcheckwrap = gtk_check_button_new_with_label ("wrap");
			gtk_grid_attach (GTK_GRID (internetgridbottom), internetcheckwrap,
				0, 0, 1, 1);
			g_signal_connect (internetcheckwrap, "toggled",
				G_CALLBACK (ToggleWrap), NULL);
			g_object_set (internetcheckwrap, "margin", 10, NULL);
			gtk_widget_set_margin_top (internetcheckwrap, 0);
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (internetcheckwrap),
				FALSE);
			gtk_widget_show (internetcheckwrap);

			/*** entry ***/
			internetentry = gtk_entry_new();
			gtk_entry_set_max_length (GTK_ENTRY (internetentry), 50);
			g_signal_connect (internetentry, "activate",
				G_CALLBACK (CallSendData), NULL);
			gtk_grid_attach (GTK_GRID (internetgridbottom), internetentry,
				1, 0, 1, 1);
			g_object_set (internetentry, "hexpand", TRUE, NULL);
			gtk_widget_set_margin_end (internetentry, 10);
			gtk_widget_set_margin_bottom (internetentry, 10);
			gtk_widget_grab_focus (internetentry);
			gtk_widget_show (internetentry);

			/*** separator ***/
			internetsep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
			gtk_grid_attach (GTK_GRID (internetgridbottom), internetsep,
				0, 1, 2, 1);
			g_object_set (internetsep, "hexpand", TRUE, NULL);
			gtk_widget_show (internetsep);

			/*** button ***/
			internetbutton = gtk_button_new_with_mnemonic ("_Disconnect");
			g_signal_connect (internetbutton, "clicked",
				G_CALLBACK (CloseSocket), NULL);
			gtk_widget_set_can_default (internetbutton, TRUE);
			gtk_window_set_default (GTK_WINDOW (internetwindow), internetbutton);
			gtk_grid_attach (GTK_GRID (internetgridbottom), internetbutton,
				0, 2, 2, 1);
			g_object_set (internetbutton, "hexpand", TRUE, NULL);
			g_object_set (internetbutton, "margin", 2, NULL);
			gtk_widget_show (internetbutton);

			gtk_widget_show (internetwindow);

			iConnected = 1;

			ReceiveData (sServerType);
		}
	}
}
/*****************************************************************************/
