/* gtkgo v0.0.12 (ReallyReStart.c) (November 2022)
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

#include "ReallyReStart.h"

/*****************************************************************************/
gfloat lprogress (gfloat pvalue)
/*****************************************************************************/
{
	/*** 0.00277 is (1/POINTS), but floats are not infinitely accurate. ***/
	pvalue+=0.00277;

	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (loadingbar), pvalue);

	while (gtk_events_pending())
	{
		gtk_main_iteration();
	}

	return (pvalue);
}
/*****************************************************************************/
void ReallyReStart (void)
/*****************************************************************************/
{
	GtkWidget *loadingwindow;
	GtkWidget *loadingim;
	GtkWidget *loadingbox;
	GtkWidget *loadinggrid;
	/***/
	int iPointLoop;
	int iPlace;
	char sPFImage[MAX_IMAGE + 2];
	gfloat pvalue;

	if ((iMovesMade > 0) && (iSaveMatch == 1))
	{
		JudgeBoard ('w');
		SaveSGF();
	}

	if (iStoreMes == 1)
	{
		Message (sSaveMes, 2, 1);
	}

	/*** Set defaults. ***/
	iCapturedW = 0;
	iCapturedB = 0;
	iFileDialogOpen = 0;
	iPassLosing = 0;
	iMoveAlt = 0;
	iSaveMatch = 1;
	iQuitAfterMessage = 0;
	iStoreMes = 0;
	iInternetWeAreBlack = 0;
	iMovesMade = 0;
	iLastMoveB = 1000;
	iLastMoveW = 1000;
	pvalue = 0;
	StatusBar();

	/*** Populate Board[]. ***/
	for (iPlace = 1; iPlace <= POINTS; iPlace++)
	{
		snprintf (Board[iPlace], MAX_I, "%s", "mme");
	}
	snprintf (Board[1], MAX_I, "%s", "lte");
	for (iPlace = 2; iPlace <= 18; iPlace++)
	{
		snprintf (Board[iPlace], MAX_I, "%s", "mte");
	}
	snprintf (Board[19], MAX_I, "%s", "rte");
	snprintf (Board[20], MAX_I, "%s", "lme");
	snprintf (Board[38], MAX_I, "%s", "rme");
	snprintf (Board[39], MAX_I, "%s", "lme");
	snprintf (Board[57], MAX_I, "%s", "rme");
	snprintf (Board[58], MAX_I, "%s", "lme");
	snprintf (Board[61], MAX_I, "%s", "mms");
	snprintf (Board[67], MAX_I, "%s", "mms");
	snprintf (Board[73], MAX_I, "%s", "mms");
	snprintf (Board[76], MAX_I, "%s", "rme");
	snprintf (Board[77], MAX_I, "%s", "lme");
	snprintf (Board[95], MAX_I, "%s", "rme");
	snprintf (Board[96], MAX_I, "%s", "lme");
	snprintf (Board[114], MAX_I, "%s", "rme");
	snprintf (Board[115], MAX_I, "%s", "lme");
	snprintf (Board[133], MAX_I, "%s", "rme");
	snprintf (Board[134], MAX_I, "%s", "lme");
	snprintf (Board[152], MAX_I, "%s", "rme");
	snprintf (Board[153], MAX_I, "%s", "lme");
	snprintf (Board[171], MAX_I, "%s", "rme");
	snprintf (Board[172], MAX_I, "%s", "lme");
	snprintf (Board[175], MAX_I, "%s", "mms");
	snprintf (Board[181], MAX_I, "%s", "mms");
	snprintf (Board[187], MAX_I, "%s", "mms");
	snprintf (Board[190], MAX_I, "%s", "rme");
	snprintf (Board[191], MAX_I, "%s", "lme");
	snprintf (Board[209], MAX_I, "%s", "rme");
	snprintf (Board[210], MAX_I, "%s", "lme");
	snprintf (Board[228], MAX_I, "%s", "rme");
	snprintf (Board[229], MAX_I, "%s", "lme");
	snprintf (Board[247], MAX_I, "%s", "rme");
	snprintf (Board[248], MAX_I, "%s", "lme");
	snprintf (Board[266], MAX_I, "%s", "rme");
	snprintf (Board[267], MAX_I, "%s", "lme");
	snprintf (Board[285], MAX_I, "%s", "rme");
	snprintf (Board[286], MAX_I, "%s", "lme");
	snprintf (Board[289], MAX_I, "%s", "mms");
	snprintf (Board[295], MAX_I, "%s", "mms");
	snprintf (Board[301], MAX_I, "%s", "mms");
	snprintf (Board[304], MAX_I, "%s", "rme");
	snprintf (Board[305], MAX_I, "%s", "lme");
	snprintf (Board[323], MAX_I, "%s", "rme");
	snprintf (Board[324], MAX_I, "%s", "lme");
	snprintf (Board[342], MAX_I, "%s", "rme");
	snprintf (Board[343], MAX_I, "%s", "lue");
	for (iPlace = 344; iPlace <= 360; iPlace++)
	{
		snprintf (Board[iPlace], MAX_I, "%s", "mue");
	}
	snprintf (Board[361], MAX_I, "%s", "rue");

	DoHandicap();

	for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
	{
		snprintf (HistoryMoves[iMovesMade][iPointLoop], MAX_I, "%s",
			Board[iPointLoop]);
	}

	gtk_widget_hide (mainwindow);

	/*** window ***/
	loadingwindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position (GTK_WINDOW (loadingwindow), GTK_WIN_POS_CENTER);
	gtk_window_set_title (GTK_WINDOW (loadingwindow), "loading...");
	g_signal_connect (loadingwindow, "delete_event",
		G_CALLBACK (Quit), NULL);
	gtk_window_set_resizable (GTK_WINDOW (loadingwindow), FALSE);
	gtk_container_set_border_width (GTK_CONTAINER (loadingwindow), 0);
	gtk_widget_realize (loadingwindow);

	/*** box ***/
	loadingbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width (GTK_CONTAINER (loadingbox), 0);
	gtk_container_add (GTK_CONTAINER (loadingwindow), loadingbox);
	gtk_widget_show (loadingbox);

	/*** grid ***/
	loadinggrid = gtk_grid_new();
	gtk_box_pack_start (GTK_BOX (loadingbox), loadinggrid, TRUE, TRUE, 0);
	gtk_widget_show (loadinggrid);

	/*** image ***/
	snprintf (sPFImage, MAX_IMAGE, "%s", PKGDATADIR"png/loadings.png");
	CheckAccess (sPFImage);
	loadingim = gtk_image_new_from_file (sPFImage);
	gtk_grid_attach (GTK_GRID (loadinggrid), loadingim, 0, 0, 1, 1);
	gtk_widget_show (loadingim);

	/*** progress ***/
	loadingbar = gtk_progress_bar_new();
	gtk_grid_attach (GTK_GRID (loadinggrid), loadingbar, 0, 1, 1, 1);
	gtk_widget_show (loadingbar);

	gtk_widget_show (loadingwindow);

	while (gtk_events_pending())
	{
		gtk_main_iteration();
	}

	/*** Adding the 19*19 board images. ***/
	for (iPointLoop = 1; iPointLoop <= POINTS; iPointLoop++)
	{
		/*** Add the image. ***/
		PixmapOnPoint (iPointLoop);

		/*** Update the progress bar. ***/
		pvalue = lprogress (pvalue);

		/*** Briefly show loading window, even on fast computers. ***/
		g_usleep (1000);
	}

	gtk_widget_destroy (loadingwindow);

	if (iTooltips == 0)
	{
		iTooltips = 1;
		Tooltips (NULL, NULL, NULL);
	}

	if (iPSize == 0)
		{ gtk_window_fullscreen (GTK_WINDOW (mainwindow)); }

	gtk_widget_show (mainwindow);
}
/*****************************************************************************/
