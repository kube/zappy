# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/17 14:16:05 by vdefilip          #+#    #+#              #
#    Updated: 2014/05/27 18:01:44 by vdefilip         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_p
VERSION=1.0.0

OBJ=$(SRC:.c=.o)

all: $(NAME)

$(NAME): serveur gfx client

gfx:
	@cd gfx && npm install

client:
	@cd client && npm install

serveur:
	make -C ./serveur

clean:
	@($(MAKE) -C ./serveur clean)

fclean:
	make -C ./serveur fclean
	@cd client && npm run clean
	@cd gfx && npm run clean

re: fclean all

.PHONY: all build clean serveur client gfx fclean re
