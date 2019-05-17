NAME=cimp
CC=gcc
INC=-I include -Llib -lSDL2-2.0.0 -lSDL2_image -lreadline
CFLAGS=-Wall -Werror
SRC = main.c parser.c completion.c ft_strsplit.c afficher.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(INC)

%.o: %.c
		$(CC) -I. -o $@ -c $? $(CFLAGS)

all: $(NAME)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all
