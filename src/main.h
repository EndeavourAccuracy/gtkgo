/* gtkgo v0.0.12 (main.h) (November 2022)
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

#ifndef MAIN_H
#define MAIN_H

/*========== Includes ==========*/
#include <gtk/gtk.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
#include <gst/gst.h>
#pragma GCC diagnostic pop

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
/*========== Includes ==========*/

/*========== Defines ==========*/
#define EXIT_NORMAL 0
#define EXIT_ERROR 1
#define GAME_NAME "gtkgo"
#define GAME_VERSION "0.0.12"
#define GAME_MONTHYEAR "November 2022"
#define GAME_AUTHOR "Norbert de Jonge"
#define GAME_COPY "Copyright (C) 2022 " GAME_AUTHOR
#define GAME_GOAL "The goal of the gtkgo project is to make a go game for" \
	" both Linux and Windows, that has skin support and can load computer" \
	" scripts that can be made by users, so that different go-computers can" \
	" 'attack' each other or other users."
#define GAME_WEBSITE "https://github.com/EndeavourAccuracy/gtkgo"
#define MAX_HOST 100
#define NNGS_DEFAULT_HOST "nngs.cosmic.org"
#define NNGS_DEFAULT_PORT "9696"
#define NNGS_CLIENT_GTKGO "23"
#define IGS_DEFAULT_HOST "igs.joyjoy.net"
#define IGS_DEFAULT_PORT "6969"
#define MAX_IMAGE 200
#define MAX_X 10
#define MAX_SPACEAR 100
#define MAX_NET 1000
#define MAX_I 5
#define MAX_SKINS 100
#define MAX_SKIN_NAME 100
#define POINTS 19 * 19
#define HISTORY 1000
#define MAX_COOR 20
#define MAX_MESSAGE 500
#define MAX_PLAYER_NAME 100
#define MAX_SENDDATA 255
#define MAX_TITLE 100
/*========== Defines ==========*/

int iPSize; /*** Point width and height in pixels. ***/
int iCapturedB; /*** Number of black stones removed from the board. ***/
int iCapturedW; /*** Number of white stones removed from the board. ***/
int iLastMoveW; /*** Place where white placed its last stone. ***/
int iLastMoveB; /*** Place where black placed its last stone. ***/
int iMovesMade; /*** Number of moves made. ***/
int iFileDialogOpen; /*** 1 = loading/saving a file. ***/
int iPassLosing; /*** 1 = passed, but score not higher than opponent's. ***/
int iIsComputerB; /*** Black: 0 = human, 1 = computer. ***/
int iIsComputerW; /*** White: 0 = human, 1 = computer. ***/
int iMoveMade; /*** Player made move: 0 = no, 1 = yes. ***/
int iMoveNotSide; /*** Avoid board sides: 0 = no, 1 = yes. ***/
int iMoveNotOwn; /*** Avoid own territory: 0 = no, 1 = yes. ***/
int iMoveNotOther; /*** Avoid opponent's territory: 0 = no, 1 = yes. ***/
int iMoveAlt; /*** Ignore iMoveNot* values: 0 = no, 1 = yes. ***/
int iHandicapStart; /*** Number of handicap stones at game start. ***/
int iJustRestarted; /*** A game just restarted: 0 = no, 1 = yes. ***/
int iStoreMes; /*** 0 = do not, 1 = store message; show later. ***/
int iAllowUndo; /*** 0 = not allowed, 1 = allowed. ***/
int iBusyMakingMove; /*** Moving: 0 = no, 1 = yes, disallow MakeMove(). ***/
int iSelectDead; /*** 1 = MakeMove() removes/adds dead stones. ***/
float fScoreBlack; /*** Total score of the black player. ***/
float fScoreWhite; /*** Total score of the white player. ***/
char cColorFirstPlayer; /*** Color of the player who started. ***/
char sCurrentSkin[MAX_SKIN_NAME]; /*** Name of the current skin. ***/
char Board[POINTS + 2][MAX_I]; /*** Current board values. ***/
int Checked[POINTS + 2];
int iQuitAfterMessage; /*** 1 = Quit after DestroyMessage(). ***/
int iWindowOpen; /*** 1 = A window (other than the main window) is open. ***/
GtkWidget *computerdialogload;
GtkWidget *savedialog;
GtkWidget *messagewindow;
GtkWidget *skinswindow;
GtkWidget *yesnowindow;
int iSaveMatch; /*** Save match: 0 = no, 1 = yes. ***/
char sPlayerNameB[MAX_PLAYER_NAME]; /*** Name of the black player. ***/
char sPlayerNameW[MAX_PLAYER_NAME]; /*** Name of the white player. ***/
char sSysExec[250]; /*** Used with system(). ***/
char sSaveMes[MAX_MESSAGE]; /*** Store the message to be shown. ***/
GtkWidget *helptext; /*** The text block used for Help(). ***/
int iFirstPlay;
guint gstmajor, gstminor, gstmicro, gstnano;
GdkScreen *screen;
GdkPixbuf *pixbuforig[POINTS + 2];
int iDebug;
int iRemoved;
int iSplash;

/*========== Sound ==========*/
GstElement *pipeline, *source, *demuxer, *decoder, *conv, *sink;
GstBus *bus;
/***/
char sPFToPlay[250]; /*** Path and file to play. ***/
int iSoundPlaying; /*** 1 = Audio is playing. ***/
/*========== Sound ==========*/

/*========== Internet ==========*/
GtkWidget *connectwindow;
GtkWidget *connectentryhost;
GtkWidget *connectentryport;
GtkWidget *connectcombotype;
/***/
GtkWidget *internetwindow;
GtkWidget *internetscrolled;
GtkWidget *internetentry; /*** User input. ***/
GtkAdjustment *internetadj; /*** Used to adjust the text. ***/
GtkWidget *internettext; /*** The text block. ***/
GtkTextBuffer *internettextbuffer;
GtkTextIter internetiter;
/***/
int iConnected; /*** 1 = Connected to a server. ***/
int iSockFD; /*** Socket used for sending/receiving Internet data. ***/
int iBytesRec; /*** Bytes received. ***/
int iBytesSent; /*** Bytes sent. ***/
int iInternetWeAreBlack; /*** Are we black: 0 = no, 1 = yes. ***/
int iSendHint; /*** 0 = do not, 1 = also send over the internet. ***/
char arSpaceArray[MAX_SPACEAR + 2][255 + 2];
/*========== Internet ==========*/

/*========== Time ==========*/
GtkWidget *timewindow;
GtkWidget *timeentry; /*** User input for TimeLimit(). ***/
/***/
int iTimeLimit; /*** Number of minutes for each player to play. ***/
int iTimeLimitSetM; /*** Set the time limit, minutes. ***/
int iTimeLimitSetH; /*** Set the time limit, hours. ***/
/***/
int iTimeLeftBH; /*** Hours left for the black player. ***/
int iTimeLeftBM; /*** Minutes left for the black player. ***/
int iTimeLeftBS; /*** Seconds left for the black player. ***/
int iTimeLeftBSCalc; /*** Used to calculate seconds left for black. ***/
int iTimeLeftWH; /*** Hours left for the white player. ***/
int iTimeLeftWM; /*** Minutes left for the white player. ***/
int iTimeLeftWS; /*** Seconds left for the white player. ***/
int iTimeLeftWSCalc; /*** Used to calculate seconds left for white. ***/
unsigned int iOutOfTimeAtB; /*** When black will run out of time. ***/
unsigned int iOutOfTimeAtW; /*** When white will run out of time. ***/
unsigned int iTurnStartTime; /*** When player's turn started. ***/
time_t tmTime; /*** Used for srand() and time limits. ***/
/*========== Time ==========*/

/*========== History ==========*/
char HistoryMoves[HISTORY + 2][POINTS + 2][MAX_I];
int HistoryTime[HISTORY + 2];
int HistoryCapturedW[HISTORY + 2];
int HistoryCapturedB[HISTORY + 2];
int HistoryLastRemoved[HISTORY + 2]; /*** Location last removed stone. ***/
int HistoryPassed[HISTORY + 2];
/*========== History ==========*/

/*========== Main window ==========*/
GtkWidget *mainwindow;
GtkWidget *maingridpoints;
GtkWidget *mainframe;
GtkWidget *maineventboxes[POINTS + 2];
GtkWidget *mainim[POINTS + 2];
GtkWidget *maingridmenubar;
GtkWidget *maingridstatusbars;
GtkWidget *mainstatbarcolor;
GtkWidget *mainstatbartomove;
GtkWidget *mainstatbarwhite;
GtkWidget *mainstatbarblack;
GtkWidget *mainbutton1;
GtkWidget *mainbutton2;
GtkWidget *mainbutton3;
GtkWidget *mainbutton4;
GtkWidget *mainbutton5;
GtkWidget *mainbutton6;
GtkWidget *mainbutton7;
GtkWidget *mainbutton8;
/*========== Main window ==========*/

/*========== Config file ==========*/
char sConfigRead[1]; /*** Used for reading from the config file. ***/
char sConfigLine[100]; /*** Data read from the config file. ***/
char sConfigLineTemp[100];
char sConfigFile[100]; /*** Location of the config file. ***/
int iConfigFD; /*** File descriptor for the config file. ***/
int iConfigEnd; /*** Reached the end of the config file. ***/
int iConfigLine; /*** Line counter for the config file. ***/
int iConfigBytesRead; /*** Number of bytes read from the config file. ***/
/*========== Config file ==========*/

/*========== Options ==========*/
GtkWidget *optionswindow;
GtkWidget *optionsbutton1;
GtkWidget *optionsbutton2;
GtkWidget *optionsbutton3;
GtkWidget *optionsbutton4;
GtkWidget *optionsbutton5;
GtkWidget *optionsbutton5b;
GtkWidget *optionsbutton6;
GtkWidget *optionsbutton6b;
GtkWidget *optionsbutton7;
GtkWidget *optionsbutton7b;
GtkWidget *optionsbutton8;
GtkWidget *optionsbutton8b;
GtkWidget *optionsbutton9;
GtkWidget *optionsbutton9b;
GtkWidget *optionsim1;
GtkWidget *optionsim2;
GtkWidget *optionsim3;
GtkWidget *optionsim4;
GtkWidget *optionsim5;
GtkWidget *optionsim5b;
GtkWidget *optionsim6;
GtkWidget *optionsim6b;
GtkWidget *optionsim7;
GtkWidget *optionsim7b;
GtkWidget *optionsim8;
GtkWidget *optionsim8b;
GtkWidget *optionsim9;
GtkWidget *optionsim9b;
/***/
int iOptionsX; /*** Options graphics: 0 = regular, 1 = fancy. ***/
int iOptionsXDone; /*** Done changing options: 0 = no, 1 = yes. ***/
int iTooltips; /*** Show tooltips: 0 = no, 1 = yes. ***/
int iTooltipsDone; /*** Done changing tooltips: 0 = no, 1 = yes. ***/
int iLatest; /*** Show latest stones: 0 = no, 1 = yes. ***/
int iLatestDone; /*** Done changing latest stones: 0 = no, 1 = yes. ***/
int iSound; /*** Sound enabled: 0 = no, 1 = yes. ***/
int iSoundDone; /*** Done changing sound: 0 = no, 1 = yes. ***/
int iHandicap; /*** Number of handicap stones. ***/
int iHandicapDone; /*** Done changing handicap: 0 = no, 1 = yes. ***/
int iOptions; /*** 1 = options window is open. ***/
/*========== Options ==========*/

/***
1 = Quit, with resign and time.
2 = Restart, with resign and time.
3 = Must quit.
4 = Quit.
***/
int iQuitRestartType;

typedef struct Invite {
	char sFrom[100 + 2];
	char sColor[10 + 2];
	int iSize;
	int iMinutes;
	int iByoYomi;
} Invite;

typedef struct InviteResponse {
	struct Invite stInvite;
	int iResponse;
} InviteResponse;

/*** Functions in main.c ***/
void ShowUsage (void);
void CheckAccess (char *sPathFile);
void substr (char *sString, int iStart, int iLength, char *sOutput);
int strpos (char *sHaystack, char *sNeedle, int iOffset);

void About (GtkMenuItem *menuitem, gpointer data);
void AskSave (void);
char* PointToPlace (int iType, int iPoint);
void ChangePixmap (int iPoint);
int ChangePoint (int iPoint, char cColor);
void ChangeSkin (GtkWidget *widget, gpointer data);
int CheckSides (int iPoint, char cColor, int iType);
int CallChangePoint (int iPoint, char cColor);
void Computer (char cColor);
void DeadStones (void);
gboolean DestroyTheComputer (GtkWidget *widget, GdkEvent *event);
gboolean DestroySkins (GtkWidget *widget, GdkEvent *event);
void DestroySaveDialog (void);
void DestroyMessage (void);
gboolean DestroyOptions (GtkWidget *widget, GdkEvent *event);
gboolean DestroyYesNo (GtkWidget *widget, GdkEvent *event, gpointer data);
void DoHandicap (void);
void EnableComp (GtkFileChooser *chooser, int iChangeColor);
void EndGame (void);
int FreePlace (int iPoint, char cColor, char cType);
void Handicap (gpointer data);
void DestroyHelp (void);
void ToggleWrapH (GtkToggleButton *togglebutton, gpointer data);
gboolean CallHelp (GtkWidget *widget, GdkEvent *event, gpointer data);
void Help (GtkMenuItem *menuitem, gpointer data);
void CallHint (GtkButton *button, gpointer data);
void Hint (GtkMenuItem *menuitem, gpointer data);
int WouldSurround (int iPoint, char cColor);
gboolean DestroyHuman (GtkWidget *widget, GdkEvent *event, gpointer data);
void ActivateHuman (GtkWidget *widget, gpointer data);
void Human (GtkMenuItem *menuitem, gpointer data);
gboolean DestroyConnect (GtkWidget *widget, GdkEvent *event, gpointer data);
void ConnectCombo (GtkComboBox *widget, gpointer data);
gboolean Connect (GtkWidget *widget, GdkEvent *event, gpointer data);
void ScrollToEnd (GtkWidget *widget, GdkRectangle *allocation, gpointer data);
void CloseSocket (void);
void ToggleWrap (GtkToggleButton *togglebutton, gpointer data);
struct in_addr *atoaddr (char *address);
void InternetGo (GtkButton *button, gpointer data);
void JudgeBoard (char cColorOther);
gboolean Latest (GtkWidget *widget, GdkEvent *event, gpointer data);
void SizeAllocate (GtkWidget *widget, GdkRectangle *allocation, gpointer data);
gboolean KeyPress (GtkWidget *widget, GdkEventKey *event, gpointer data);
void ButtonTop (GtkWidget **button, int iButtonWidth,
	int iPlace, GCallback GC, char *sName);
void MainWindow (void);
void MakeMove (GtkWidget *widget, GdkEvent *event, gpointer data);
void Message (char *sText, int iShowQuit, int iType);
int Modulo (int iOne, int iTwo);
int MyLand (char cColor);
int NotSuicide (int iPoint, char cColor);
gboolean ChangeHandicap (GtkWidget *widget, GdkEvent *event, gpointer data);
gboolean PlayerPopUp (GtkWidget *widget, GdkEvent *event, gpointer data);
void CreateButtonBox (GtkWidget **button, GtkWidget **image, char *sImageP,
	int iWidth, GCallback GC, gpointer gwid,
	int iPlaceX, int iPlaceY, int iPlaceW);
void Options (GtkWidget *widget, gpointer data);
void ChangeImageX (GtkWidget **button, GtkWidget **image, char *sImageP);
gboolean OptionsX (GtkWidget *widget, GdkEvent *event, gpointer data);
void Pass (GtkWidget *widget, gpointer data);
gboolean DrawCallback (GtkWidget *widget, cairo_t *cr, gpointer data);
void PopUpMenu (GtkWidget *widget, GdkEvent *event);
gboolean MenuOrMove (GtkWidget *widget, GdkEvent *event, gpointer data);
void PixmapOnPoint (int iPoint);
gboolean BusCallback (GstBus *busc, GstMessage *message, gpointer data);
void PadAdded (GstElement *element, GstPad *pad, gpointer data);
void Play (char *sFile, int iLoop);
void CallQuit (GtkWidget *widget, gpointer data);
gboolean Quit (GtkWidget *widget, GdkEvent *event, gpointer data);
void ReallyQuit (void);
gfloat lprogress (gfloat pvalue);
void ReallyReStart (void);
int SpaceArray (char *sString);
int PlaceToPoint (char sPlace[3]);
gboolean CallDestroyInvite (GtkWidget *widget, GdkEvent *event, gpointer data);
void DestroyInvite (GtkButton *button, gpointer data);
void InviteAcceptDecline (struct Invite stInvite);
void ReceiveData (char *sServerType);
void ReSize (GtkWidget *widget, gpointer data);
void DestroySplashText (gpointer data);
void SplashText (int iSeconds, int iWidth, int iHeight, char *sText);
void CallReStart (GtkWidget *widget, gpointer data);
void ReStart (int iReCheck);
void SaveSGF (void);
void SaveDialog (void);
float ScoreBlack (void);
float ScoreWhite (void);
void CallSendData (GtkEntry *entry, gpointer data);
void SendData (int iType, char *sData);
gboolean DestroyTime (GtkWidget *widget, GdkEvent *event, gpointer data);
void SetTimeLimit (GtkWidget *widget, gpointer data);
int StrCmp (const void* vString1, const void* vString2);
void Skin (GtkWidget *widget, gpointer data);
gboolean Sound (GtkWidget *widget, GdkEvent *event, gpointer data);
void StatusBar (void);
void TheComputer (GtkMenuItem *menuitem, gpointer data);
gboolean TimeLimit (GtkWidget *widget, GdkEvent *event, gpointer data);
gboolean Tooltips (GtkWidget *widget, GdkEvent *event, gpointer data);
void Undo (GtkWidget *widget, gpointer data);
int Where (int iAbove, int iUnder, int iRight, int iLeft);

#endif
