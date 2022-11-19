/* gtkgo v0.0.12 (Quit.c) (November 2022)
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

#include "Quit.h"

/*****************************************************************************/
void CallQuit (GtkWidget *widget, gpointer data)
/*****************************************************************************/
{
	/* GtkWidget *widget receives either GtkMenuItem *menuitem
	 * or GtkButton *button.
	 */

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/

	Quit (NULL, NULL, data);
}
/*****************************************************************************/
gboolean Quit (GtkWidget *widget, GdkEvent *event, gpointer data)
/*****************************************************************************/
{
	/* Quit can be triggered from four locations: by closing the loading
	 * window, by closing the main window, by selecting Quit from the Game
	 * menu, and by clicking one of the top buttons.
	 */

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (event != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	if (iFileDialogOpen != 0) { return (FALSE); }
	if (iWindowOpen != 0) { return (FALSE); }

	if (iOptions == 0) { Play ("click.ogg", 0); }

	if (iMovesMade > 1)
	{
		iQuitRestartType = 1; /*** Resign. ***/
		AskSave();
	} else {
		Play ("", 2);
		iQuitRestartType = 4;
		ReallyQuit();
	}

	return (GDK_EVENT_STOP); /*** = TRUE ***/
}
/*****************************************************************************/
