##
## EPITECH PROJECT, 2019
## arp
## File description:
## Makefile
##

all	:	$(NAME)

.PHONY : all

NAME	=	myftp


CFLAGS	=	-Wall -Wextra -pedantic

SRC	=	./src/main.c	\
		./src/socket.c	\
		./src/victim.c

OBJ	=	$(SRC:.c=.o)


$(NAME)	:	$(OBJ)
		gcc -o $(NAME) $(CFLAGS) $(OBJ)

all	:	$(NAME)

clean	:
		rm -f $(OBJ)

fclean	:	clean
		rm -f $(NAME)

re	: fclean all
