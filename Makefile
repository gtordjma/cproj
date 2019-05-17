<<<<<<< HEAD
<<<<<<< HEAD
NAME	=	cimp
LIBS  	=	-lSDL2 -lSDL2_image
SRC		= misengris.c  
=======
NAME	=	sauvegarde
LIBS  	=	-lSDL2 -lSDL2_image
SRC		= cimp.c sauvegarde.c
>>>>>>> sauvegarde
OBJ		=	$(SRC:.c=.o)
FLAGS	=	-Wall -Wextra -Werror
CC		=	gcc
=======
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
>>>>>>> b37bee0d6b6160c226f8ffe1a4eb5f931a38594b

%.o: %.c
		$(CC) $(CFLAGS) -I. -o $@ -c $? 

all: $(NAME)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all
