/* gtkgo v0.0.12 (SetTimeLimit.c) (November 2022)
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

#include "SetTimeLimit.h"

/*****************************************************************************/
void SetTimeLimit (GtkWidget *widget, gpointer data)
/*****************************************************************************/
{
	/* GtkWidget *widget receives either GtkEntry *entry
	 * or GtkButton *button.
	 */

	char sTimeLimit[7];
	char sTimeMinutes[7];
	char sTimeMinutesTemp[7];
	char sTimeHours[7];
	int iTimeLoop;
	int iTimeLoop2;
	int iWarn;

	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	snprintf (sTimeHours, 7, "%s", "");
	snprintf (sTimeMinutes, 7, "%s", "");
	snprintf (sTimeLimit, 7, "%s", gtk_entry_get_text (GTK_ENTRY (timeentry)));

	for (iTimeLoop = 0; iTimeLoop < (int)strlen (sTimeLimit); iTimeLoop++)
	{
		if (sTimeLimit[iTimeLoop] != ':')
		{
			snprintf (sTimeMinutesTemp, 7, "%s%c", sTimeMinutes,
				sTimeLimit[iTimeLoop]);
			snprintf (sTimeMinutes, 7, "%s", sTimeMinutesTemp);
		} else {
			snprintf (sTimeHours, 7, "%s", sTimeMinutes);
			snprintf (sTimeMinutes, 7, "%s", "");
			for (iTimeLoop2 = iTimeLoop; iTimeLoop2 < (int)strlen (sTimeLimit);
				iTimeLoop2++)
			{
				if (sTimeLimit[iTimeLoop2] != ':')
				{
					snprintf (sTimeMinutesTemp, 7, "%s%c", sTimeMinutes,
						sTimeLimit[iTimeLoop2]);
					snprintf (sTimeMinutes, 7, "%s", sTimeMinutesTemp);
				}
			}
			iTimeLoop = 10;
		}
	}

	iTimeLimitSetH = atoi (sTimeHours);
	iTimeLimitSetM = atoi (sTimeMinutes);
	iTimeLimit = (60 * iTimeLimitSetH) + iTimeLimitSetM;

	gtk_widget_destroy (timewindow);
	iWindowOpen = 0;

	/*** Deal with incorrect user input. ***/
	if (iTimeLimit == 0)
	{
		iWarn = 1;
		iTimeLimit = 30;
	} else { iWarn = 0; }

	StatusBar();

	if (iWarn == 1) { Message ("Incorrect input.", 3, 0); }
}
/*****************************************************************************/
