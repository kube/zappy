# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/27 17:20:07 by vdefilip          #+#    #+#              #
#    Updated: 2014/05/27 17:20:07 by vdefilip         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=serveur
VERSION=1.0.6
CFLAGS=-Wall -Werror -Wextra -g
INCLUDES=-I ../libft/includes
LIBS=-L ../libft -l ft

SRC=client_handler.c \
	fd.c \
	server.c \
	try.c \

OBJ=$(SRC:.c=.o)

all: build $(NAME) finish

build:
	@($(MAKE) -C ../libft)

$(NAME): $(OBJ) ../libft/libft.a
	gcc $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBS)

%.o: %.c server.h ../libft/includes
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@(rm -rf $(OBJ))

fclean: clean
	@(rm -rf $(NAME))
	@($(MAKE) -C ../libft fclean)

re: fclean all

v:
	@(echo "version: $(VERSION)")

finish:
	@(echo "[\033[32m$(NAME)\033[00m]")

.PHONY: all build clean fclean re v

