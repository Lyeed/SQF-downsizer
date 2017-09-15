NAME=		sqf_cleaner

OBJ=		$(SRC:.cpp=.o)

SRC=		main.cpp

CPPFLAGS=	-std=c++11

all:		$(NAME)

$(NAME):	$(OBJ)
			g++ -o $(NAME) $(OBJ) $(LIB)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
