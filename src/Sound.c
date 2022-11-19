/* gtkgo v0.0.12 (Sound.c) (November 2022)
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

#include "Sound.h"

/*****************************************************************************/
gboolean Sound (GtkWidget *widget, GdkEvent *event, gpointer data)
/*****************************************************************************/
{
	char sPFImage[MAX_IMAGE + 2];

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (event != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	if (iFileDialogOpen != 0) { return (FALSE); }
	if (iWindowOpen != 0) { return (FALSE); }

	if (iSoundDone == 1)
	{
		iSoundDone = 0;

		gtk_container_remove (GTK_CONTAINER (optionsbutton8b),
			GTK_WIDGET (optionsim8b));
		if (iSound == 1)
		{
			if (iOptionsX == 1)
			{
				snprintf (sPFImage, MAX_IMAGE, "%s",
					PKGDATADIR"png/optionsx/8off.png");
			} else {
				snprintf (sPFImage, MAX_IMAGE, "%s",
					PKGDATADIR"png/options/8off.png");
			}
			iSound = 0;
			Play ("", 2);
		} else {
			if (iOptionsX == 1)
			{
				snprintf (sPFImage, MAX_IMAGE, "%s",
					PKGDATADIR"png/optionsx/8on.png");
			} else {
				snprintf (sPFImage, MAX_IMAGE, "%s",
					PKGDATADIR"png/options/8on.png");
			}
			iSound = 1;
			Play ("options.ogg", 1);
		}
		CheckAccess (sPFImage);
		optionsim8b = gtk_image_new_from_file (sPFImage);
		gtk_container_add (GTK_CONTAINER (optionsbutton8b), optionsim8b);
		gtk_widget_show (optionsim8b);

		while (gtk_events_pending())
		{
			gtk_main_iteration();
		}

		iSoundDone = 1;
	}

	return (TRUE);
}
/*****************************************************************************/
