# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/24 17:00:56 by vdefilip          #+#    #+#              #
#    Updated: 2014/05/24 17:00:56 by vdefilip         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
VERSION=1.1.2
CFLAGS=-Wall -Werror -Wextra -g
INCLUDES=-I ./includes

SRC=ft_atod.c \
	ft_atof.c \
	ft_atoi.c \
	ft_atom_new.c \
	ft_atomp_new.c \
	ft_bzero.c \
	ft_chr_to_str.c \
	ft_exit.c \
	ft_free_strtab.c \
	ft_get_next_line.c \
	ft_getfilename.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_islower.c \
	ft_isnumber.c \
	ft_isprint.c \
	ft_isupper.c \
	ft_iswhitespace.c \
	ft_itoa.c \
	ft_itoa_base.c \
	ft_itoa_base_fitted.c \
	ft_litoa_base.c \
	ft_loadcolor.c \
	ft_loadcolor2.c \
	ft_lst_atom_index.c \
	ft_lst_cpy.c \
	ft_lst_del.c \
	ft_lst_del_atom.c \
	ft_lst_iter.c \
	ft_lst_iter_atom.c \
	ft_lst_iter_next_content.c \
	ft_lst_iter_rev.c \
	ft_lst_new.c \
	ft_lst_next_content.c \
	ft_lst_pop.c \
	ft_lst_popend.c \
	ft_lst_prev_content.c \
	ft_lst_push.c \
	ft_lst_push_after_atom.c \
	ft_lst_push_after_curr.c \
	ft_lst_push_before_atom.c \
	ft_lst_push_before_curr.c \
	ft_lst_pushend.c \
	ft_lst_qsort.c \
	ft_lst_reset_curr.c \
	ft_lst_swap_atom.c \
	ft_lst_to_tab.c \
	ft_memalloc.c \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memdel.c \
	ft_memdup.c \
	ft_memjoin_free.c \
	ft_memmove.c \
	ft_memset.c \
	ft_power.c \
	ft_putchar.c \
	ft_putchar_fd.c \
	ft_putendl.c \
	ft_putendl_fd.c \
	ft_putnbr.c \
	ft_putnbr_fd.c \
	ft_putnspace.c \
	ft_putptr.c \
	ft_putstr.c \
	ft_putstr_fd.c \
	ft_qsort.c \
	ft_secure_fork.c \
	ft_secure_pipe.c \
	ft_strcat.c \
	ft_strchr.c \
	ft_strclr.c \
	ft_strcmp.c \
	ft_strcpy.c \
	ft_strdel.c \
	ft_strdup.c \
	ft_strdupchr.c \
	ft_strequ.c \
	ft_strerror.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strjoin_char.c \
	ft_strjoin_sep.c \
	ft_strlcat.c \
	ft_strlen.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_strmcat.c \
	ft_strmjoin.c \
	ft_strncat.c \
	ft_strncmp.c \
	ft_strncpy.c \
	ft_strndup.c \
	ft_strnequ.c \
	ft_strnew.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strsplit.c \
	ft_strsplit_raw.c \
	ft_strstr.c \
	ft_strsub.c \
	ft_strtabcat.c \
	ft_strtabjoin.c \
	ft_strtocolor.c \
	ft_strtrim.c \
	ft_swap.c \
	ft_tabrev.c \
	ft_timespeccmp.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_warning.c \
	hash_tab_color.c \

OBJ=$(SRC:.c=.o)

all: $(NAME) finish

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

%.o: %.c ./includes
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@(rm -rf $(OBJ))

fclean: clean
	@(rm -rf $(NAME))

re: fclean all

v:
	@(echo "version: $(VERSION)")

finish:
	@(echo "[\033[32m$(NAME)\033[00m]")

.PHONY: all build clean fclean re v

