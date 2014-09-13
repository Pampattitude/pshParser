PATH_BIN =	bin
NAME =		parser

SRC =		src/Main.cpp \
		src/Lexer.cpp
OBJ =		$(SRC:.cpp=.o)

CXX =		g++
CXXFLAGS +=	-std=c++11
CXXFLAGS +=	-Wall -Wextra
CXXFLAGS +=	-I inc/

LDFLAGS +=	-L /usr/lib

$(NAME):	$(OBJ)
		@mkdir -p $(PATH_BIN)
		$(CXX) -o $(PATH_BIN)/$(NAME) $(OBJ) $(LDFLAGS)

all:		$(NAME)

debug:		CXXFLAGS += -O0 -g3 -DDEBUG
debug:		$(NAME)

thin:		CXXFLAGS += -Os
thin:		all

clean:
		@rm -vf $(OBJ)

fclean:		clean
		@rm -Rvf $(PATH_BIN)

re:		fclean all

deploy:		CXXFLAGS += -O3
deploy:		re

.PHONY:		all debug thin clean fclean re deploy
