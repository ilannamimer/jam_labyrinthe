##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##


SRC     =       src/main.cpp					\
				src/labyrinthe.cpp				\

CXX      =       g++

OBJ     =       $(SRC:.cpp=.o)

NAME    =       Jam

CXXFLAGS  =       -Wall -Wextra

CPPFLAGS        =       -I include -lsfml-graphics -lsfml-window -lsfml-system

all:            $(NAME)

$(NAME):    $(OBJ)
			$(CXX) $(OBJ) -o $(NAME) $(CPPFLAGS)

clean:	
		$(RM) $(OBJ)

fclean:     clean
		$(RM) $(NAME)

re:         fclean all

tests_run:
		$(CC) $(SRC) --coverage -lcriterion -o $(TNAME)

.PHONY:         all clean fclean re tests_run
