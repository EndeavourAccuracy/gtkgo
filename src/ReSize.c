/* gtkgo v0.0.12 (ReSize.c) (November 2022)
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

#include "ReSize.h"

/*****************************************************************************/
void ReSize (GtkWidget *widget, gpointer data)
/*****************************************************************************/
{
	/* GtkWidget *widget receives either GtkMenuItem *menuitem
	 * or GtkButton *button.
	 */

	int iPoint;

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	if (iFileDialogOpen != 0) { return; }
	if ((iIsComputerB == 1) && (iIsComputerW == 1)) { return; }
	if (iWindowOpen != 0) { return; }

	if (iOptions == 0) { Play ("click.ogg", 0); }

	switch (iPSize)
	{
		case 30: iPSize = 0; break;
		case 0: iPSize = 24; break;
		case 24: iPSize = 15; break;
		case 15: iPSize = 30; break;
		default: iPSize = 30; break;
	}

	gtk_widget_destroy (mainwindow);

	for (iPoint = 1; iPoint <= POINTS; iPoint++)
	{
		maineventboxes[iPoint] = NULL;
		mainim[iPoint] = NULL;
	}

	MainWindow();

	ReStart (2);
}
/*****************************************************************************/
