/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 11:07:55 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/17 16:18:41 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "server.h"

void			move(t_env *e, t_bot *bot, int sq)
{
	t_iterator		itr;
	t_bot			*b;
	int				old;

	old = bot->sq;
	if (old != -1)
	{
		itr = NULL;
		while ((b = (t_bot *)ft_lst_iter_next_content(e->board[old].bot, &itr)))
		{
			if (b == bot)
				ft_lst_del_atom(e->board[old].bot, itr, NULL);
		}
	}
	ft_lst_pushend(e->board[sq].bot, bot);
	bot->sq = sq;
}

void			turn_left(t_env *e, t_bot *bot)
{
	(void)e;
	bot->dir--;
	if (bot->dir == 0)
		bot->dir = 4;
	printf("Bot client #%d turn left\n", bot->fd);
	ft_strcat(e->fds[bot->fd].buf_write, "ok\n");
}

void			turn_right(t_env *e, t_bot *bot)
{
	(void)e;
	bot->dir++;
	if (bot->dir == 5)
		bot->dir = 1;
	printf("Bot client #%d turn right\n", bot->fd);
	ft_strcat(e->fds[bot->fd].buf_write, "ok\n");
}

void			step(t_env *e, t_bot *bot)
{
	int			sq;

	if (bot->dir == EAST)
		sq = get_east(e, bot->sq);
	else if (bot->dir == WEST)
		sq = get_west(e, bot->sq);
	else if (bot->dir == NORTH)
		sq = get_north(e, bot->sq);
	else
		sq = get_south(e, bot->sq);
	move(e, bot, sq);
	printf("Bot client #%d step\n", bot->fd);
	ft_strcat(e->fds[bot->fd].buf_write, "ok\n");
}
