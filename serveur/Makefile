# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/06/20 10:53:12 by vdefilip          #+#    #+#              #
#    Updated: 2014/06/20 15:17:12 by vdefilip         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=serveur
VERSION=1.1.8
CFLAGS=-Wall -Werror -Wextra -g
INCLUDES=-I ./libft/includes
LIBS=-L ./libft -l ft

SRC=bot.c \
	client_handler.c \
	connection.c \
	dir.c \
	fd.c \
	game.c \
	gfx.c \
	gfx_msg.c \
	look.c \
	move.c \
	obj.c \
	opt.c \
	parse_request.c \
	rand.c \
	server.c \
	timer.c \
	try.c \

OBJ=$(SRC:.c=.o)

all: build $(NAME) finish

build:
	@($(MAKE) -C ./libft)

$(NAME): $(OBJ) ./libft/libft.a
	gcc $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBS)

%.o: %.c requests.h server.h ./libft/includes
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@(rm -rf $(OBJ))

fclean: clean
	@(rm -rf $(NAME))
	@($(MAKE) -C ./libft fclean)

re: fclean all

v:
	@(echo "version: $(VERSION)")

finish:
	@(echo "[\033[32m$(NAME)\033[00m]")

.PHONY: all build clean fclean re v

