gtkgo v0.0.12 (November 2022)
Copyright (C) 1998-2022 Norbert de Jonge <nlmdejonge@gmail.com>

- [CONTENTS] ------------------------------------------------------------------

1 ABOUT/RULES
2 LICENSE/DISCLAIMER
3 INSTALL
4 MAKING GO-COMPUTERS
5 FEEDBACK
6 TODO

- [1 ABOUT/RULES] -------------------------------------------------------------

[About]
A skinnable go client.

The goal of the gtkgo project is to make a go game for both Linux and Windows,
that has skin support and can load computer scripts that can be made by users,
so that different go-computers can 'attack' each other or other users.

The gtkgo website:
https://github.com/EndeavourAccuracy/gtkgo

Information about the SGF FF[4] save format:
https://www.red-bean.com/sgf/

NNGS commands:
http://web.archive.org/web/20050310114628/nngs.cosmic.org/help.html
https://github.com/matsu911/nngs/tree/master/data/help/en

Go rules can be confusing. To be able to build very strong gtkgo go-computers
in the future, gtkgo does NOT rely on different rule sets (as some go programs
do). Instead, it uses the following static (Japanese/IGS-like) rules:

[Rules]
In gtkgo, two players (human player or go-computer) alternate in placing a
stone of their color on an empty intersection on a square board with 19x19
intersections (the weaker player always takes black and goes first). A player
may also pass (the game ends after two consecutive passes). Stones (or a group
of stones) that are surrounded, with no liberties on one of their sides (note
that diagonal points are no liberties) are captured and removed from the board.
It is not allowed to place a stone on a point with no liberties (suicide),
unless this will help you to capture stone(s) from your opponent. Repeats (ko)
are not allowed either. The placement of handicap stones (used to allow players
with different ranks to compete, the handicap is the number of ranks between
two players) is fixed.

[Scoring]
Scoring goes by territory: territory surrounded (not occupied) by your color
plus the prisoners you have captured. So, placing stones in your own territory
lessens your score. Points in an undecided situation (called seki) will be
counted (after removing dead stones, dead stones are stones that are not
functional on the board). White will get 5.5 score extra (called komi) since it
didn't start the game (0.5 in a handicapped game). Of course, the player with
the highest score wins.

[Ranks]
If I'm not mistaken, with go, there are two different series of ranks. The
amateur ranks: (Weak) 30 kyu ... 1 kyu 1 dan ... 6 dan (Strong)
and the professional ranks (professionals are almost always better than
amateurs, but some differences between the dans are just formal and make the
ranks even more confusing): (Weak) 1 dan ... 9 dan (Strong).

- [2 LICENSE/DISCLAIMER] ------------------------------------------------------

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this game; if not, write to the Free Software Foundation, Inc., 59 Temple Place
- Suite 330, Boston, MA 02111-1307, USA.

- [3 INSTALL] -----------------------------------------------------------------

Required:
* GTK+ 3.24+ (apt-get install libgtk-3-dev)
* GStreamer 1.16+ (apt-get install libgstreamer1.0-dev)

$ tar -zxvf gtkgo-0.0.12.tar.gz
$ cd gtkgo-0.0.12/src/
$ make

- [4 MAKING GO-COMPUTERS] -----------------------------------------------------

A new computer can be made by editing a new .gtkgo file in the computers
directory. When a computer has to make a new move, the selected .gtkgo script
will be parsed (character by character) by the computer. If the computer has
found a new move, the rest of the script will be ignored. The script commands
(all other characters in a script will be ignored):

z<a-y>/?<a-y>z   Use this for the eye concept. This command can check, for all
                 points on the board, if two eyes in a connecting group can be
                 made. Take a look at the following block with characters:

                 abcde
                 fghij
                 klmno
                 pqrst
                 uvwxy

                 Each point on the board, checked by the computer, will be seen
                 as the 'g'. If all points before the '/' are empty and just ?
                 or less stones are needed to make all points after the ? be
                 occupied by your color, the computer will make its next move
                 on the next point after the ? that is not yours yet. Note that
                 the computer will only do this if all points after the ? are
                 yours or empty. The sides of the board will be seen as your
                 color. But, if any of the characters after the ? is behind the
                 sides of the board, the computer will not do anything with the
                 current point (ignores it) and checks out the next point.

                 Good examples are zgi/1abcdefhjklnoz, zgi/1abdefhjklmnoz,
                 zgq/1abcfhklpruvwz, zgq/1abcfhlmpruvwz, zgi/1bcdefhjklmnz,
                 zgi/1abcdfhjlmnoz, zgq/1abfhklmprvwz, zgq/1bcfhklmpruvz,
                 zgm/1abfhklnqrsz, zgm/1abcfhilnrsz, zgm/1bcfhiklnqrz,
                 zhl/1cdgikmnpqrz, zhl/1bcdfgikmpqz and zhl/1bcfgikmnqrz
g<C/N>?<a/u/r/l> Check your last move and after that all points on the board
                 with your color (C) or your opponent's last move and after
                 that all opponent's points on the board (N) if they are part
                 of a group containing ? or more stones. If so, make your next
                 move above this point (a), under this point (u), at the right
                 of this point (r) or at the left of this point (l). a, u, r
                 and l may be used together. If you do so, all points will be
                 tried after each other, as long as no move can be made.
s<C/N>?<a/u/r/l> Check all points on the board with your color (C) or your
                 opponent's color (N) for ? sides occupied. When found, make
                 your next move above this point (a), under this point (u),
                 at the right of this point (r) or at the left of this point
                 (l). Sides occupied returns the total of 'left occupied' (1),
                 'right occupied' (2), 'above occupied' (4) and 'under
                 occupied' (8). This way you can see which sides are free and
                 occupied. a, u, r and l may be used together. If you do so,
                 one of them will be chosen and used randomly.
l<a/u/r/l><C/N>  Make next move above (a), under (u), at the right (r) or at
                 the left (l) of your last move (C) or your opponent's last
                 move (N). a, u, r and l may be used together. If you do so,
                 one of them will be chosen and used randomly.
*?*              Do ? only if you already made at least 25 moves during the
                 game.
!?!              Do ? only if not in own territory (unless this is really
                 needed to stop an attack by the opponent).
.?.              Do ? only if not in opponent's territory.
%?%              Do ? in 50% of all cases.
+?+              Do ? in 10% of all cases.
#?#              ? is comment.
$?$              Do not make the next move during ? if this would be on a point
                 somewhere on the sides of the board.
E                Pass if the opponent just passed and your score is higher.
f                Make your next move on a random free point, which touches your
                 color diagonally just once.
F                Make next move on a random free point. All sides, also
                 diagonally, are unoccupied.
M                Make next move on a random point, that touches at least one
                 point with your color.
m                Make next move on a diagonal side of a stone of your color,
                 that touches the opponent's color on one (or more) side and
                 doesn't touch a stone of your color anywhere (not even
                 diagonally).
X                Make next move on a random free point, that is on (or on the
                 sides) of the square formed by the dots on the board.
P                Pass.

- [5 FEEDBACK] ----------------------------------------------------------------

If gtkgo crashes, gets compilation errors or crashes while building, does not
work as the documentation says or just won't work like you want it to, send an
e-mail to <nlmdejonge@gmail.com>. Make sure to describe exactly what actions
triggered the bug and the precise symptoms of the bug.

For Linux also include: 'uname -a', 'gcc -v',
'pkg-config --modversion gtk+-3.0' and 'gtkgo --version'.

For Windows also include: Windows version, processor type, amount of available
memory and 'gtkgo --version'.

To debug (GTK+ elements of) the application yourself, you can use:
$ GTK_DEBUG=interactive ./gtkgo --debug=1

- [6 TODO] --------------------------------------------------------------------

Allow board sizes other than 19x19.
Also allow selecting dead stones by group.
More Internet features, such as listing players.
Better go-computer scripts.
Go Text Protocol.
Somehow (cross) compile a Windows executable.
