/* gtkgo v0.0.12 (Skin.c) (November 2022)
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

#include "Skin.h"

/*****************************************************************************/
int StrCmp (const void* vString1, const void* vString2)
/*****************************************************************************/
{
	/* This function is used because strcmp() wants "const char *",
	 * while qsort() sends to "const void *".
	 */

	const char* cA;
	const char* cB;

	cA = (const char*)vString1;
	cB = (const char*)vString2;

	return (strcmp (cA, cB));
}
/*****************************************************************************/
void Skin (GtkWidget *widget, gpointer data)
/*****************************************************************************/
{
	/* GtkWidget *widget receives either GtkMenuItem *menuitem
	 * or GtkButton *button.
	 */

	GtkWidget *skinbuttons[MAX_SKINS];
	GtkWidget *skingrid;
	GtkWidget *skinim;
	/***/
	DIR *dirSkinDir;
	struct dirent *dDirent;
	int iSkins;
	int iSkinLoop;
	char sPFSkin[200];

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	if ((iIsComputerB == 1) && (iIsComputerW == 1))
	{
		if (iOptions == 0) { Play ("click.ogg", 0); }
		return;
	}
	if (iWindowOpen != 0)
	{
		if (iOptions == 0) { Play ("click.ogg", 0); }
		return;
	}

	if (iFileDialogOpen == 0)
	{
		if ((dirSkinDir = opendir (PKGDATADIR"skins")) == NULL)
		{
			Message ("Error loading skins.", 1, 0);
		} else {
			/*** window ***/
			skinswindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
			gtk_window_set_transient_for (GTK_WINDOW (skinswindow),
				GTK_WINDOW (mainwindow));
			gtk_window_set_title (GTK_WINDOW (skinswindow), "load skin");
			g_signal_connect (skinswindow, "delete_event",
				G_CALLBACK (DestroySkins), NULL);
			gtk_window_set_resizable (GTK_WINDOW (skinswindow), FALSE);
			gtk_container_set_border_width (GTK_CONTAINER (skinswindow), 10);
			gtk_widget_realize (skinswindow);

			/*** grid ***/
			skingrid = gtk_grid_new();
			gtk_container_add (GTK_CONTAINER (skinswindow), skingrid);
			gtk_widget_show (skingrid);

			/*** Load skin names. ***/
			iSkins = 0;
			while ((dDirent = readdir (dirSkinDir)) != NULL)
			{
				if ((strcmp (dDirent->d_name, ".") != 0) &&
					(strcmp (dDirent->d_name, "..") != 0))
				{
					snprintf (arSkinNames[iSkins], 100, "%s", dDirent->d_name);
					iSkins++;
				}
			}
			closedir (dirSkinDir);

			/*** Sort skin names. ***/
			qsort (arSkinNames, iSkins, 100, StrCmp);

			/*** Show skins list. ***/
			for (iSkinLoop = 0; iSkinLoop < iSkins; iSkinLoop++)
			{
				/*** image (black stone) ***/
				snprintf (sPFSkin, 200, PKGDATADIR"skins/%s/mmb.png",
					arSkinNames[iSkinLoop]);
				CheckAccess (sPFSkin);
				skinim = gtk_image_new_from_file (sPFSkin);
				gtk_grid_attach (GTK_GRID (skingrid), skinim,
					0, iSkinLoop, 1, 1);
				gtk_widget_show (skinim);

				/*** button ***/
				skinbuttons[iSkinLoop] = gtk_button_new_with_label
					(arSkinNames[iSkinLoop]);
				gtk_widget_set_size_request (GTK_WIDGET (skinbuttons[iSkinLoop]),
					200, 30);
				gtk_grid_attach (GTK_GRID (skingrid), skinbuttons[iSkinLoop],
					1, iSkinLoop, 1, 1);
				g_object_set (skinbuttons[iSkinLoop], "hexpand", TRUE, NULL);
				g_object_set (skinbuttons[iSkinLoop], "vexpand", TRUE, NULL);
				gtk_widget_set_margin_start (skinbuttons[iSkinLoop], 4);
				gtk_widget_set_margin_end (skinbuttons[iSkinLoop], 4);
				gtk_widget_set_margin_top (skinbuttons[iSkinLoop], 2);
				gtk_widget_set_margin_bottom (skinbuttons[iSkinLoop], 2);
				g_signal_connect (skinbuttons[iSkinLoop], "clicked",
					G_CALLBACK (ChangeSkin), (gpointer)arSkinNames[iSkinLoop]);
				gtk_widget_show (skinbuttons[iSkinLoop]);

				/*** image (white stone) ***/
				snprintf (sPFSkin, 200, PKGDATADIR"skins/%s/mmw.png",
					arSkinNames[iSkinLoop]);
				CheckAccess (sPFSkin);
				skinim = gtk_image_new_from_file (sPFSkin);
				gtk_grid_attach (GTK_GRID (skingrid), skinim,
					2, iSkinLoop, 1, 1);
				gtk_widget_show (skinim);
			}

			gtk_widget_show (skinswindow);
			iFileDialogOpen = 1;

			if (iOptions == 0) { Play ("open.ogg", 0); }
		}
	}
}
/*****************************************************************************/
