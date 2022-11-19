/* gtkgo v0.0.12 (DestroyTheComputer.c) (November 2022)
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

#include "DestroyTheComputer.h"

/*****************************************************************************/
gboolean DestroyTheComputer (GtkWidget *widget, GdkEvent *event)
/*****************************************************************************/
{
	/*** Destroys the computer loading window. ***/

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (event != NULL) { } /*** To prevent (set but) unused warnings. ***/

	iFileDialogOpen = 0;
	gtk_widget_destroy (computerdialogload);

	return (TRUE);
}
/*****************************************************************************/
