NAME=		downsize

OBJ=		$(SRC:.cpp=.o)

SRC=		main.cpp \
			src/trim.cpp \
			src/downsize.cpp

CPPFLAGS=	-Iincludes -W -Wall -Wextra -Werror -Werror-implicit-function-declaration -Wparentheses -Wreturn-type -Wuninitialized -std=c++17

all:		$(NAME)

$(NAME):	$(OBJ)
			g++ -o $(NAME) $(OBJ)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
