##
## Makefile for Makefile in /home/pinche_j
## 
## Made by julien pinchelimouroux
## Login   <pinche_j@epitech.net>
## 
## Started on  Wed Nov  4 18:37:27 2015 julien pinchelimouroux
## Last update Wed Mar  9 19:18:24 2016 Adrien Chaix
##

CC	=	gcc

NAME		=plasma

CFLAGS          =       -Iinclude \
			-I/home/${USER}/.froot/include \
                        -L/home/${USER}/.froot/lib -L.\
			-I/usr/local/include -lfmodex64 -lSDL \
			-llapin -lsfml-audio -lsfml-graphics \
                        -lsfml-window -lsfml-system -lstdc++ -ldl -lm

LIB		= -llapin \
		-lsfml-audio \
		-lsfml-graphics \
		-lsfml-window \
		-lsfml-system \
		-lstdc++ -ldl \
		-lm \
		-Lliblapin -Iliblapin

SRCS		= plasma.c \
		tinyfiledialogs.c \
		set_plasma.c\
		palette_plasma.c\
		get_plasma.c


OBJS		= $(SRCS:.c=.o)

all:	$(NAME)

$(NAME):$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS) $(LIB)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
