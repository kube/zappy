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

$(NAME): serveur

serveur:
	@($(MAKE) -C ./srv)

clean:
	@($(MAKE) -C ./srv clean)

fclean:
	@($(MAKE) -C ./srv fclean)
	@(rm -rf serveur)

re: fclean all


.PHONY: all build clean fclean re v

