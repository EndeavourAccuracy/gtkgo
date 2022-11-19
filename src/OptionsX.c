/* gtkgo v0.0.12 (OptionsX.c) (November 2022)
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

#include "OptionsX.h"

/*****************************************************************************/
void ChangeImageX (GtkWidget **button, GtkWidget **image, char *sImageP)
/*****************************************************************************/
{
	char sX[MAX_X + 2];
	char sImage[MAX_IMAGE + 2];

	gtk_container_remove (GTK_CONTAINER (*button), GTK_WIDGET (*image));
	switch (iOptionsX)
	{
		case 0: snprintf (sX, MAX_X, "%s", ""); break;
		case 1: snprintf (sX, MAX_X, "%s", "x"); break;
	}
	snprintf (sImage, MAX_IMAGE, PKGDATADIR"png/options%s/%s.png", sX, sImageP);
	CheckAccess (sImage);
	*image = gtk_image_new_from_file (sImage);
	gtk_container_add (GTK_CONTAINER (*button), *image);
	gtk_widget_show (*image);
}
/*****************************************************************************/
gboolean OptionsX (GtkWidget *widget, GdkEvent *event, gpointer data)
/*****************************************************************************/
{
	char sImageP[MAX_IMAGE + 2];

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (event != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	if (iOptionsXDone == 1)
	{
		iOptionsXDone = 0;

		if (iOptionsX == 0)
		{
			iOptionsX = 1;
		} else {
			iOptionsX = 0;
		}

		ChangeImageX (&optionsbutton1, &optionsim1, "1");
		ChangeImageX (&optionsbutton2, &optionsim2, "2");
		ChangeImageX (&optionsbutton3, &optionsim3, "3");
		ChangeImageX (&optionsbutton4, &optionsim4, "4");
		ChangeImageX (&optionsbutton5, &optionsim5, "5");
		ChangeImageX (&optionsbutton5b, &optionsim5b, "5b");
		ChangeImageX (&optionsbutton6, &optionsim6, "6");
		if (iTooltips == 1)
			{ ChangeImageX (&optionsbutton6b, &optionsim6b, "6on"); }
				else { ChangeImageX (&optionsbutton6b, &optionsim6b, "6off"); }
		ChangeImageX (&optionsbutton7, &optionsim7, "7");
		if (iLatest == 1)
			{ ChangeImageX (&optionsbutton7b, &optionsim7b, "7on"); }
				else { ChangeImageX (&optionsbutton7b, &optionsim7b, "7off"); }
		ChangeImageX (&optionsbutton8, &optionsim8, "8");
		if (iSound == 1)
			{ ChangeImageX (&optionsbutton8b, &optionsim8b, "8on"); }
				else { ChangeImageX (&optionsbutton8b, &optionsim8b, "8off"); }
		ChangeImageX (&optionsbutton9, &optionsim9, "9");
		snprintf (sImageP, MAX_IMAGE, "9%i", iHandicap);
		ChangeImageX (&optionsbutton9b, &optionsim9b, sImageP);

		while (gtk_events_pending())
		{
			gtk_main_iteration();
		}

		iOptionsXDone = 1;
	}

	return (TRUE);
}
/*****************************************************************************/
