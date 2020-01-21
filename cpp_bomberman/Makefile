##
## Makefile for bomberman in /home/pridea_v/rendu/mybomberman
##
## Made by virgile prideaux
## Login   <pridea_v@epitech.net>
##
## Started on  Wed Apr 30 13:25:35 2014 virgile prideaux
## Last update Sun Jun 15 15:33:08 2014 artige_x
##

CXX		=	g++ -O2

CXXFLAGS	+=	-Wall -Wextra -ILibBomberman_linux_x64/includes -I. -Imap -Iaudio
DEBUG		=	0
ifeq ($(DEBUG), 1)
  CXXFLAGS	+=	-g -O0
endif

LDFLAGS		+=	-lGL -ldl -lrt -lpthread
LDFLAGS		+=	-LLibBomberman_linux_x64/libs/ -Wl,-rpath,LibBomberman_linux_x64/libs/ -lgdl_gl -lGLEW -lfbxsdk -lSDL2 -Laudio -Wl,-rpath,audio -lfmodex64

NAME		=	bomberman

SRCS		=	main.cpp \
			Coord3.cpp \
			Engine.cpp \
			Plan.cpp \
			Cube.cpp \
			Menu.cpp \
			Hitbox.cpp \
			map/AElement.cpp \
			map/AI.cpp \
			map/Bitmap.cpp \
			map/Bomb.cpp \
			map/Bonus.cpp \
			map/Case.cpp \
			map/Character.cpp \
			map/Color.cpp \
			map/Explosion.cpp \
			map/Invalid.cpp \
			map/Line.cpp \
			map/Map.cpp \
			map/Wall.cpp \
			audio/Audio.cpp


OBJS		=	$(SRCS:.cpp=.o)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
