/* gtkgo v0.0.12 (DestroyYesNo.c) (November 2022)
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

#include "DestroyYesNo.h"

/*****************************************************************************/
gboolean DestroyYesNo (GtkWidget *widget, GdkEvent *event, gpointer data)
/*****************************************************************************/
{
	/* data:
	 * 0 = Close yesnowindow and (if necessary) make computer move.
	 * 1 = Show save SGF dialog.
	 * 2 = Close yesnowindow and restart.
	 * 3 = Close yesnowindow and quit.
	 */

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (event != NULL) { } /*** To prevent (set but) unused warnings. ***/

	if (iFileDialogOpen == 0)
	{
		if (GPOINTER_TO_INT (data) == 0)
		{
			gtk_widget_destroy (yesnowindow);
			iWindowOpen = 0;

			/* If a computer is selected and the user destroys AskSave,
			 * make a computer move.
			 */
			if ((Modulo (iMovesMade, 2) == 0) && (iIsComputerB == 1))
			{
				Computer ('b');
				JudgeBoard ('w');
			}
			if ((Modulo (iMovesMade, 2) != 0) && (iIsComputerW == 1))
			{
				Computer ('w');
				JudgeBoard ('b');
			}
		}

		if (GPOINTER_TO_INT (data) == 1)
		{
			SaveDialog();
		}

		if (GPOINTER_TO_INT (data) == 2)
		{
			gtk_widget_destroy (yesnowindow);
			iWindowOpen = 0;
			iSaveMatch = 0;
			ReallyReStart();
		}

		if (GPOINTER_TO_INT (data) == 3)
		{
			gtk_widget_destroy (yesnowindow);
			iWindowOpen = 0;
			iSaveMatch = 0;
			ReallyQuit();
		}
	}

	return (TRUE);
}
/*****************************************************************************/
