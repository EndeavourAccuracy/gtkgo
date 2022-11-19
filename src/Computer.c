/* gtkgo v0.0.12 (Computer.c) (November 2022)
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

#include "Computer.h"

/*****************************************************************************/
int CallChangePoint (int iPoint, char cColor)
/*****************************************************************************/
{
	/* Function used if it's unclear a change is allowed. This prevents
	 * pop-up warnings if the computer is randomly trying to use ChangePoint().
	 */

	if (cColor == 'e')
	{
		printf ("[FAILED] CallChangePoint() should never receive cColor 'e'!\n");
		exit (EXIT_ERROR);
	}

	if ((Board[iPoint][2] == 'e') || (Board[iPoint][2] == 's'))
	{
		if ((CheckSides (iPoint, cColor, 1) != 15) ||
			((NotSuicide (iPoint, cColor) == 1) &&
			(CheckSides (iPoint, cColor, 1) == 15)))
		{
			return (ChangePoint (iPoint, cColor));
		} else {
			return (0);
		}
	} else {
		return (0);
	}
}
/*****************************************************************************/
void Computer (char cColor)
/*****************************************************************************/
{
	/* Makes a computer generated move for the player with color cColor.
	 * This function needs a thorough cleanup.
	 */

	int iButtonC;
	int iRandom;
	int iReturned;
	int iCompFD;
	int iDo;
	int iDid;
	int iNeed;
	int iStopIt;
	int iTheOne;
	int arEye[6][6];
	float fNumber;
	char sPFComputer[100];
	char sChar[1];
	char cCheck;
	char cColorOther;
	char sSides[10];
	char sTempC[10];
	int iTriedB[POINTS + 2];
	/***/
	int iTry1;
	int iTry2;
	int iTry3;
	/***/
	int iOK1;
	int iOK2;
	int iOK3;
	int iOK4;
	/***/
	int i10p;
	int i50p;
	int i30moves;
	/***/
	int iAbove;
	int iUnder;
	int iRight;
	int iLeft;
	/***/
	int iTempC1;
	int iTempC2;

	/*** The next 4 lines must be here. ***/
	while (gtk_events_pending())
	{
		gtk_main_iteration();
	}

	iMoveMade = 0;
	iMoveNotSide = 0;
	iMoveNotOwn = 0;
	iMoveNotOther = 0;
	iOK1 = 1;
	i50p = 0;
	iOK2 = 1;
	i10p = 0;
	iOK3 = 1;
	iDid = 0;
	i30moves = 0;
	iOK4 = 0;
	iTheOne = -1;
	fNumber = -1;

	if (cColor == 'w')
	{
		if (iIsComputerW == 1)
		{
			snprintf (sPFComputer, 100, PKGDATADIR"computers/%s.%s",
				sPlayerNameW, GAME_NAME);
		}
		else
		{
			if (iIsComputerB == 0)
			{
				snprintf (sPFComputer, 100, PKGDATADIR"computers/default2.%s",
					GAME_NAME);
			}
			else
			{
				snprintf (sPFComputer, 100, PKGDATADIR"computers/%s.%s",
					sPlayerNameB, GAME_NAME);
			}
		}
		cColorOther = 'b';
	}
	else
	{
		if (iIsComputerB == 1)
		{
			snprintf (sPFComputer, 100, PKGDATADIR"computers/%s.%s",
				sPlayerNameB, GAME_NAME);
		}
		else
		{
			if (iIsComputerW == 0)
			{
				snprintf (sPFComputer, 100, PKGDATADIR"computers/default2.%s",
					GAME_NAME);
			}
			else
			{
				snprintf (sPFComputer, 100, PKGDATADIR"computers/%s.%s",
					sPlayerNameW, GAME_NAME);
			}
		}
		cColorOther = 'w';
	}

	iCompFD = open (sPFComputer, O_RDONLY, 0600);
	if (iCompFD == -1)
	{
		Message ("Could not open computer.", 1, 0);
	}
	else
	do
	{
		if (iDid != 1)
		{
			iReturned = read (iCompFD, sChar, 1);
		}
		else
		{
			iDid = 0;
		}
		if (iReturned == -1)
		{
			Message ("Error reading computer.", 1, 0);
		}
		else
		{

			if (i30moves == 1)
			{
				if (iMovesMade >= 49)
				{
					iOK4 = 1;
				}
				else
				{
					iOK4 = 0;
				}
			}
			else
			{
				iOK4 = 1;
			}

			/* # */

			if ((sChar[0] == '#') && (iMoveMade == 0))
			{
				if (iOK3 == 0)
				{
					iOK3 = 1;
				}
				else
				{
					iOK3 = 0;
				}
			}

			/* + */

			if ((sChar[0] == '+') && (iMoveMade == 0) && (iOK1 == 1) &&
				(iOK3 == 1) && (iOK4 == 1))
			{
				if (i10p == 1)
				{
					iOK2 = 1;
					i10p = 0;
				}
				else
				{
					iDo = 1 + (int) (10.0 * rand() / (RAND_MAX + 1.0));
					if (iDo != 10)
					{
						iOK2 = 0;
					}
					i10p = 1;
				}
			}

			/* % */

			if ((sChar[0] == '%') && (iMoveMade == 0) && (iOK2 == 1) &&
				(iOK3 == 1) && (iOK4 == 1))
			{
				if (i50p == 1)
				{
					iOK1 = 1;
					i50p = 0;
				}
				else
				{
					iDo = 1 + (int) (2.0 * rand() / (RAND_MAX + 1.0));
					if (iDo == 2)
					{
						iOK1 = 0;
					}
					i50p = 1;
				}
			}

			/* * */

			if ((sChar[0] == '*') && (iMoveMade == 0) && (iOK1 == 1) && (iOK2 == 1)
				&& (iOK3 == 1))
			{
				if (i30moves == 0)
				{
					i30moves = 1;
				}
				else
				{
					i30moves = 0;
				}
			}

			if ((iOK1 == 1) && (iOK2 == 1) && (iOK3 == 1) && (iOK4 == 1))
			{

			/* z */

			if ((sChar[0] == 'z') && (iMoveMade == 0))
			{
				for (iTempC1 = 1; iTempC1 <= 5; iTempC1++)
				{
					for (iTempC2 = 1; iTempC2 <= 5; iTempC2++)
					{
						arEye[iTempC1][iTempC2] = 0;
					}
				}
				do
				{
					iReturned = read (iCompFD, sChar, 1);
					if (iReturned == -1)
					{
						Message ("Error reading computer.", 1, 0);
					}
					switch (sChar[0])
					{
						case 'a': arEye[1][1] = 1; break;
						case 'b': arEye[1][2] = 1; break;
						case 'c': arEye[1][3] = 1; break;
						case 'd': arEye[1][4] = 1; break;
						case 'e': arEye[1][5] = 1; break;
						case 'f': arEye[2][1] = 1; break;
						case 'g': arEye[2][2] = 1; break;
						case 'h': arEye[2][3] = 1; break;
						case 'i': arEye[2][4] = 1; break;
						case 'j': arEye[2][5] = 1; break;
						case 'k': arEye[3][1] = 1; break;
						case 'l': arEye[3][2] = 1; break;
						case 'm': arEye[3][3] = 1; break;
						case 'n': arEye[3][4] = 1; break;
						case 'o': arEye[3][5] = 1; break;
						case 'p': arEye[4][1] = 1; break;
						case 'q': arEye[4][2] = 1; break;
						case 'r': arEye[4][3] = 1; break;
						case 's': arEye[4][4] = 1; break;
						case 't': arEye[4][5] = 1; break;
						case 'u': arEye[5][1] = 1; break;
						case 'v': arEye[5][2] = 1; break;
						case 'w': arEye[5][3] = 1; break;
						case 'x': arEye[5][4] = 1; break;
						case 'y': arEye[5][5] = 1;
					}
				} while ((sChar[0] != '/') && (iReturned != 0));
				if (iReturned == 0)
				{
					Message ("Incorrect computer.", 1, 0);
				}
				snprintf (sTempC, 10, "%s", "");
				do
				{
					iReturned = read (iCompFD, sChar, 1);
					if (iReturned == -1)
					{
						Message ("Error reading computer.", 1, 0);
					}
					if ((sChar[0] == '0') || (sChar[0] == '1') || (sChar[0] == '2') ||
						(sChar[0] == '3') || (sChar[0] == '4') || (sChar[0] == '5') ||
						(sChar[0] == '6') || (sChar[0] == '7') || (sChar[0] == '8') ||
						(sChar[0] == '9'))
					{
						snprintf (sSides, 10, "%s%c", sTempC, sChar[0]);
						snprintf (sTempC, 10, "%s", sSides);
					}
					else iDid = 1;
				} while ((iDid == 0) && (iReturned != 0));
				if (iReturned == 0)
				{
					Message ("Incorrect computer.", 1, 0);
				}
				iDid = 0;
				do
				{
					switch (sChar[0])
					{
						case 'a': arEye[1][1] = 2; break;
						case 'b': arEye[1][2] = 2; break;
						case 'c': arEye[1][3] = 2; break;
						case 'd': arEye[1][4] = 2; break;
						case 'e': arEye[1][5] = 2; break;
						case 'f': arEye[2][1] = 2; break;
						case 'g': arEye[2][2] = 2; break;
						case 'h': arEye[2][3] = 2; break;
						case 'i': arEye[2][4] = 2; break;
						case 'j': arEye[2][5] = 2; break;
						case 'k': arEye[3][1] = 2; break;
						case 'l': arEye[3][2] = 2; break;
						case 'm': arEye[3][3] = 2; break;
						case 'n': arEye[3][4] = 2; break;
						case 'o': arEye[3][5] = 2; break;
						case 'p': arEye[4][1] = 2; break;
						case 'q': arEye[4][2] = 2; break;
						case 'r': arEye[4][3] = 2; break;
						case 's': arEye[4][4] = 2; break;
						case 't': arEye[4][5] = 2; break;
						case 'u': arEye[5][1] = 2; break;
						case 'v': arEye[5][2] = 2; break;
						case 'w': arEye[5][3] = 2; break;
						case 'x': arEye[5][4] = 2; break;
						case 'y': arEye[5][5] = 2; break;
					}
					iReturned = read (iCompFD, sChar, 1);
					if (iReturned == -1)
					{
						Message ("Error reading computer.", 1, 0);
					}
				} while ((sChar[0] != 'z') && (iReturned != 0));
				if (iReturned == 0)
				{
					Message ("Incorrect computer.", 1, 0);
				}
				for (iButtonC = 1; iButtonC <= POINTS; iButtonC++)
				{
					if (iMoveMade != 1)
					{
						iNeed = 0;
						iStopIt = 0;

						/* a */

						if ((arEye[1][1] == 1) && (iStopIt != 1))
						{
							if ((iButtonC <= 19) ||
								(Modulo (iButtonC - 1, 19) == 0))
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC - 20][2] != 'e') &&
								(Board[iButtonC - 20][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[1][1] == 2) && (iStopIt != 1))
						{
							if ((iButtonC > 19) &&
								(Modulo (iButtonC - 1, 19) != 0))
							{
								if (Board[iButtonC - 20][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC - 20][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC - 20;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* b */

						if ((arEye[1][2] == 1) && (iStopIt != 1))
						{
							if (iButtonC <= 19)
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC - 19][2] != 'e') &&
								(Board[iButtonC - 19][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[1][2] == 2) && (iStopIt != 1))
						{
							if (iButtonC > 19)
							{
								if (Board[iButtonC - 19][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC - 19][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC - 19;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* c */

						if ((arEye[1][3] == 1) && (iStopIt != 1))
						{
							if ((iButtonC <= 19) ||
								(Modulo (iButtonC, 19) == 0))
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC - 18][2] != 'e') &&
								(Board[iButtonC - 18][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[1][3] == 2) && (iStopIt != 1))
						{
							if ((iButtonC > 19) &&
								(Modulo (iButtonC, 19) != 0))
							{
								if (Board[iButtonC - 18][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC - 18][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC - 18;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* d */

						if ((arEye[1][4] == 1) && (iStopIt != 1))
						{
							if (Modulo (iButtonC, 19) == 0)
							{
								iStopIt = 1;
							}
							if ((iButtonC <= 19) ||
								(Modulo (iButtonC + 1, 19) == 0))
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC - 17][2] != 'e') &&
								(Board[iButtonC - 17][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[1][4] == 2) && (iStopIt != 1))
						{
							if (Modulo (iButtonC, 19) == 0)
							{
								iStopIt = 1;
							}
							if ((iButtonC > 19) &&
								(Modulo (iButtonC + 1, 19) != 0))
							{
								if (Board[iButtonC - 17][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC - 17][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC - 17;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* e */

						if ((arEye[1][5] == 1) && (iStopIt != 1))
						{
							if ((Modulo (iButtonC, 19) == 0) ||
								(Modulo (iButtonC + 1, 19) == 0))
							{
								iStopIt = 1;
							}
							if ((iButtonC <= 19) ||
								(Modulo (iButtonC + 2, 19) == 0))
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC - 16][2] != 'e') &&
								(Board[iButtonC - 16][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[1][5] == 2) && (iStopIt != 1))
						{
							if ((Modulo (iButtonC, 19) == 0) ||
								(Modulo (iButtonC + 1, 19) == 0))
							{
								iStopIt = 1;
							}
							if ((iButtonC > 19) &&
								(Modulo (iButtonC + 2, 19) != 0))
							{
								if (Board[iButtonC - 16][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC - 16][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC - 16;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* f */

						if ((arEye[2][1] == 1) && (iStopIt != 1))
						{
							if (Modulo (iButtonC - 1, 19) == 0)
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC - 1][2] != 'e') &&
								(Board[iButtonC - 1][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[2][1] == 2) && (iStopIt != 1))
						{
							if (Modulo (iButtonC - 1, 19) != 0)
							{
								if (Board[iButtonC - 1][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC - 1][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC - 1;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* g */

						if ((arEye[2][2] == 1) && (iStopIt != 1))
						{
							if ((Board[iButtonC][2] != 'e') &&
								(Board[iButtonC][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[2][2] == 2) && (iStopIt != 1))
						{
							if (Board[iButtonC][2] == cColorOther)
							{
								iStopIt = 1;
							}
							if (Board[iButtonC][2] != cColor)
							{
								iNeed++;
								if (iNeed == 1) iTheOne = iButtonC;
								if (iNeed > atoi (sSides)) iStopIt = 1;
							}
						}

						/* h */

						if ((arEye[2][3] == 1) && (iStopIt != 1))
						{
							if (Modulo (iButtonC, 19) == 0)
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 1][2] != 'e') &&
								(Board[iButtonC + 1][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[2][3] == 2) && (iStopIt != 1))
						{
							if (Modulo (iButtonC, 19) != 0)
							{
								if (Board[iButtonC + 1][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 1][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 1;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* i */

						if ((arEye[2][4] == 1) && (iStopIt != 1))
						{
							if (Modulo (iButtonC, 19) == 0)
							{
								iStopIt = 1;
							}
							if (Modulo (iButtonC + 1, 19) == 0)
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 2][2] != 'e') &&
								(Board[iButtonC + 2][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[2][4] == 2) && (iStopIt != 1))
						{
							if (Modulo (iButtonC, 19) == 0)
							{
								iStopIt = 1;
							}
							if (Modulo (iButtonC + 1, 19) != 0)
							{
								if (Board[iButtonC + 2][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 2][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 2;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* j */

						if ((arEye[2][5] == 1) && (iStopIt != 1))
						{
							if ((Modulo (iButtonC, 19) == 0) ||
								(Modulo (iButtonC + 1, 19) == 0))
							{
								iStopIt = 1;
							}
							if (Modulo (iButtonC + 2, 19) == 0)
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 3][2] != 'e') &&
								(Board[iButtonC + 3][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[2][5] == 2) && (iStopIt != 1))
						{
							if ((Modulo (iButtonC, 19) == 0) ||
								(Modulo (iButtonC + 1, 19) == 0))
							{
								iStopIt = 1;
							}
							if (Modulo (iButtonC + 2, 19) != 0)
							{
								if (Board[iButtonC + 3][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 3][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 3;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* k */

						if ((arEye[3][1] == 1) && (iStopIt != 1))
						{
							if ((Modulo (iButtonC - 1, 19) == 0) ||
								(iButtonC >= 343))
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 18][2] != 'e') &&
								(Board[iButtonC + 18][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[3][1] == 2) && (iStopIt != 1))
						{
							if ((Modulo (iButtonC - 1, 19) != 0) &&
								(iButtonC < 343))
							{
								if (Board[iButtonC + 18][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 18][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 18;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* l */

						if ((arEye[3][2] == 1) && (iStopIt != 1))
						{
							if (iButtonC >= 343)
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 19][2] != 'e') &&
								(Board[iButtonC + 19][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[3][2] == 2) && (iStopIt != 1))
						{
							if (iButtonC < 343)
							{
								if (Board[iButtonC + 19][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 19][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 19;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* m */

						if ((arEye[3][3] == 1) && (iStopIt != 1))
						{
							if ((Modulo (iButtonC, 19) == 0) ||
								(iButtonC >= 343))
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 20][2] != 'e') &&
								(Board[iButtonC + 20][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[3][3] == 2) && (iStopIt != 1))
						{
							if ((Modulo (iButtonC, 19) != 0) &&
								(iButtonC < 343))
							{
								if (Board[iButtonC + 20][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 20][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 20;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* n */

						if ((arEye[3][4] == 1) && (iStopIt != 1))
						{
							if (Modulo (iButtonC, 19) == 0)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC + 1, 19) == 0) ||
								(iButtonC >= 343))
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 21][2] != 'e') &&
								(Board[iButtonC + 21][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[3][4] == 2) && (iStopIt != 1))
						{
							if (Modulo (iButtonC, 19) == 0)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC + 1, 19) != 0) &&
								(iButtonC < 343))
							{
								if (Board[iButtonC + 21][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 21][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 21;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* o */

						if ((arEye[3][5] == 1) && (iStopIt != 1))
						{
							if ((Modulo (iButtonC, 19) == 0) ||
								(Modulo (iButtonC + 1, 19) == 0))
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC + 2, 19) == 0) ||
								(iButtonC >= 343))
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 22][2] != 'e') &&
								(Board[iButtonC + 22][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[3][5] == 2) && (iStopIt != 1))
						{
							if ((Modulo (iButtonC, 19) == 0) ||
								(Modulo (iButtonC + 1, 19) == 0))
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC + 2, 19) != 0) &&
								(iButtonC < 343))
							{
								if (Board[iButtonC + 22][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 22][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 22;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* p */

						if ((arEye[4][1] == 1) && (iStopIt != 1))
						{
							if (iButtonC >= 343)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC - 1, 19) == 0) ||
								(iButtonC >= 324))
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 37][2] != 'e') &&
								(Board[iButtonC + 37][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[4][1] == 2) && (iStopIt != 1))
						{
							if (iButtonC >= 343)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC - 1, 19) != 0) &&
								(iButtonC < 324))
							{
								if (Board[iButtonC + 37][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 37][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 37;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* q */

						if ((arEye[4][2] == 1) && (iStopIt != 1))
						{
							if (iButtonC >= 343)
							{
								iStopIt = 1;
							}
							if (iButtonC >= 324)
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 38][2] != 'e') &&
								(Board[iButtonC + 38][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[4][2] == 2) && (iStopIt != 1))
						{
							if (iButtonC >= 343)
							{
								iStopIt = 1;
							}
							if (iButtonC < 324)
							{
								if (Board[iButtonC + 38][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 38][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 38;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* r */

						if ((arEye[4][3] == 1) && (iStopIt != 1))
						{
							if (iButtonC >= 343)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC, 19) == 0) ||
								(iButtonC >= 324))
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 39][2] != 'e') &&
								(Board[iButtonC + 39][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[4][3] == 2) && (iStopIt != 1))
						{
							if (iButtonC >= 343)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC, 19) != 0) &&
								(iButtonC < 324))
							{
								if (Board[iButtonC + 39][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 39][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 39;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* s */

						if ((arEye[4][4] == 1) && (iStopIt != 1))
						{
							if (iButtonC >= 343)
							{
								iStopIt = 1;
							}
							if (Modulo (iButtonC, 19) == 0)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC + 1, 19) == 0) ||
								(iButtonC >= 324))
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 40][2] != 'e') &&
								(Board[iButtonC + 40][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[4][4] == 2) && (iStopIt != 1))
						{
							if (iButtonC >= 343)
							{
								iStopIt = 1;
							}
							if (Modulo (iButtonC, 19) == 0)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC + 1, 19) != 0) &&
								(iButtonC < 324))
							{
								if (Board[iButtonC + 40][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 40][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 40;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* t */

						if ((arEye[4][5] == 1) && (iStopIt != 1))
						{
							if (iButtonC >= 343)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC, 19) == 0) ||
								(Modulo (iButtonC + 1, 19) == 0))
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC + 2, 19) == 0) ||
								(iButtonC >= 324))
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 41][2] != 'e') &&
								(Board[iButtonC + 41][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[4][5] == 2) && (iStopIt != 1))
						{
							if (iButtonC >= 343)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC, 19) == 0) ||
								(Modulo (iButtonC + 1, 19) == 0))
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC + 2, 19) != 0) &&
								(iButtonC < 324))
							{
								if (Board[iButtonC + 41][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 41][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 41;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* u */

						if ((arEye[5][1] == 1) && (iStopIt != 1))
						{
							if (iButtonC >= 324)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC - 1, 19) == 0) ||
								(iButtonC >= 305))
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 56][2] != 'e') &&
								(Board[iButtonC + 56][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[5][1] == 2) && (iStopIt != 1))
						{
							if (iButtonC >= 324)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC - 1, 19) != 0) &&
								(iButtonC < 305))
							{
								if (Board[iButtonC + 56][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 56][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 56;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* v */

						if ((arEye[5][2] == 1) && (iStopIt != 1))
						{
							if (iButtonC >= 324)
							{
								iStopIt = 1;
							}
							if (iButtonC >= 305)
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 57][2] != 'e') &&
								(Board[iButtonC + 57][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[5][2] == 2) && (iStopIt != 1))
						{
							if (iButtonC >= 324)
							{
								iStopIt = 1;
							}
							if (iButtonC < 305)
							{
								if (Board[iButtonC + 57][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 57][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 57;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* w */

						if ((arEye[5][3] == 1) && (iStopIt != 1))
						{
							if (iButtonC >= 324)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC, 19) == 0) ||
								(iButtonC >= 305))
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 58][2] != 'e') &&
								(Board[iButtonC + 58][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[5][3] == 2) && (iStopIt != 1))
						{
							if (iButtonC >= 324)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC, 19) != 0) &&
								(iButtonC < 305))
							{
								if (Board[iButtonC + 58][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 58][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 58;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* x */

						if ((arEye[5][4] == 1) && (iStopIt != 1))
						{
							if (iButtonC >= 324)
							{
								iStopIt = 1;
							}
							if (Modulo (iButtonC, 19) == 0)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC + 1, 19) == 0) ||
								(iButtonC >= 305))
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 59][2] != 'e') &&
								(Board[iButtonC + 59][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[5][4] == 2) && (iStopIt != 1))
						{
							if (iButtonC >= 324)
							{
								iStopIt = 1;
							}
							if (Modulo (iButtonC, 19) == 0)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC + 1, 19) != 0) &&
								(iButtonC < 305))
							{
								if (Board[iButtonC + 59][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 59][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 59;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						/* y */

						if ((arEye[5][5] == 1) && (iStopIt != 1))
						{
							if (iButtonC >= 324)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC, 19) == 0) ||
								(Modulo (iButtonC + 1, 19) == 0))
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC + 2, 19) == 0) ||
								(iButtonC >= 305))
							{
								iStopIt = 1;
							}
							if ((Board[iButtonC + 60][2] != 'e') &&
								(Board[iButtonC + 60][2] != 's'))
							{
								iStopIt = 1;
							}
						}
						if ((arEye[5][5] == 2) && (iStopIt != 1))
						{
							if (iButtonC >= 324)
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC, 19) == 0) ||
								(Modulo (iButtonC + 1, 19) == 0))
							{
								iStopIt = 1;
							}
							if ((Modulo (iButtonC + 2, 19) != 0) &&
								(iButtonC < 305))
							{
								if (Board[iButtonC + 60][2] == cColorOther)
								{
									iStopIt = 1;
								}
								if (Board[iButtonC + 60][2] != cColor)
								{
									iNeed++;
									if (iNeed == 1) iTheOne = iButtonC + 60;
									if (iNeed > atoi (sSides)) iStopIt = 1;
								}
							}
						}

						if ((iStopIt != 1) && (iNeed != 0))
						{
							CallChangePoint (iTheOne, cColor);
						}
					}
				}
			}

			/* m */

			if ((sChar[0] == 'm') && (iMoveMade == 0))
			{
				for (iButtonC = 1; iButtonC <= POINTS; iButtonC++)
				{
					if (((Board[iButtonC - 1][2] == cColorOther) ||
						(Board[iButtonC + 1][2] == cColorOther) ||
						(Board[iButtonC - 19][2] == cColorOther) ||
						(Board[iButtonC + 19][2] == cColorOther)) &&
						(Board[iButtonC - 20][2] != cColor) &&
						(Board[iButtonC - 19][2] != cColor) &&
						(Board[iButtonC - 18][2] != cColor) &&
						(Board[iButtonC - 1][2] != cColor) &&
						(Board[iButtonC + 1][2] != cColor) &&
						(Board[iButtonC + 18][2] != cColor) &&
						(Board[iButtonC + 19][2] != cColor) &&
						(Board[iButtonC + 20][2] != cColor) &&
						(Board[iButtonC][2] == cColor))
					{
						fNumber++;
					}
				}
				if (fNumber != 0)
				{
					iRandom = 1 + (int) (fNumber * rand() / (RAND_MAX + 1.0));
					fNumber = 0;
					iTry1 = 0;
					for (iButtonC = 1; iButtonC <= POINTS; iButtonC++)
					{
						if (((Board[iButtonC - 1][2] == cColorOther) ||
							(Board[iButtonC + 1][2] == cColorOther) ||
							(Board[iButtonC - 19][2] == cColorOther) ||
							(Board[iButtonC + 19][2] == cColorOther)) &&
							(Board[iButtonC - 20][2] != cColor) &&
							(Board[iButtonC - 19][2] != cColor) &&
							(Board[iButtonC - 18][2] != cColor) &&
							(Board[iButtonC - 1][2] != cColor) &&
							(Board[iButtonC + 1][2] != cColor) &&
							(Board[iButtonC + 18][2] != cColor) &&
							(Board[iButtonC + 19][2] != cColor) &&
							(Board[iButtonC + 20][2] != cColor) &&
							(Board[iButtonC][2] == cColor))
						{
							fNumber++;
						}
						if ((fNumber == iRandom) && (iTry1 == 0))
						{
							iTry1 = 1;
							if ((Modulo (iButtonC - 1, 19) != 0) && (iButtonC > 19))
							{
								CallChangePoint (iButtonC - 20, cColor);
							}
							if ((Modulo (iButtonC, 19) != 0) && (iButtonC > 19) &&
								(iMoveMade == 0))
							{
								CallChangePoint (iButtonC - 18, cColor);
							}
							if ((Modulo (iButtonC - 1, 19) != 0) && (iButtonC < 343) &&
								(iMoveMade == 0))
							{
								CallChangePoint (iButtonC + 18, cColor);
							}
							if ((Modulo (iButtonC, 19) != 0) && (iButtonC < 343) &&
								(iMoveMade == 0))
							{
								CallChangePoint (iButtonC + 20, cColor);
							}
						}
					}
				}
			}

			/* X */

			if ((sChar[0] == 'X') && (iMoveMade == 0))
			{
				fNumber = 0;
				for (iButtonC = 1; iButtonC <= POINTS; iButtonC++)
				{
					if ((FreePlace (iButtonC, cColor, 'F') == 1) &&
						(((iButtonC > 40) && (iButtonC < 56)) ||
						((iButtonC > 59) && (iButtonC < 75)) ||
						((iButtonC > 78) && (iButtonC < 94)) ||
						((iButtonC > 268) && (iButtonC < 284)) ||
						((iButtonC > 287) && (iButtonC < 303)) ||
						((iButtonC > 306) && (iButtonC < 322)) ||
						(((PointToPlace (1, iButtonC)[0] == 'c') ||
						(PointToPlace (1, iButtonC)[0] == 'd') ||
						(PointToPlace (1, iButtonC)[0] == 'e') ||
						(PointToPlace (1, iButtonC)[0] == 'o') ||
						(PointToPlace (1, iButtonC)[0] == 'p') ||
						(PointToPlace (1, iButtonC)[0] == 'q')) &&
						((PointToPlace (1, iButtonC)[1] == 'f') ||
						(PointToPlace (1, iButtonC)[1] == 'g') ||
						(PointToPlace (1, iButtonC)[1] == 'h') ||
						(PointToPlace (1, iButtonC)[1] == 'i') ||
						(PointToPlace (1, iButtonC)[1] == 'j') ||
						(PointToPlace (1, iButtonC)[1] == 'k') ||
						(PointToPlace (1, iButtonC)[1] == 'l') ||
						(PointToPlace (1, iButtonC)[1] == 'm') ||
						(PointToPlace (1, iButtonC)[1] == 'n')))))
					{
						fNumber++;
					}
				}
				if (fNumber != 0)
				{
					iRandom = 1 + (int) (fNumber * rand() / (RAND_MAX + 1.0));
					fNumber = 0;
					iTry1 = 0;
					for (iButtonC = 1; iButtonC <= POINTS; iButtonC++)
					{
						if ((FreePlace (iButtonC, cColor, 'F') == 1) &&
							(((iButtonC > 40) && (iButtonC < 56)) ||
							((iButtonC > 59) && (iButtonC < 75)) ||
							((iButtonC > 78) && (iButtonC < 94)) ||
							((iButtonC > 268) && (iButtonC < 284)) ||
							((iButtonC > 287) && (iButtonC < 303)) ||
							((iButtonC > 306) && (iButtonC < 322)) ||
							(((PointToPlace (1, iButtonC)[0] == 'c') ||
							(PointToPlace (1, iButtonC)[0] == 'd') ||
							(PointToPlace (1, iButtonC)[0] == 'e') ||
							(PointToPlace (1, iButtonC)[0] == 'o') ||
							(PointToPlace (1, iButtonC)[0] == 'p') ||
							(PointToPlace (1, iButtonC)[0] == 'q')) &&
							((PointToPlace (1, iButtonC)[1] == 'f') ||
							(PointToPlace (1, iButtonC)[1] == 'g') ||
							(PointToPlace (1, iButtonC)[1] == 'h') ||
							(PointToPlace (1, iButtonC)[1] == 'i') ||
							(PointToPlace (1, iButtonC)[1] == 'j') ||
							(PointToPlace (1, iButtonC)[1] == 'k') ||
							(PointToPlace (1, iButtonC)[1] == 'l') ||
							(PointToPlace (1, iButtonC)[1] == 'm') ||
							(PointToPlace (1, iButtonC)[1] == 'n')))))
						{
							fNumber++;
						}
						if ((fNumber == iRandom) && (iMoveMade == 0) && (iTry1 == 0))
						{
							CallChangePoint (iButtonC, cColor);
							iTry1 = 1;
						}
					}
				}
			}

			/* s */

			if ((sChar[0] == 's') && (iMoveMade == 0))
			{
				iAbove = 0;
				iUnder = 0;
				iLeft = 0;
				iRight = 0;
				do
				{
					iReturned = read (iCompFD, sChar, 1);
					if (iReturned == -1)
					{
						Message ("Error reading computer.", 1, 0);
					}
				} while ((sChar[0] != 'C') && (sChar[0] != 'N') && (iReturned != 0));
				if (iReturned == 0)
				{
					Message ("Incorrect computer.", 1, 0);
				}
				cCheck = sChar[0];
				snprintf (sTempC, 10, "%s", "");
				do
				{
					iReturned = read (iCompFD, sChar, 1);
					if (iReturned == -1)
					{
						Message ("Error reading computer.", 1, 0);
					}
					if ((sChar[0] == '0') || (sChar[0] == '1') || (sChar[0] == '2') ||
						(sChar[0] == '3') || (sChar[0] == '4') || (sChar[0] == '5') ||
						(sChar[0] == '6') || (sChar[0] == '7') || (sChar[0] == '8') ||
						(sChar[0] == '9'))
					{
						snprintf (sSides, 10, "%s%c", sTempC, sChar[0]);
						snprintf (sTempC, 10, "%s", sSides);
					}
				} while ((sChar[0] != 'a') && (sChar[0] != 'u') &&
					(sChar[0] != 'r') && (sChar[0] != 'l') && (iReturned != 0));
				if (iReturned == 0)
				{
					Message ("Incorrect computer.", 1, 0);
				}
				if (sChar[0] == 'a') iAbove = 1;
				if (sChar[0] == 'u') iUnder = 1;
				if (sChar[0] == 'r') iRight = 1;
				if (sChar[0] == 'l') iLeft = 1;
				do
				{
					iReturned = read (iCompFD, sChar, 1);
					if (iReturned == -1)
					{
						Message ("Error reading computer.", 1, 0);
					}
					if (sChar[0] == 'a') iAbove = 1;
					if (sChar[0] == 'u') iUnder = 1;
					if (sChar[0] == 'r') iRight = 1;
					if (sChar[0] == 'l') iLeft = 1;
				} while (((sChar[0] == 'a') || (sChar[0] == 'u') || (sChar[0] == 'r')
					|| (sChar[0] == 'l')) && (iReturned != 0));
				if (iReturned == 0)
				{
					Message ("Incorrect computer.", 1, 0);
				}
				iDid = 1;
				iRandom = Where (iAbove, iUnder, iRight, iLeft);
				if (cCheck == 'C')
				{
					for (iButtonC = 1; iButtonC <= POINTS; iButtonC++)
					{
						if ((Board[iButtonC][2] == cColor) && (iMoveMade == 0))
						{
							if (CheckSides (iButtonC, cColor, 1) == atoi (sSides))
							{
								if (iRandom == 1)
								{
									CallChangePoint (iButtonC - 19, cColor);
								}
								if (iRandom == 2)
								{
									CallChangePoint (iButtonC + 19, cColor);
								}
								if (iRandom == 3)
								{
									CallChangePoint (iButtonC + 1, cColor);
								}
								if (iRandom == 4)
								{
									CallChangePoint (iButtonC - 1, cColor);
								}
							}
						}
					}
				}
				else
				{
					for (iButtonC = 1; iButtonC <= POINTS; iButtonC++)
					{
						if ((Board[iButtonC][2] == cColorOther) && (iMoveMade == 0))
						{
							if (CheckSides (iButtonC, cColorOther, 1) == atoi (sSides))
							{
								if (iRandom == 1)
								{
									CallChangePoint (iButtonC - 19, cColor);
								}
								if (iRandom == 2)
								{
									CallChangePoint (iButtonC + 19, cColor);
								}
								if (iRandom == 3)
								{
									CallChangePoint (iButtonC + 1, cColor);
								}
								if (iRandom == 4)
								{
									CallChangePoint (iButtonC - 1, cColor);
								}
							}
						}
					}
				}
			}

			/* g */

			if ((sChar[0] == 'g') && (iMoveMade == 0) && (iDid != 1))
			{
				iAbove = 0;
				iUnder = 0;
				iLeft = 0;
				iRight = 0;
				do
				{
					iReturned = read (iCompFD, sChar, 1);
					if (iReturned == -1)
					{
						Message ("Error reading computer.", 1, 0);
					}
				} while ((sChar[0] != 'C') && (sChar[0] != 'N') && (iReturned != 0));
				if (iReturned == 0)
				{
					Message ("Incorrect computer.", 1, 0);
				}
				cCheck = sChar[0];
				snprintf (sTempC, 10, "%s", "");
				do
				{
					iReturned = read (iCompFD, sChar, 1);
					if (iReturned == -1)
					{
						Message ("Error reading computer.", 1, 0);
					}
					if ((sChar[0] == '0') || (sChar[0] == '1') || (sChar[0] == '2') ||
						(sChar[0] == '3') || (sChar[0] == '4') || (sChar[0] == '5') ||
						(sChar[0] == '6') || (sChar[0] == '7') || (sChar[0] == '8') ||
						(sChar[0] == '9'))
					{
						snprintf (sSides, 10, "%s%c", sTempC, sChar[0]);
						snprintf (sTempC, 10, "%s", sSides);
					}
				} while ((sChar[0] != 'a') && (sChar[0] != 'u') &&
					(sChar[0] != 'r') && (sChar[0] != 'l') && (iReturned != 0));
				if (iReturned == 0)
				{
					Message ("Incorrect computer.", 1, 0);
				}
				if (sChar[0] == 'a') iAbove = 1;
				if (sChar[0] == 'u') iUnder = 1;
				if (sChar[0] == 'r') iRight = 1;
				if (sChar[0] == 'l') iLeft = 1;
				do
				{
					iReturned = read (iCompFD, sChar, 1);
					if (iReturned == -1)
					{
						Message ("Error reading computer.", 1, 0);
					}
					if (sChar[0] == 'a') iAbove = 1;
					if (sChar[0] == 'u') iUnder = 1;
					if (sChar[0] == 'r') iRight = 1;
					if (sChar[0] == 'l') iLeft = 1;
				} while (((sChar[0] == 'a') || (sChar[0] == 'u') || (sChar[0] == 'r')
					|| (sChar[0] == 'l')) && (iReturned != 0));
				if (iReturned == 0)
				{
					Message ("Incorrect computer.", 1, 0);
				}
				iDid = 1;
				if (((cCheck == 'C') && (cColor == 'b')) ||
					((cCheck == 'N') && (cColor == 'w')))
				{
					if (CheckSides (iLastMoveB, 'b', 3) >= atoi (sSides))
					{
						if ((iMoveMade == 0) && (iAbove == 1) && (iLastMoveB > 19))
							CallChangePoint (iLastMoveB - 19, cColor);
						if ((iMoveMade == 0) && (iUnder == 1) && (iLastMoveB < 343))
							CallChangePoint (iLastMoveB + 19, cColor);
						if ((iMoveMade == 0) && (iRight == 1) &&
							(Modulo (iLastMoveB, 19) != 0))
							CallChangePoint (iLastMoveB + 1, cColor);
						if ((iMoveMade == 0) && (iLeft == 1) &&
							(Modulo (iLastMoveB - 1, 19) != 0))
							CallChangePoint (iLastMoveB - 1, cColor);
					}
				}
				if (((cCheck == 'C') && (cColor == 'w')) ||
					((cCheck == 'N') && (cColor == 'b')))
				{
					if (CheckSides (iLastMoveW, 'w', 3) >= atoi (sSides))
					{
						if ((iMoveMade == 0) && (iAbove == 1) && (iLastMoveW > 19))
							CallChangePoint (iLastMoveW - 19, cColor);
						if ((iMoveMade == 0) && (iUnder == 1) && (iLastMoveW < 343))
							CallChangePoint (iLastMoveW + 19, cColor);
						if ((iMoveMade == 0) && (iRight == 1) &&
							(Modulo (iLastMoveW, 19) != 0))
							CallChangePoint (iLastMoveW + 1, cColor);
						if ((iMoveMade == 0) && (iLeft == 1) &&
							(Modulo (iLastMoveW - 1, 19) != 0))
							CallChangePoint (iLastMoveW - 1, cColor);
					}
				}
				if (cCheck == 'C')
				{
					for (iButtonC = 1; iButtonC <= POINTS; iButtonC++)
					{
						if ((Board[iButtonC][2] == cColor) && (iMoveMade == 0))
						{
							if (CheckSides (iButtonC, cColor, 3) >= atoi (sSides))
							{
								if ((iMoveMade == 0) && (iAbove == 1) && (iButtonC > 19))
									CallChangePoint (iButtonC - 19, cColor);
								if ((iMoveMade == 0) && (iUnder == 1) && (iButtonC < 343))
									CallChangePoint (iButtonC + 19, cColor);
								if ((iMoveMade == 0) && (iRight == 1) &&
									(Modulo (iButtonC, 19) != 0))
									CallChangePoint (iButtonC + 1, cColor);
								if ((iMoveMade == 0) && (iLeft == 1) &&
									(Modulo (iButtonC - 1, 19) != 0))
									CallChangePoint (iButtonC - 1, cColor);
							}
						}
					}
				}
				else
				{
					for (iButtonC = 1; iButtonC <= POINTS; iButtonC++)
					{
						if ((Board[iButtonC][2] == cColorOther) && (iMoveMade == 0))
						{
							if (CheckSides (iButtonC, cColorOther, 3) >= atoi (sSides))
							{
								if ((iMoveMade == 0) && (iAbove == 1) && (iButtonC > 19))
									CallChangePoint (iButtonC - 19, cColor);
								if ((iMoveMade == 0) && (iUnder == 1) && (iButtonC < 343))
									CallChangePoint (iButtonC + 19, cColor);
								if ((iMoveMade == 0) && (iRight == 1) &&
									(Modulo (iButtonC, 19) != 0))
									CallChangePoint (iButtonC + 1, cColor);
								if ((iMoveMade == 0) && (iLeft == 1) &&
									(Modulo (iButtonC - 1, 19) != 0))
									CallChangePoint (iButtonC - 1, cColor);
							}
						}
					}
				}
			}

			/* l */

			if ((sChar[0] == 'l') && (iMoveMade == 0) && (iDid != 1))
			{
				iAbove = 0;
				iUnder = 0;
				iLeft = 0;
				iRight = 0;
				do
				{
					iReturned = read (iCompFD, sChar, 1);
					if (iReturned == -1)
					{
						Message ("Error reading computer.", 1, 0);
					}
					if (sChar[0] == 'a') iAbove = 1;
					if (sChar[0] == 'u') iUnder = 1;
					if (sChar[0] == 'r') iRight = 1;
					if (sChar[0] == 'l') iLeft = 1;
				} while ((sChar[0] != 'C') && (sChar[0] != 'N') && (iReturned != 0));
				if (iReturned == 0)
				{
					Message ("Incorrect computer.", 1, 0);
				}
				iRandom = Where (iAbove, iUnder, iRight, iLeft);
				if (((sChar[0] == 'C') && (cColor == 'b')) ||
					((sChar[0] == 'N') && (cColor == 'w')))
				{
					if (iRandom == 1)
					{
						if (iLastMoveB - 19 >= 1)
						{
							CallChangePoint (iLastMoveB - 19, cColor);
						}
					}
					if (iRandom == 2)
					{
						if (iLastMoveB + 19 <= 361)
						{
							CallChangePoint (iLastMoveB + 19, cColor);
						}
					}
					if (iRandom == 3)
					{
						if (Modulo (iLastMoveB, 19) != 0)
						{
							CallChangePoint (iLastMoveB + 1, cColor);
						}
					}
					if (iRandom == 4)
					{
						if (Modulo (iLastMoveB - 1, 19) != 0)
						{
							CallChangePoint (iLastMoveB - 1, cColor);
						}
					}
					if (((sChar[0] == 'N') && (cColor == 'b')) ||
						((sChar[0] == 'C') && (cColor == 'w')))
					{
						if (iRandom == 1)
						{
							if (iLastMoveW - 19 >= 1)
							{
								CallChangePoint (iLastMoveW - 19, cColor);
							}
						}
						if (iRandom == 2)
						{
							if (iLastMoveW + 19 <= 361)
							{
								CallChangePoint (iLastMoveW + 19, cColor);
							}
						}
						if (iRandom == 3)
						{
							if (Modulo (iLastMoveW, 19) != 0)
							{
								CallChangePoint (iLastMoveW + 1, cColor);
							}
						}
						if (iRandom == 4)
						{
							if (Modulo (iLastMoveW - 1, 19) != 0)
							{
								CallChangePoint (iLastMoveW - 1, cColor);
							}
						}
					}
				}
			}

			/* ! */

			if ((sChar[0] == '!') && (iMoveMade == 0) && (iDid != 1))
			{
				if (iMoveNotOwn == 0)
				{
					iMoveNotOwn = 1;
				}
				else
				{
					iMoveNotOwn = 0;
				}
			}

			/* . */

			if ((sChar[0] == '.') && (iMoveMade == 0) && (iDid != 1))
			{
				if (iMoveNotOther == 0)
				{
					iMoveNotOther = 1;
				}
				else
				{
					iMoveNotOther = 0;
				}
			}

			/* $ */

			if ((sChar[0] == '$') && (iMoveMade == 0) && (iDid != 1))
			{
				if (iMoveNotSide == 0)
				{
					iMoveNotSide = 1;
				}
				else
				{
					iMoveNotSide = 0;
				}
			}

			/* E */

			if ((sChar[0] == 'E') && (iMoveMade == 0) && (iDid != 1))
			{
				if ((cColor == 'w') && (HistoryPassed[iMovesMade] == 1) &&
					(ScoreWhite() > ScoreBlack()))
				{
					HistoryPassed[iMovesMade + 1] = 1;
					EndGame();
					iMoveMade = 1;
				}
				if ((cColor == 'b') && (HistoryPassed[iMovesMade] == 1) &&
					(ScoreBlack() > ScoreWhite()))
				{
					HistoryPassed[iMovesMade + 1] = 1;
					EndGame();
					iMoveMade = 1;
				}
			}

			/* F */

			if ((sChar[0] == 'F') && (iMoveMade == 0) && (iDid != 1))
			{
				fNumber = 0;
				for (iButtonC = 1; iButtonC <= POINTS; iButtonC++)
				{
					if (FreePlace (iButtonC, cColor, 'F') == 1)
					{
						fNumber++;
					}
				}
				if (fNumber != 0)
				{
					iRandom = 1 + (int) (fNumber * rand() / (RAND_MAX + 1.0));
					fNumber = 0;
					iTry1 = 0;
					for (iButtonC = 1; iButtonC <= POINTS; iButtonC++)
					{
						if (FreePlace (iButtonC, cColor, 'F') == 1)
						{
							fNumber++;
						}
						if ((fNumber == iRandom) && (iMoveMade == 0) && (iTry1 == 0))
						{
							CallChangePoint (iButtonC, cColor);
							iTry1 = 1;
						}
					}
				}
			}

			/* f */

			if ((sChar[0] == 'f') && (iMoveMade == 0) && (iDid != 1))
			{
				fNumber = 0;
				for (iButtonC = 1; iButtonC <= POINTS; iButtonC++)
				{
					if (FreePlace (iButtonC, cColor, 'f') == 1)
					{
						fNumber++;
					}
				}
				if (fNumber != 0)
				{
					iRandom = 1 + (int) (fNumber * rand() / (RAND_MAX + 1.0));
					fNumber = 0;
					iTry2 = 0;
					for (iButtonC = 1; iButtonC <= POINTS; iButtonC++)
					{
						if (FreePlace (iButtonC, cColor, 'f') == 1)
						{
							fNumber++;
						}
						if ((fNumber == iRandom) && (iMoveMade == 0) && (iTry2 == 0))
						{
							CallChangePoint (iButtonC, cColor);
							iTry2 = 1;
						}
					}
				}
			}

			/* M */

			if ((sChar[0] == 'M') && (iMoveMade == 0) && (iDid != 1))
			{
				for (iButtonC = 1; iButtonC <= POINTS; iButtonC++)
				{
					iTriedB[iButtonC] = 0;
				}
				do {
					fNumber = 0;
					for (iButtonC = 1; iButtonC <= POINTS; iButtonC++)
					{
						if ((FreePlace (iButtonC, cColor, 'M') == 1)
							&& (iTriedB[iButtonC] != 1))
						{
							fNumber++;
						}
					}
					if (fNumber != 0)
					{
						iRandom = 1 + (int) (fNumber * rand() / (RAND_MAX + 1.0));
						fNumber = 0;
						iTry3 = 0;
						for (iButtonC = 1; iButtonC <= POINTS; iButtonC++)
						{
							if ((FreePlace (iButtonC, cColor, 'M') == 1)
								&& (iTriedB[iButtonC] != 1))
							{
								fNumber++;
							}
							if ((fNumber == iRandom) && (iMoveMade == 0) && (iTry3 == 0))
							{
								CallChangePoint (iButtonC, cColor);
								iTriedB[iButtonC] = 1;
								iTry3 = 1;
							}
						}
					}
				} while ((fNumber != 0) && (iMoveMade == 0));
			}

			/* P */

			if ((sChar[0] == 'P') && (iMoveMade == 0) && (iDid != 1))
			{
				if (cColor == 'w')
				{
					HistoryPassed[iMovesMade + 1] = 1;
					if (HistoryPassed[iMovesMade] == 1)
					{
						EndGame();
					}
				}
				else
				{
					HistoryPassed[iMovesMade + 1] = 1;
					if (HistoryPassed[iMovesMade] == 1)
					{
						EndGame();
					}
				}
				iMoveMade = 1;
			}

			}

		}
	} while ((iReturned != 0) && (iMoveMade == 0));
	close (iCompFD);
	if (iMoveMade == 0)
	{
		if (cColor == 'w')
		{
			HistoryPassed[iMovesMade + 1] = 1;
			if (HistoryPassed[iMovesMade] == 1)
			{
				EndGame();
			}
		}
		else
		{
			HistoryPassed[iMovesMade + 1] = 1;
			if (HistoryPassed[iMovesMade] == 1)
			{
				EndGame();
			}
		}
	}
	else
	{
		if (((iMovesMade == 0) || (iMovesMade == 1)) && (iJustRestarted == 1))
		{
			iHandicapStart = iHandicap;
			iJustRestarted = 0;
		}
	}
	while (gtk_events_pending())
	{
		gtk_main_iteration();
	}
}
/*****************************************************************************/
