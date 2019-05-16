NAME	=	afficher
LIBS  	=	-lSDL2 -lSDL2_image
SRC		= main.c afficher.c
OBJ		=	$(SRC:.c=.o)
FLAGS	=	-Wall -Wextra -Werror
CC		=	gcc

%.o: %.c
	@$(CC) -I ./includes -o $@ -c $?

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRC) -I/usr/local/include -L/usr/local/lib $(LIBS) -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY:
	all clean fclean re
