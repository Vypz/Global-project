NAME		=	gomoku

CXX		=	g++

CPPFLAGS	+=	-Wall -Wextra -Iinclude -Iia -Iarbitre -Igui -std=c++11 -O3
ifeq ($(DEBUG), 1)
  CPPFLAGS	+=	-O0 -g -pg
endif
LDFLAGS		+=	-Llib -lsfml-system -lsfml-graphics -lsfml-window
LDFLAGS		+=	-Wl,-rpath lib

SRCS		=	main.cpp \
			gui/Gui.cpp \
			gui/GameScene.cpp \
			gui/Menu.cpp \
			gui/Goban.cpp \
			gui/Rules.cpp \
			arbitre/Arbitre.cpp \
			ia/Bot.cpp


OBJS		=	$(SRCS:.cpp=.o)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(CPPFLAGS) $(LDFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
