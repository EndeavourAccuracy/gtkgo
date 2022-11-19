/* gtkgo v0.0.12 (main.c) (November 2022)
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

#include "main.h"

/*****************************************************************************/
int main (int argc, char *argv[])
/*****************************************************************************/
{
	int iArg;
	GtkCssProvider *provider;
	GdkDisplay *display;
	const gchar *cssdata;

	iDebug = 0;

	/*** Process command-line options. ***/
	if (argc > 1)
	{
		for (iArg = 1; iArg <= argc - 1; iArg++)
		{
			/*** help ***/
			if ((strcmp (argv[iArg], "-h") == 0) ||
				(strcmp (argv[iArg], "-?") == 0) ||
				(strcmp (argv[iArg], "--help") == 0))
			{
				ShowUsage();
			}
			/*** version ***/
			else if ((strcmp (argv[iArg], "--version") == 0) ||
				(strcmp (argv[iArg], "-v") == 0))
			{
				printf ("%s %s\n", GAME_NAME, GAME_VERSION);
				exit (EXIT_NORMAL);
			}
			/*** debug ***/
			else if (((strncmp (argv[iArg], "--debug=", 8) == 0) &&
				(strlen (argv[iArg]) > 8)) ||
				((strncmp (argv[iArg], "-d=", 3) == 0) &&
				(strlen (argv[iArg]) > 3)))
			{
				iDebug = argv[iArg][strlen (argv[iArg]) - 1] - 48;
				if ((iDebug < 1) || (iDebug > 2)) { iDebug = 1; }
				printf ("[ INFO ] Debug level set to: %i\n", iDebug);
			}
			else { ShowUsage(); }
		}
	}

	if ((getenv ("DISPLAY")) == 0)
	{
		printf ("[FAILED] Start the X Window System first!\n");
		exit (EXIT_ERROR);
	}

	gtk_disable_setlocale(); /*** For now. ***/
	gtk_init (&argc, &argv);

	/*** GStreamer ***/
	gst_init (&argc, &argv);
	pipeline = gst_pipeline_new ("audio-player");
	source = gst_element_factory_make ("filesrc", "file-source");
	demuxer = gst_element_factory_make ("oggdemux", "ogg-demuxer");
	decoder = gst_element_factory_make ("vorbisdec", "vorbis-decoder");
	conv = gst_element_factory_make ("audioconvert", "converter");
	sink = gst_element_factory_make ("autoaudiosink", "audio-output");
	if (!pipeline || !source || !demuxer || !decoder || !conv || !sink)
	{
		printf ("[FAILED] Could not initialize GStreamer!\n");
		exit (EXIT_ERROR);
	}
	/*** GStreamer ***/

	/*** In debug mode, show the versions of GTK+ and GStreamer. ***/
	if (iDebug >= 1)
	{
		gst_version (&gstmajor, &gstminor, &gstmicro, &gstnano);
		printf ("[ INFO ] Compiled with GStreamer %u.%u.%u,"
			" linked with GStreamer %u.%u.%u.\n",
			GST_VERSION_MAJOR, GST_VERSION_MINOR, GST_VERSION_MICRO,
			gstmajor, gstminor, gstmicro);
		printf ("[ INFO ] Compiled with GTK+ %u.%u.%u,"
			" linked with GTK+ %u.%u.%u.\n",
			GTK_MAJOR_VERSION, GTK_MINOR_VERSION, GTK_MICRO_VERSION,
			gtk_major_version, gtk_minor_version, gtk_micro_version);
	}

	/*** CSS ***/
	provider = gtk_css_provider_new();
	display = gdk_display_get_default();
	screen = gdk_display_get_default_screen (display);
	gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER
		(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	/*** This is used to get rid of, for example, unwanted padding. ***/
	cssdata = ".mainbutton { margin:0px; padding:0px; }\n"
		".cssstatusbarl { font:Arial 9; }\n"
		".cssstatusbarr { border-style:solid; border-width:1px; font:Arial 9; }\n"
		".invite { font:Arial 14; }\n"
		".bgwhite { background-color:#fff; }\n"
		".frame { margin:0px; padding:0px; }\n";
	gtk_css_provider_load_from_data (GTK_CSS_PROVIDER (provider),
		cssdata, -1, NULL);
	g_object_unref (provider);
	/*** CSS ***/

	srand ((unsigned)time(&tmTime));

	/*** Set defaults. ***/
	iSoundPlaying = 0;
	iOptionsXDone = 1;
	iTooltipsDone = 1;
	iLatestDone = 1;
	iSoundDone = 1;
	iHandicapDone = 1;
	iWindowOpen = 0;
	iConnected = 0;
	iAllowUndo = 0;
	iSendHint = 0;
	iIsComputerW = 1;
	iIsComputerB = 0;
	iTooltips = 0;
	iPSize = 30;
	iHandicap = 0;
	iLatest = 0;
	iSound = 0;
	iBusyMakingMove = 0;
	iSelectDead = 0;
	iFirstPlay = 1;
	snprintf (sPlayerNameB, MAX_PLAYER_NAME, "%s", "unknown");
	snprintf (sPlayerNameW, MAX_PLAYER_NAME, "%s", "default2");
	iSplash = 0;

	snprintf (sConfigFile, 100, "%s/.%s", getenv ("HOME"), GAME_NAME);
	iConfigFD = open (sConfigFile, O_RDONLY, 0600);
	iConfigLine = 0;
	if (iConfigFD == -1)
	{
		snprintf (sCurrentSkin, MAX_SKIN_NAME, "%s", "default");
		iOptionsX = 0;
		iTimeLimit = 30;
	} else {
		iConfigEnd = 0;
		snprintf (sConfigLine, 100, "%s", "");
		do
		{
			do
			{
				iConfigBytesRead = read (iConfigFD, sConfigRead, 1);
				if ((sConfigRead[0] != '\n') && (sConfigRead[0] != '/'))
				{
					snprintf (sConfigLineTemp, 100, "%s%c", sConfigLine, sConfigRead[0]);
					snprintf (sConfigLine, 100, "%s", sConfigLineTemp);
				}
			} while ((iConfigBytesRead != 0) && (sConfigRead[0] != '\n'));
			iConfigLine++;
			switch (iConfigLine)
			{
				case 3:
					snprintf (sCurrentSkin, MAX_SKIN_NAME, "%s", sConfigLine); break;
				case 4:
					iOptionsX = atoi (sConfigLine); break;
				case 5:
					iTimeLimit = atoi (sConfigLine); iConfigEnd = 1; break;
			}
			snprintf (sConfigLine, 100, "%s", "");
		} while ((iConfigBytesRead != 0) && (iConfigEnd == 0));
		close (iConfigFD);
		if (iConfigEnd == 0)
		{
			snprintf (sSysExec, 250, "rm -f %s", sConfigFile);
			system (sSysExec);
			printf ("Please restart %s.\n", GAME_NAME);
			exit (EXIT_ERROR);
		}
	}

	MainWindow();
	ReStart (1);

	/*** Welcome message. ***/
	if (iConfigLine == 0)
	{
		Message ("Welcome to gtkgo!\n\nEven though gtkgo is as stable as "
			"possible, it is by NO means perfect.\nIf you want to know more "
			"about gtkgo, please select 'Help...' from the 'Help'-menu.\nDon't "
			"expect too much, this is just version " GAME_VERSION "...", 3, 1);
	}

	gtk_main();

	return 0;
}
/*****************************************************************************/
void ShowUsage (void)
/*****************************************************************************/
{
	printf ("%s v%s (%s)\n%s\n\n",
		GAME_NAME, GAME_VERSION, GAME_MONTHYEAR, GAME_COPY);
	printf ("Usage:\n");
	printf ("  %s [OPTIONS]\n\nOptions:\n", GAME_NAME);
	printf ("  -h, -?,    --help           display this help and exit\n");
	printf ("  -v,        --version        output version information and"
		" exit\n");
	printf ("  -d=DEBUG   --debug=DEBUG    show debug info on the console\n");
	printf ("\n");
	printf ("Debug:\n");
	printf ("  1, 2\n");
	printf ("\n");

	exit (EXIT_NORMAL);
}
/*****************************************************************************/
void CheckAccess (char *sPathFile)
/*****************************************************************************/
{
	if (access (sPathFile, R_OK) == -1)
	{
		printf ("[FAILED] Could not open \"%s\": %s\n",
			sPathFile, strerror (errno));
		exit (EXIT_ERROR);
	}
}
/*****************************************************************************/
void substr (char *sString, int iStart, int iLength, char *sOutput)
/*****************************************************************************/
{
	memcpy (sOutput, &sString[iStart], iLength);
	sOutput[iLength] = '\0';
}
/*****************************************************************************/
int strpos (char *sHaystack, char *sNeedle, int iOffset)
/*****************************************************************************/
{
	char sHaystackTemp[1000];
	char *sTemp;

	substr (sHaystack, iOffset, strlen (sHaystack) - iOffset, sHaystackTemp);
	sTemp = strstr (sHaystackTemp, sNeedle);
	if (sTemp == NULL) { return (-1); }
		else { return ((sTemp - sHaystackTemp) + iOffset); }
}
/*****************************************************************************/
