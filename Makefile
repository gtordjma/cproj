NAME=cimp
CC=gcc
INC=-I include -Llib -lSDL2-2.0.0 -lSDL2_image -lreadline
CFLAGS=-Wall -Werror
SRC = cimp.c parser.c completion.c ft_strsplit.c afficher.c \
		rotation.c paint.c symetrie_horizontale.c symetrie_verticale.c\
		remplissage.c save.c selection.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(INC)

%.o: %.c
		$(CC) $(CFLAGS) -I. -o $@ -c $? 

all: $(NAME)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all