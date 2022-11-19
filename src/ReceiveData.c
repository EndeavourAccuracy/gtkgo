/* gtkgo v0.0.12 (ReceiveData.c) (November 2022)
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

#include "ReceiveData.h"

/*****************************************************************************/
int SpaceArray (char *sString)
/*****************************************************************************/
{
	/* Splits sString into arSpaceArray. It uses space (' ') as the
	 * delimiter. The function returns the number of elements in arSpaceArray.
	 */

	char sTemp[MAX_SPACEAR + 2];
	int iStore;
	int iTemp;

	/*** Clear. ***/
	iStore = 0;
	for (iTemp = 0; iTemp < MAX_SPACEAR; iTemp++)
		{ snprintf (arSpaceArray[iTemp], MAX_SPACEAR, "%s", ""); }

	for (iTemp = 0; iTemp < (int)strlen (sString); iTemp++)
	{
		if (sString[iTemp] == ' ')
		{
			iStore++;
			snprintf (arSpaceArray[iStore], MAX_SPACEAR, "%s", "");
		} else {
			snprintf (sTemp, MAX_SPACEAR, "%s", arSpaceArray[iStore]);
			snprintf (arSpaceArray[iStore], MAX_SPACEAR, "%s%c",
				sTemp, sString[iTemp]);
		}
	}

	return (iStore + 1);
}
/*****************************************************************************/
int PlaceToPoint (char sPlace[3])
/*****************************************************************************/
{
	char sPlaceX[5], sPlaceY[5];
	int iPointX, iPointY;
	int iPoint;

	/*** Split sPlace into sPlaceX and sPlaceY. ***/
	snprintf (sPlaceX, 5, "%c", sPlace[0]);
	switch (strlen (sPlace))
	{
		case 2:
			snprintf (sPlaceY, 5, "%c", sPlace[1]);
			break;
		case 3:
			snprintf (sPlaceY, 5, "%c%c", sPlace[1], sPlace[2]);
			break;
	}

	/*** Calculate iPoint. ***/
	iPointX = sPlaceX[0] - 64;
	if (sPlaceX[0] > 73) { iPointX-=1; } /*** Skip I. ***/
	iPointY = (19 - atoi (sPlaceY)) * 19;
	iPoint = iPointX + iPointY;

	if ((iPoint < 1) || (iPoint > POINTS))
	{
		Message ("Incorrect server.", 3, 0);
	}

	return (iPoint);
}
/*****************************************************************************/
gboolean CallDestroyInvite (GtkWidget *widget, GdkEvent *event, gpointer data)
/*****************************************************************************/
{
	if (widget != NULL) { } /*** To prevent (set but) unused warnings. ***/
	if (event != NULL) { } /*** To prevent (set but) unused warnings. ***/

	DestroyInvite (NULL, data);

	return (TRUE);
}
/*****************************************************************************/
void DestroyInvite (GtkButton *button, gpointer data)
/*****************************************************************************/
{
	struct InviteResponse *stInviteResponse;
	char sSendData[MAX_SENDDATA + 2];

	if (button != NULL) { } /*** To prevent (set but) unused warnings. ***/

	stInviteResponse = data;

	switch (stInviteResponse->iResponse)
	{
		case 0: /*** User closed the invite window. ***/
			break;
		case 1: /*** Accept ***/
			snprintf (sSendData, MAX_SENDDATA, "match %s %s %i %i %i",
				stInviteResponse->stInvite.sFrom,
				stInviteResponse->stInvite.sColor,
				stInviteResponse->stInvite.iSize,
				stInviteResponse->stInvite.iMinutes,
				stInviteResponse->stInvite.iByoYomi);
			SendData (1, sSendData);
			break;
		case 2: /*** Decline ***/
			snprintf (sSendData, MAX_SENDDATA, "decline %s",
				stInviteResponse->stInvite.sFrom);
			SendData (1, sSendData);
			break;
	}

	g_free (stInviteResponse);
	gtk_widget_destroy (invitewindow);
	iWindowOpen = 0;
}
/*****************************************************************************/
void InviteAcceptDecline (struct Invite stInvite)
/*****************************************************************************/
{
	GtkWidget *inviteboxmain;
	GtkWidget *inviteboxtop;
	GtkWidget *inviteboxbottom;
	GtkWidget *invitegridtop;
	GtkWidget *invitegridbottom;
	GtkWidget *inviteimage;
	GtkWidget *invitelabel;
	GtkWidget *invitesep;
	GtkWidget *invitebuttonaccept;
	GtkWidget *invitebuttondecline;
	/***/
	char sInviteLabel[300];
	char sPFImage[MAX_IMAGE + 2];

	InviteResponse *stInviteResponse0 = g_new (InviteResponse, 1);
	stInviteResponse0->stInvite = stInvite;
	InviteResponse *stInviteResponse1 = g_new (InviteResponse, 1);
	stInviteResponse1->stInvite = stInvite;
	InviteResponse *stInviteResponse2 = g_new (InviteResponse, 1);
	stInviteResponse2->stInvite = stInvite;

	/*** window ***/
	stInviteResponse0->iResponse = 0;
	invitewindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (invitewindow), "invitation");
	gtk_window_set_mnemonics_visible (GTK_WINDOW (invitewindow), TRUE);
	g_signal_connect (invitewindow, "delete_event",
		G_CALLBACK (CallDestroyInvite), stInviteResponse0);
	gtk_window_set_resizable (GTK_WINDOW (invitewindow), FALSE);
	gtk_container_set_border_width (GTK_CONTAINER (invitewindow), 0);
	gtk_widget_realize (invitewindow);

	/*** box main ***/
	inviteboxmain = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width (GTK_CONTAINER (inviteboxmain), 0);
	gtk_container_add (GTK_CONTAINER (invitewindow), inviteboxmain);
	gtk_widget_show (inviteboxmain);

	/*** box top ***/
	inviteboxtop = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_set_border_width (GTK_CONTAINER (inviteboxtop), 0);
	gtk_container_add (GTK_CONTAINER (inviteboxmain), inviteboxtop);
	gtk_widget_show (inviteboxtop);

	/*** bot bottom ***/
	inviteboxbottom = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width (GTK_CONTAINER (inviteboxbottom), 0);
	gtk_container_add (GTK_CONTAINER (inviteboxmain), inviteboxbottom);
	gtk_widget_show (inviteboxbottom);

	/*** grid top ***/
	invitegridtop = gtk_grid_new();
	gtk_box_pack_start (GTK_BOX (inviteboxtop), invitegridtop, TRUE, TRUE, 0);
	gtk_widget_show (invitegridtop);

	/*** grid bottom ***/
	invitegridbottom = gtk_grid_new();
	gtk_box_pack_start (GTK_BOX (inviteboxbottom), invitegridbottom,
		TRUE, TRUE, 0);
	gtk_widget_show (invitegridbottom);

	/*** image ***/
	snprintf (sPFImage, MAX_IMAGE, "%s", PKGDATADIR"png/invite.png");
	CheckAccess (sPFImage);
	inviteimage = gtk_image_new_from_file (sPFImage);
	gtk_grid_attach (GTK_GRID (invitegridtop), inviteimage, 0, 0, 1, 1);
	g_object_set (inviteimage, "margin", 20, NULL);
	gtk_widget_show (inviteimage);

	/*** label ***/
	snprintf (sInviteLabel, 300,
		"From: %s\n"
		"Your color: %s\n"
		"Size: %ix%i\n"
		"Minutes: %i\n"
		"Byo-yomi: %i",
		stInvite.sFrom, stInvite.sColor, stInvite.iSize, stInvite.iSize,
		stInvite.iMinutes, stInvite.iByoYomi);
	invitelabel = gtk_label_new (sInviteLabel);
	gtk_style_context_add_class (gtk_widget_get_style_context
		(GTK_WIDGET (invitelabel)), "invite");
	gtk_label_set_justify (GTK_LABEL (invitelabel), GTK_JUSTIFY_CENTER);
	gtk_grid_attach (GTK_GRID (invitegridtop), invitelabel, 1, 0, 1, 1);
	g_object_set (invitelabel, "margin", 20, NULL);
	gtk_widget_set_margin_start (invitelabel, 0);
	gtk_widget_show (invitelabel);

	/*** separator ***/
	invitesep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach (GTK_GRID (invitegridbottom), invitesep, 0, 0, 2, 1);
	gtk_widget_show (invitesep);

	/*** accept ***/
	stInviteResponse1->iResponse = 1;
	invitebuttonaccept = gtk_button_new_with_mnemonic ("_Accept");
	g_signal_connect (invitebuttonaccept, "clicked",
		G_CALLBACK (DestroyInvite), stInviteResponse1);
	gtk_widget_set_can_default (invitebuttonaccept, TRUE);
	gtk_window_set_default (GTK_WINDOW (invitewindow), invitebuttonaccept);
	gtk_grid_attach (GTK_GRID (invitegridbottom), invitebuttonaccept,
		0, 1, 1, 1);
	g_object_set (invitebuttonaccept, "hexpand", TRUE, NULL);
	g_object_set (invitebuttonaccept, "margin", 2, NULL);
	gtk_widget_show (invitebuttonaccept);

	/*** decline ***/
	stInviteResponse2->iResponse = 2;
	invitebuttondecline = gtk_button_new_with_mnemonic ("_Decline");
	g_signal_connect (invitebuttondecline, "clicked",
		G_CALLBACK (DestroyInvite), stInviteResponse2);
	gtk_grid_attach (GTK_GRID (invitegridbottom), invitebuttondecline,
		1, 1, 1, 1);
	g_object_set (invitebuttondecline, "hexpand", TRUE, NULL);
	g_object_set (invitebuttondecline, "margin", 2, NULL);
	gtk_widget_show (invitebuttondecline);

	iWindowOpen = 1;
	gtk_widget_show (invitewindow);
	if (iOptions == 0) { Play ("open.ogg", 0); }
}
/*****************************************************************************/
void ReceiveData (char *sServerType)
/*****************************************************************************/
{
	GtkTextIter citer1, citer2;
	/***/
	char sReceived[MAX_NET + 2];
	char sTemp[MAX_NET + 2];
	int iFirstPrompt;
	char sInternetOpponent[MAX_PLAYER_NAME + 2];
	char sHandicap[3];
	char sShow[2];
	unsigned char sBuffer[1];
	int iLastMovePos;
	char sLastMove[1000];
	int iReadyToGo;
	int iKnowOpponent;
	int iHaveMove;
	int iAElements;
	int iAElement; /*** To loop through iAElements elements of arSpaceArray. ***/
	Invite *stInvite = g_new (Invite, 1);
	int iFromOpponent;
	char sFrom[100 + 2];

	/*** Set defaults. ***/
	iFirstPrompt = 1;
	iReadyToGo = 0;
	iKnowOpponent = 0;
	snprintf (sInternetOpponent, MAX_PLAYER_NAME, "%s", "");
	snprintf (sHandicap, 3, "%s", "");

	do {
		snprintf (sReceived, MAX_NET, "%s", "");
		do {
			iBytesRec = read (iSockFD, sBuffer, 1);
			if (iBytesRec > 0)
			{
				if (sBuffer[0] != '\r')
				{
					snprintf (sTemp, MAX_NET, "%s", sReceived);
					snprintf (sReceived, MAX_NET, "%s%c", sTemp, sBuffer[0]);
					/* 245-255 = invalid
					 * 1 = start of heading
					 * 7 = bell
					 */
					if ((sBuffer[0] < 245) && (sBuffer[0] != 1) && (sBuffer[0] != 7))
					{
						/*** Show character. ***/
						snprintf (sShow, 2, "%c", sBuffer[0]);
						gtk_text_buffer_get_end_iter (internettextbuffer, &internetiter);
						gtk_text_buffer_insert (internettextbuffer, &internetiter,
							g_locale_to_utf8 (sShow, -1, NULL, NULL, NULL), -1);

						/*** Last three characters a (non-client-mode) prompt? ***/
						gtk_text_buffer_get_iter_at_offset (internettextbuffer, &citer1,
							gtk_text_buffer_get_char_count (GTK_TEXT_BUFFER
							(internettextbuffer)) - 3);
						gtk_text_buffer_get_end_iter (internettextbuffer, &citer2);
						if ((strcmp (gtk_text_buffer_get_text (GTK_TEXT_BUFFER
							(internettextbuffer), &citer1, &citer2, FALSE), "#> ") == 0))
						{
							if (strcmp (sServerType, "NNGS") == 0)
							{
								/*** Send our client's number. ***/
								if (iFirstPrompt == 1)
								{
									SendData (1, "client " NNGS_CLIENT_GTKGO);
									iFirstPrompt = 0;
								}
							}
							if (strcmp (sServerType, "IGS") == 0)
							{
								/*** Always turn on client-mode. ***/
								SendData (1, "toggle client");
							}
						}
					}

					/*** bell ***/
					if (sBuffer[0] == 7)
					{
						if (iOptions == 0) { Play ("bell.ogg", 0); }
					}
				}
			}
			if (iBytesRec == 0)
			{
				Message ("Connection closed by foreign host.", 3, 0);
				iConnected = 0;
			}
			if (iBytesRec < 0)
			{
/***
				struct timeval timeout;
				do {
					FD_ZERO (&set);
					FD_SET (iSockFD, &set);
					timeout.tv_sec = 0;
					timeout.tv_usec = 0;
					iRet = select (iSockFD + 1, &set, NULL, NULL, &timeout);
***/
					if (gtk_events_pending())
					{
						gtk_main_iteration();
					}
/***
				} while (iRet == 0);
***/
			}
		} while ((sBuffer[0] != '\r') && (iConnected != 0));

		if (iConnected != 0)
		{
			iAElements = SpaceArray (sReceived);

			/*** In debug mode, show all elements of the line we received. ***/
			if (iDebug >= 2)
			{
				printf ("-----\n");
				for (iAElement = 0; iAElement < iAElements; iAElement++)
				{
					printf ("|%s|\n", arSpaceArray[iAElement]);
				}
				printf ("-----\n");
			}

			/*** Received invitation. ***/
			/*** NNGS ***/
			if ((strcmp (sServerType, "NNGS") == 0) &&
				(strcmp (arSpaceArray[0], "\nUse") == 0) &&
				(strcmp (arSpaceArray[11], "respond.") == 0))
			{
				snprintf (stInvite->sFrom, MAX_PLAYER_NAME, "%s", arSpaceArray[2]);
				snprintf (stInvite->sColor, 10, "%s", arSpaceArray[3]);
				stInvite->iSize = atoi (arSpaceArray[4]);
				stInvite->iMinutes = atoi (arSpaceArray[5]);
				stInvite->iByoYomi = atoi (arSpaceArray[6]);
				InviteAcceptDecline (*stInvite);
			}
			/*** IGS ***/
			if ((strcmp (sServerType, "IGS") == 0) &&
				(strcmp (arSpaceArray[0], "\n9") == 0) &&
				(strcmp (arSpaceArray[12], "respond.") == 0))
			{
				snprintf (stInvite->sFrom, MAX_PLAYER_NAME, "%s", arSpaceArray[3]);
				snprintf (stInvite->sColor, 10, "%s", arSpaceArray[4]);
				stInvite->iSize = atoi (arSpaceArray[5]);
				stInvite->iMinutes = atoi (arSpaceArray[6]);
				stInvite->iByoYomi = atoi (arSpaceArray[7]);
				InviteAcceptDecline (*stInvite);
			}

			/*** Opponent undid your move. ***/
			/*** NNGS and IGS ***/
			if ((strcmp (arSpaceArray[1], sInternetOpponent) == 0) &&
				(strcmp (arSpaceArray[2], "undid") == 0))
			{
				Message ("Opponent undid your move.", 3, 1);
				iAllowUndo = 1;
				Undo (NULL, NULL);
				iAllowUndo = 0;
				StatusBar();
			}

			/*** Extract player names by color. ***/
			/*** NNGS ***/
			if ((strcmp (sServerType, "NNGS") == 0) &&
				(strcmp (arSpaceArray[0], "\nGame") == 0) &&
				(strcmp (arSpaceArray[7], "vs") == 0))
			{
				snprintf (sPlayerNameW, MAX_PLAYER_NAME, "%s", arSpaceArray[3]);
				snprintf (sPlayerNameB, MAX_PLAYER_NAME, "%s", arSpaceArray[8]);
				iReadyToGo++;
			}
			/*** IGS ***/
			if ((strcmp (sServerType, "IGS") == 0) &&
				(strcmp (arSpaceArray[1], "Game") == 0) &&
				(strcmp (arSpaceArray[8], "vs") == 0))
			{
				snprintf (sPlayerNameW, MAX_PLAYER_NAME, "%s", arSpaceArray[4]);
				snprintf (sPlayerNameB, MAX_PLAYER_NAME, "%s", arSpaceArray[9]);
				iReadyToGo++;
			}

			/*** Illegal move. ***/
			/*** NNGS ***/
			if ((strcmp (sServerType, "NNGS") == 0) &&
				(strcmp (arSpaceArray[0], "\nIllegal") == 0) &&
				(strcmp (arSpaceArray[1], "Move!") == 0))
			{
				Message ("Illegal move.", 3, 0);
			}
			/*** IGS ***/
			if ((strcmp (sServerType, "IGS") == 0) &&
				(strcmp (arSpaceArray[1], "Illegal") == 0) &&
				(strcmp (arSpaceArray[2], "move.") == 0))
			{
				Message ("Illegal move.", 3, 0);
			}

			/*** Opponent resigned. ***/
			/*** NNGS and IGS ***/
			if ((strcmp (arSpaceArray[1], sInternetOpponent) == 0) &&
				(strcmp (arSpaceArray[3], "resigned") == 0))
			{
				Message ("Opponent resigned.", 3, 1);
				snprintf (sInternetOpponent, MAX_PLAYER_NAME, "%s", "");
				snprintf (sPlayerNameB, MAX_PLAYER_NAME, "%s", "unknown");
				snprintf (sPlayerNameW, MAX_PLAYER_NAME, "%s", "unknown");
				iInternetWeAreBlack = 0;
				iHandicap = 0;
				iReadyToGo = 0;
				iKnowOpponent = 0;
				StatusBar();
			}

			/*** Extract opponent's name. ***/
			/*** NNGS and IGS ***/
			if ((strcmp (arSpaceArray[1], "Creating") == 0) &&
				(strcmp (arSpaceArray[2], "match") == 0) &&
				(iKnowOpponent == 0))
			{
				snprintf (sInternetOpponent, MAX_PLAYER_NAME, "%s", arSpaceArray[5]);
				/*** Remove period. ***/
				sInternetOpponent[strlen (sInternetOpponent) - 1] = '\0';
				iReadyToGo++;
				iKnowOpponent = 1;
			}
			if ((strcmp (arSpaceArray[1], "Match") == 0) &&
				(strcmp (arSpaceArray[7], "accepted.") == 0) &&
				(iKnowOpponent == 0))
			{
				snprintf (sInternetOpponent, MAX_PLAYER_NAME, "%s", arSpaceArray[4]);
				iReadyToGo++;
				iKnowOpponent = 1;
			}

			/*** Get the last move, as sLastMove. ***/
			iHaveMove = 0;
			/*** NNGS ***/
			if ((strcmp (sServerType, "NNGS") == 0) &&
				(strstr (sReceived, "Last Move: ") != NULL))
			{
				iLastMovePos = strpos (sReceived, "Last Move: ", 0) +
					strlen ("Last Move: ");
				substr (sReceived, iLastMovePos, strlen (sReceived) -
					iLastMovePos, sLastMove);
				iHaveMove = 1;
			}
			/*** IGS ***/
			if ((strcmp (sServerType, "IGS") == 0) &&
				(strcmp (arSpaceArray[0], "\n15") == 0) &&
				(sReceived[10] == ':'))
			{
				iLastMovePos = strpos (sReceived, ": ", 0) + strlen (": ");
				substr (sReceived, iLastMovePos, strlen (sReceived) -
					iLastMovePos, sLastMove);
				iHaveMove = 1;
			}

			if (iHaveMove == 1)
			{
				if (((Modulo (iMovesMade, 2) == 0) && (iInternetWeAreBlack == 1)) ||
					((Modulo (iMovesMade, 2) != 0) && (iInternetWeAreBlack == 0)))
					{ iFromOpponent = 0; } else { iFromOpponent = 1; }

				if (iDebug >= 1)
				{
					switch (iFromOpponent)
					{
						case 0: snprintf (sFrom, 100, "%s", "(your)"); break;
						case 1: snprintf (sFrom, 100, "%s", "(opponent's)"); break;
					}
					printf ("[ INFO ] Received %s move \"%s\".\n", sFrom, sLastMove);
				}

				if (strstr (sLastMove, "Handicap ") != NULL)
				{
					/*** set handicap ***/
					substr (sLastMove, 8, 2, sHandicap);
					iHandicap = atoi (sHandicap);
					iMovesMade = 0;
					DoHandicap();
				} else if (strcmp (sLastMove, "Pass") == 0) {
					/*** pass ***/
					switch (iFromOpponent)
					{
						case 0: Message ("You passed.", 3, 1); break;
						case 1: Message ("Opponent passed.", 3, 1); break;
					}
					HistoryPassed[iMovesMade + 1] = 1;
					if (Modulo (iMovesMade, 2) == 0)
						{ JudgeBoard ('w'); }
							else { JudgeBoard ('b'); }
				} else {
					/*** make move ***/

					if ((strcmp (sServerType, "IGS") == 0) &&
						(strstr (sLastMove, " ") != NULL))
					{
						/* For now we just remove information about captured stones.
						 * The program already checks for these itself.
						 */
						sLastMove[strpos (sLastMove, " ", 0)] = '\0';
					}

					if (Modulo (iMovesMade, 2) == 0)
					{
						iMoveMade = 0;
						ChangePoint (PlaceToPoint (sLastMove), 'b');
						if (iMoveMade == 1)
						{
							JudgeBoard ('w');
						}
					} else {
						iMoveMade = 0;
						ChangePoint (PlaceToPoint (sLastMove), 'w');
						if (iMoveMade == 1)
						{
							JudgeBoard ('b');
						}
					}
				}
			}

			/*** Set up the board. ***/
			if (iReadyToGo == 2)
			{
				iReadyToGo = 3; /*** Must be before ReallyReStart(). ***/
				iHandicap = 0;
				iSaveMatch = 0;
				ReallyReStart();
				if (strcmp (sPlayerNameW, sInternetOpponent) == 0)
				{
					iInternetWeAreBlack = 1; /*** Must be after ReallyReStart(). ***/
				}
			}
		}
	} while (iConnected == 1);

	close (iSockFD);
	gtk_widget_destroy (internetwindow);
}
/*****************************************************************************/
