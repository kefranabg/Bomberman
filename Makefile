##
## Makefile for Makefile in /home/chauch_a/rendu/cpp_bomberman
## 
## Made by CHAUCHET Alan
## Login   <chauch_a@epitech.net>
## 
## Started on  Tue May 27 15:45:45 2014 CHAUCHET Alan
## Last update Sat Nov  1 12:07:55 2014 abgral_f
##
##

NAME		=	bomber

PATH1		=	src/

PATH2		=	$(PATH1)Thread/

PATH3		=	$(PATH1)Game/

PATH4		=	$(PATH1)GUI/

PATH5		=	$(PATH1)Menu/

PATH_I		=	inc/

SRC		=	$(PATH1)main.cpp			\
			$(PATH2)Thread.cpp			\
			$(PATH2)Mutex.cpp			\
			$(PATH2)Cond.cpp			\
			$(PATH3)APlayer.cpp			\
			$(PATH3)Player.cpp			\
			$(PATH3)IA.cpp				\
			$(PATH3)Box.cpp				\
			$(PATH3)Map.cpp				\
			$(PATH3)Bomb.cpp			\
			$(PATH3)BomberGame.cpp			\
			$(PATH3)Key.cpp				\
			$(PATH3)Rand.cpp			\
			$(PATH3)ALexer.cpp			\
			$(PATH3)LexerKey.cpp			\
			$(PATH3)AParser.cpp			\
			$(PATH3)ParserKey.cpp			\
			$(PATH3)LexerSave.cpp			\
			$(PATH3)ParserSave.cpp			\
			$(PATH3)LexerScore.cpp			\
			$(PATH3)ParserScore.cpp			\
			$(PATH3)ListFiles.cpp			\
			$(PATH4)GetGDL.cpp			\
			$(PATH4)Window.cpp			\
			$(PATH4)AGUI.cpp			\
			$(PATH4)MapGUI.cpp			\
			$(PATH4)AObject.cpp			\
			$(PATH4)WallIGUI.cpp			\
			$(PATH4)WallDGUI.cpp			\
			$(PATH4)FloorGUI.cpp			\
			$(PATH4)PlayerGUI.cpp			\
			$(PATH4)EnnemyGUI.cpp			\
			$(PATH4)BombGUI.cpp			\
			$(PATH4)FireGUI.cpp			\
			$(PATH4)BonusGUI.cpp			\
			$(PATH4)MenuGUI.cpp			\
			$(PATH4)Sound.cpp			\
			$(PATH4)Cinematic.cpp			\
			$(PATH4)TextGUI.cpp			\
			$(PATH5)TextBoxButton.cpp		\
			$(PATH5)NbListButton.cpp      		\
			$(PATH5)TextListButton.cpp    		\
			$(PATH5)AListButton.cpp       		\
			$(PATH5)AButton.cpp           		\
			$(PATH5)NormalButton.cpp      		\
			$(PATH5)Menu.cpp              		\
			$(PATH5)Text.cpp              		\

OBJ		=	$(SRC:.cpp=.o)

GDL		=	LibBomberman_linux_x64/

LIB		=	-lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2 -lpthread -lSDL_mixer -lfmodex64

CPPFLAGS	=	-W -Wall -Werror -Wextra -I $(PATH_I) -I $(GDL)includes/

all:			$(NAME)

$(NAME):		$(OBJ)
			g++ -o $(NAME) $(OBJ) -L $(GDL)libs/ $(LIB) -D_REENTRANT

clean:
			rm -f $(OBJ)

fclean:			clean
			rm -f $(NAME)

re:			fclean all

debug:			CPPFLAGS += -g

debug:			re
