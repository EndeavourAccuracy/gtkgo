/* gtkgo v0.0.12 (Tooltips.c) (November 2022)
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

#include "Tooltips.h"

/*****************************************************************************/
gboolean Tooltips (GtkWidget *widget, GdkEvent *event, gpointer data)
/*****************************************************************************/
{
	int iPointLoop;
	char sPFImage[MAX_IMAGE + 2];

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (event != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	if (iFileDialogOpen != 0) { return (FALSE); }
	if (iWindowOpen != 0) { return (FALSE); }

	if (iTooltipsDone == 1)
	{
		iTooltipsDone = 0;

		for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
		{
			if (iTooltips == 1)
			{
				gtk_widget_set_has_tooltip (maineventboxes[iPointLoop], FALSE);
			} else {
				gtk_widget_set_has_tooltip (maineventboxes[iPointLoop], TRUE);
			}
		}

		if (iOptions == 1)
		{
			gtk_container_remove (GTK_CONTAINER (optionsbutton6b), optionsim6b);
			if (iTooltips == 1)
			{
				if (iOptionsX == 1)
				{
					snprintf (sPFImage, MAX_IMAGE, "%s",
						PKGDATADIR"png/optionsx/6off.png");
				} else {
					snprintf (sPFImage, MAX_IMAGE, "%s",
						PKGDATADIR"png/options/6off.png");
				}
			} else {
				if (iOptionsX == 1)
				{
					snprintf (sPFImage, MAX_IMAGE, "%s",
						PKGDATADIR"png/optionsx/6on.png");
				} else {
					snprintf (sPFImage, MAX_IMAGE, "%s",
						PKGDATADIR"png/options/6on.png");
				}
			}
			CheckAccess (sPFImage);
			optionsim6b = gtk_image_new_from_file (sPFImage);
			gtk_container_add (GTK_CONTAINER (optionsbutton6b), optionsim6b);
			gtk_widget_show (optionsim6b);

			while (gtk_events_pending())
			{
				gtk_main_iteration();
			}
		}

		if (iTooltips == 1)
		{
			gtk_widget_set_has_tooltip (GTK_WIDGET (mainbutton1), FALSE);
			gtk_widget_set_has_tooltip (GTK_WIDGET (mainbutton2), FALSE);
			gtk_widget_set_has_tooltip (GTK_WIDGET (mainbutton3), FALSE);
			gtk_widget_set_has_tooltip (GTK_WIDGET (mainbutton4), FALSE);
			gtk_widget_set_has_tooltip (GTK_WIDGET (mainbutton5), FALSE);
			gtk_widget_set_has_tooltip (GTK_WIDGET (mainbutton6), FALSE);
			gtk_widget_set_has_tooltip (GTK_WIDGET (mainbutton7), FALSE);
			gtk_widget_set_has_tooltip (GTK_WIDGET (mainbutton8), FALSE);
			iTooltips = 0;
		} else {
			gtk_widget_set_has_tooltip (GTK_WIDGET (mainbutton1), TRUE);
			gtk_widget_set_has_tooltip (GTK_WIDGET (mainbutton2), TRUE);
			gtk_widget_set_has_tooltip (GTK_WIDGET (mainbutton3), TRUE);
			gtk_widget_set_has_tooltip (GTK_WIDGET (mainbutton4), TRUE);
			gtk_widget_set_has_tooltip (GTK_WIDGET (mainbutton5), TRUE);
			gtk_widget_set_has_tooltip (GTK_WIDGET (mainbutton6), TRUE);
			gtk_widget_set_has_tooltip (GTK_WIDGET (mainbutton7), TRUE);
			gtk_widget_set_has_tooltip (GTK_WIDGET (mainbutton8), TRUE);
			iTooltips = 1;
		}

		iTooltipsDone = 1;
	}

	return (TRUE);
}
/*****************************************************************************/
