/* gtkgo v0.0.12 (SendData.c) (November 2022)
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

#include "SendData.h"

/*****************************************************************************/
void CallSendData (GtkEntry *entry, gpointer data)
/*****************************************************************************/
{
	if (entry != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (data != NULL) { } /*** To prevent (set but) unused warnings. ***/

	SendData (2, "");
}
/*****************************************************************************/
void SendData (int iType, char *sData)
/*****************************************************************************/
{
	/* iType:
	 * 1 = Use input from the sData parameter.
	 * 2 = Use user input from internetentry.
	 */

	char sSendLine[255];

	if (iType == 1)
	{
		snprintf (sSendLine, 255, "%s\n", sData);
	} else {
		snprintf (sSendLine, 255, "%s\n", gtk_entry_get_text
			(GTK_ENTRY (internetentry)));
		gtk_entry_set_text (GTK_ENTRY (internetentry), "");
	}
	iBytesSent = strlen (sSendLine);
	if (send (iSockFD, sSendLine, iBytesSent, 0) != iBytesSent)
	{
		Message ("A send error has occured.", 3, 0);
	}
	gtk_text_buffer_get_end_iter (internettextbuffer, &internetiter);
	gtk_text_buffer_insert_with_tags_by_name (internettextbuffer, &internetiter,
		g_locale_to_utf8 (sSendLine, -1, NULL, NULL, NULL), -1, "red_fg", NULL);
}
/*****************************************************************************/
