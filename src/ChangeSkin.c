/* gtkgo v0.0.12 (ChangeSkin.c) (November 2022)
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

#include "ChangeSkin.h"

/*****************************************************************************/
void ChangeSkin (GtkWidget *widget, gpointer data)
/*****************************************************************************/
{
	/*** Changes the skin to the skin in data. ***/

	int iPointLoop;

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/

	snprintf (sCurrentSkin, MAX_SKIN_NAME, "%s", (char *)data);

	/*** Close the skins window. ***/
	DestroySkins (NULL, NULL);

	/*** Recreate the main window. ***/
	gtk_widget_destroy (mainwindow);
	for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
	{
		maineventboxes[iPointLoop] = NULL;
		mainim[iPointLoop] = NULL;
	}
	MainWindow();
	ReStart (2);
}
/*****************************************************************************/
