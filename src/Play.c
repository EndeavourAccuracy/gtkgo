/* gtkgo v0.0.12 (Play.c) (November 2022)
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

#include "Play.h"

/*****************************************************************************/
gboolean BusCallback (GstBus *busc, GstMessage *message, gpointer data)
/*****************************************************************************/
{
	GstElement *play;

	if (busc != NULL) { } /*** To prevent (set but) unused warnings. ***/

	play = GST_ELEMENT (data);
	switch (GST_MESSAGE_TYPE (message))
	{
		case GST_MESSAGE_EOS:
			gst_element_seek (play,
				1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,
				GST_SEEK_TYPE_SET, 0,
				GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE);
				break;
		default: break; /*** To prevent warnings. ***/
	}

	return (TRUE);
}
/*****************************************************************************/
void PadAdded (GstElement *element, GstPad *pad, gpointer data)
/*****************************************************************************/
{
	GstPad *sinkpad;

	if (element != NULL) { } /*** To prevent (set but) unused warnings. ***/

	GstElement *pdecoder = (GstElement *)data;
	sinkpad = gst_element_get_static_pad (pdecoder, "sink");
	gst_pad_link (pad, sinkpad);
	gst_object_unref (sinkpad);
}
/*****************************************************************************/
void Play (char *sFile, int iLoop)
/*****************************************************************************/
{
	/* iLoop:
	 * 0 = No loop.
	 * 1 = Loop.
	 * 2 = Stop playing.
	 */

	if (iLoop != 2)
	{
		if (iSound == 1)
		{
			/*** Stop playing. ***/
			if (iSoundPlaying == 1)
			{
				gst_element_set_state (pipeline, GST_STATE_NULL);
				iSoundPlaying = 0;
			}

			/*** Set the audio source. ***/
			snprintf (sPFToPlay, 250, "%sogg/%s", PKGDATADIR, sFile);
			g_object_set (G_OBJECT (source), "location", sPFToPlay, NULL);

			/*** Loop or not. ***/
			bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
			if (iLoop == 1)
				{ gst_bus_add_watch (bus, BusCallback, pipeline); }
					else { gst_bus_remove_watch (bus); }
			gst_object_unref (bus);

			if (iFirstPlay == 1)
			{
				gst_bin_add_many (GST_BIN (pipeline),
					source, demuxer, decoder, conv, sink, NULL);
				gst_element_link (source, demuxer);
				gst_element_link_many (decoder, conv, sink, NULL);
				g_signal_connect (demuxer, "pad-added", G_CALLBACK (PadAdded),
					decoder);
				iFirstPlay = 0;
			}

			gst_element_set_state (pipeline, GST_STATE_PLAYING);
			iSoundPlaying = 1;
		}
	} else {
		if (iSoundPlaying == 1)
		{
			gst_element_set_state (pipeline, GST_STATE_NULL);
			iSoundPlaying = 0;
		}
	}
}
/*****************************************************************************/
