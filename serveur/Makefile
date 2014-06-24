# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/06/24 18:46:26 by vdefilip          #+#    #+#              #
#    Updated: 2014/06/24 18:46:26 by vdefilip         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=serveur
VERSION=1.2.8
CFLAGS=-Wall -Werror -Wextra -g
INCLUDES=-I ./libft/includes
LIBS=-L ./libft -l ft

SRC=bot.c \
	bot_parse.c \
	broadcast.c \
	check_end.c \
	client_handler.c \
	connect_bot.c \
	connection.c \
	dir.c \
	expulse.c \
	fd.c \
	fork.c \
	game.c \
	get_bot_by_id_arg.c \
	gfx.c \
	gfx_bct.c \
	gfx_custom.c \
	gfx_ebo.c \
	gfx_edi.c \
	gfx_eht.c \
	gfx_enw.c \
	gfx_mct.c \
	gfx_msz.c \
	gfx_parse.c \
	gfx_pbc.c \
	gfx_pdi.c \
	gfx_pdr.c \
	gfx_pex.c \
	gfx_pfk.c \
	gfx_pgt.c \
	gfx_pic.c \
	gfx_pie.c \
	gfx_pin.c \
	gfx_plv.c \
	gfx_pnw.c \
	gfx_ppo.c \
	gfx_sbp.c \
	gfx_seg.c \
	gfx_sgt.c \
	gfx_smg.c \
	gfx_sst.c \
	gfx_suc.c \
	gfx_tna.c \
	incantation.c \
	incantation_req.c \
	inventory.c \
	look.c \
	move.c \
	obj.c \
	opt.c \
	put.c \
	rand.c \
	send_dimension.c \
	send_nbr.c \
	server.c \
	take.c \
	team.c \
	timer.c \
	try.c \

OBJ=$(SRC:.c=.o)

all: build $(NAME) finish

build:
	@($(MAKE) -C ./libft)

$(NAME): $(OBJ) ./libft/libft.a
	gcc $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBS)

%.o: %.c server.h ./libft/includes
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

