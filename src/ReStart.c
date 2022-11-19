/* gtkgo v0.0.12 (ReStart.c) (November 2022)
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

#include "ReStart.h"

/*****************************************************************************/
void DestroySplashText (gpointer data)
/*****************************************************************************/
{
	int iSplashIn;

	iSplashIn = GPOINTER_TO_INT (data);

	if ((iSplash == iSplashIn) && (splashwindow != NULL))
	{
		gtk_widget_destroy (splashwindow);
		splashwindow = NULL;
	}
}
/*****************************************************************************/
void SplashText (int iSeconds, int iWidth, int iHeight, char *sText)
/*****************************************************************************/
{
	GtkWidget *splashlabel;

	DestroySplashText (GINT_TO_POINTER (iSplash));

	/*** window ***/
	splashwindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request (splashwindow, iWidth, iHeight);
	gtk_window_set_transient_for (GTK_WINDOW (splashwindow),
		GTK_WINDOW (mainwindow));
	gtk_window_set_decorated (GTK_WINDOW (splashwindow), FALSE);
	gtk_window_set_position (GTK_WINDOW (splashwindow),
		GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_resizable (GTK_WINDOW (splashwindow), FALSE);
	gtk_widget_realize (splashwindow);

	/*** label ***/
	splashlabel = gtk_label_new (sText);
	gtk_label_set_justify (GTK_LABEL (splashlabel), GTK_JUSTIFY_CENTER);
	g_object_set (splashlabel, "margin", 10, NULL);
	gtk_container_add (GTK_CONTAINER (splashwindow), splashlabel);
	gtk_widget_show (splashlabel);

	gtk_widget_show (splashwindow);
	iSplash++;
	g_timeout_add_seconds (iSeconds, (GSourceFunc) DestroySplashText,
		GINT_TO_POINTER (iSplash));
}
/*****************************************************************************/
void CallReStart (GtkWidget *widget, gpointer data)
/*****************************************************************************/
{
	/* GtkWidget *widget receives either GtkMenuItem *menuitem
	 * or GtkButton *button.
	 */

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	ReStart (1);
}
/*****************************************************************************/
void ReStart (int iReCheck)
/*****************************************************************************/
{
	/* iReCheck:
	 * 1 = A full restart.
	 * 2 = Just redraw, after a resize or skin change.
	 */

	int iPointLoop;
	char sMessage[MAX_MESSAGE + 2];

	if (iFileDialogOpen != 0) { return; }
	if ((iIsComputerB == 1) && (iIsComputerW == 1)) { return; }
	if (iWindowOpen != 0) { return; }
	if (iConnected == 1)
	{
		if (iReCheck == 1)
		{
			Message ("To manually restart, disconnect first.", 3, 0);
			return;
		}
	}

	if (iReCheck == 1)
	{
		if (iMovesMade > 0)
		{
			iQuitRestartType = 2;
			AskSave();
		} else {
			ReallyReStart();
		}
	} else {
		if (iOptions == 0) { Play ("click.ogg", 0); }

		for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
		{
			PixmapOnPoint (iPointLoop);
		}
		if (iTooltips == 0)
		{
			iTooltips = 1;
			Tooltips (NULL, NULL, NULL);
		}
		if (iPSize == 0)
			{ gtk_window_fullscreen (GTK_WINDOW (mainwindow)); }
		gtk_widget_show (mainwindow);
	}

	if ((iPSize != 0) && (iPSize != 30))
	{
		snprintf (sMessage, MAX_MESSAGE, "Point size: %i", iPSize);
		SplashText (2, 200, 50, sMessage);
	}
}
/*****************************************************************************/
