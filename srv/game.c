/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 13:05:23 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/04 23:22:38 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "server.h"

static void			print_board(t_env *e)
{
	t_iterator		iter;
	int				i;
	t_bot			*bot;
	t_obj			*obj;
	int				rock[OBJ_NB];

	i = 0;
	printf("[ SQ ] : FOOD R0 R1 R2 R3 R4 R5 BOTS ...");
	while (i < e->n_sq)
	{
		ft_bzero(rock, sizeof(int) * OBJ_NB);
		iter = NULL;
		while ((obj = (t_obj *)ft_lst_iter_next_content(e->board[i].obj, &iter)))
			rock[obj->type]++;
		printf("[%4d] : ", i);
		printf("%4d ", rock[0]);
		printf("%2d ", rock[1]);
		printf("%2d ", rock[2]);
		printf("%2d ", rock[3]);
		printf("%2d ", rock[4]);
		printf("%2d ", rock[5]);
		printf("%2d ", rock[6]);
		iter = NULL;
		while ((bot = (t_bot *)ft_lst_iter_next_content(e->board[i].bot, &iter)))
			printf("#%d ", bot->fd);
		printf("\n");
		i++;
	}
}

static void			board_fill(t_env *e)
{
	int		max_bot;
	int		nb_food;
	int		nb_rock;
	int		i;
	int		tmp;

	max_bot = e->opt.limit * e->opt.team_name->len;
	nb_food = max_bot * 2;
	i = 0;
	while (i < nb_food)
	{
		ft_lst_pushend(e->board[sq_rand(e)].obj, obj_new(OBJ_FOOD));
		i++;
	}
	i = 1;
	while (i < OBJ_NB)
	{
		nb_rock = (i == 1 ? 5 : nb_rock * 2);
		tmp = nb_rock;
		while (tmp--)
			ft_lst_pushend(e->board[sq_rand(e)].obj, obj_new(i));
		i++;
	}
}

static void			board_create(t_env *e)
{
	int		size;
	int		i;

	size = sizeof(t_sq) * e->n_sq;
	e->board = (t_sq *)try_void(ft_memalloc(size), NULL, "malloc");
	i = 0;
	while (i < e->n_sq)
	{
		e->board[i].obj = ft_lst_new(NULL);
		e->board[i].bot = ft_lst_new(NULL);
		i++;
	}
	board_fill(e);
	print_board(e);
}

void				init_game(t_env *e)
{
	t_iterator		iter;
	char			*name;
	t_team			*team;

	e->n_sq = e->opt.height * e->opt.width;
	e->bot_lst = ft_lst_new(NULL);
	e->gfx_lst = ft_lst_new(NULL);
	e->team = ft_lst_new(NULL);
	iter = NULL;
	while ((name = (char *)ft_lst_iter_next_content(e->opt.team_name, &iter)))
	{
		team = (t_team *)try_void(malloc(sizeof(*team)), NULL, "malloc");
		team->name = name;
		team->limit = e->opt.limit;
		team->nb_bot = 0;
		ft_lst_pushend(e->team, team);
	}
	board_create(e);
}
