# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/17 14:16:05 by vdefilip          #+#    #+#              #
#    Updated: 2014/06/27 01:23:25 by cfeijoo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=zappy
VERSION=1.0.0

OBJ=$(SRC:.c=.o)

all: $(NAME)

$(NAME): serveur gfx client

gfx:
	@cd ./src/gfx && npm install
	@echo "open src/gfx/Visualizer.app" > gfx
	@chmod +x gfx

client:
	@cd ./src/client && npm install
	@rm -f client
	@ln -s ./src/client/client

serveur:
	make -C ./src/serveur
	@rm -f serveur
	@ln -s ./src/serveur/serveur

clean:
	@($(MAKE) -C ./src/serveur clean)

fclean:
	@($(MAKE) -C ./src/serveur fclean)
	@cd ./src/client && npm run clean
	@cd ./src/gfx && npm run clean
	@rm -f serveur client gfx

re: fclean all

.PHONY: all build clean serveur client gfx fclean re
