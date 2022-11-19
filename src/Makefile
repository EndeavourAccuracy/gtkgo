# Makefile for gtkgo 0.0.12 by Norbert de Jonge
#
# cppcheck --language=c --std=c99 --verbose *.c
# Also try CC=clang.
#
GAME_GTK=3.24.20
GAME_GST=1.16.3
USER_GTK=$(shell echo `pkg-config --modversion gtk+-3.0`)
USER_GST=$(shell echo `pkg-config --modversion gstreamer-1.0`)
ifneq ($(GAME_GTK),$(USER_GTK))
	WARNGTK=WARNING: Your GTK+ \($(USER_GTK)\) does not equal $(GAME_GTK).
endif
ifneq ($(GAME_GST),$(USER_GST))
	WARNGST=WARNING: Your GStreamer \($(USER_GST)\) does not equal $(GAME_GST).
endif

CC=gcc
CFLAGS=`pkg-config gtk+-3.0 --cflags` `pkg-config gstreamer-1.0 --cflags` -O2 -Wno-unused-result -std=c99 -g -pedantic -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -DPKGDATADIR=\"${pkgdatadir}\" -D_REENTRANT
LIBS=`pkg-config gtk+-3.0 --libs` `pkg-config gstreamer-1.0 --libs` -lm
OUT=gtkgo
OBJS=main.o About.o AskSave.o ChangePixmap.o ChangePoint.o ChangeSkin.o CheckSides.o Computer.o Connect.o DeadStones.o DestroyMessage.o DestroyOptions.o DestroySaveDialog.o DestroySkins.o DestroyTheComputer.o DestroyYesNo.o DoHandicap.o EnableComp.o EndGame.o FreePlace.o Handicap.o Help.o Hint.o Human.o InternetGo.o JudgeBoard.o Latest.o MainWindow.o MakeMove.o Message.o Modulo.o MyLand.o NotSuicide.o Options.o OptionsX.o Pass.o PixmapOnPoint.o Play.o PointToPlace.o Quit.o ReallyQuit.o ReallyReStart.o ReceiveData.o ReSize.o ReStart.o SaveDialog.o SaveSGF.o ScoreBlack.o ScoreWhite.o SendData.o SetTimeLimit.o Skin.o Sound.o StatusBar.o TheComputer.o TimeLimit.o Tooltips.o Undo.o Where.o WouldSurround.o

all: $(OBJS)
	@echo $(WARNGTK)
	@echo $(WARNGST)
	$(CC) $(INCLUDES) $(CFLAGS) -o $(OUT) $(OBJS) $(LIBS)
	mv $(OUT) ..
	@echo
	@echo The executable \(\"$(OUT)\"\) is in the parent directory.
	@echo

clean:
	rm *.o
