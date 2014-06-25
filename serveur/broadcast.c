/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 12:15:09 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 12:05:10 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int		calcul_north_dir(int *diff)
{
	if (diff[X] == 0 && diff[Y] == 0)
		return (0);
	if (ABS(diff[X]) > ABS(diff[Y]) * 2)
	{
		if (diff[X] < 0)
			return (3);
		return (7);
	}
	else if (ABS(diff[Y]) > ABS(diff[X]) * 2)
	{
		if (diff[Y] < 0)
			return (1);
		return (5);
	}
	else if (diff[X] < 0)
	{
		if (diff[Y] < 0)
			return (2);
		return (4);
	}
	if (diff[Y] < 0)
		return (8);
	return (6);
}

static int		get_sound_dir(t_env *e, t_bot *bot_dst, t_bot *bot_src)
{
	int		diff[2];
	int		dir;

	diff[X] = (bot_src->sq % e->opt.width) - (bot_dst->sq % e->opt.width);
	if (ABS(diff[X]) > e->opt.width / 2)
		diff[X] = (diff[X] >= 0) ? (e->opt.width - ABS(diff[X])) * -1
			: (e->opt.width - ABS(diff[X]));
	diff[Y] = (bot_src->sq / e->opt.width) - (bot_dst->sq / e->opt.width);
	if (ABS(diff[Y]) > e->opt.height / 2)
		diff[Y] = (diff[Y] >= 0) ? (e->opt.height - ABS(diff[Y])) * -1
		: (e->opt.height - ABS(diff[Y]));
	if ((dir = calcul_north_dir(diff)) == 0)
		return (0);
	if (bot_dst->dir == WEST)
		dir = (dir <= 2) ? dir + 6 : dir - 2;
	else if (bot_dst->dir == SOUTH)
		dir = (dir >= 5) ? dir - 4 : dir + 4;
	else if (bot_dst->dir == EAST)
		dir = (dir >= 7) ? dir - 6 : dir + 2;
	return (dir);
}

void			broadcast(t_env *e, t_bot *bot, char *msg)
{
	t_iterator		iter_t;
	t_iterator		iter_b;
	t_team			*t;
	t_bot			*b;
	char			buf[128];

	bot->action_timer = BROADCAST_TIME;
	iter_t = NULL;
	while ((t = (t_team *)ft_lst_iter_next_content(e->team, &iter_t)))
	{
		iter_b = NULL;
		while ((b = (t_bot *)ft_lst_iter_next_content(t->connected, &iter_b)))
		{
			if (b != bot)
			{
				b->action_timer = BROADCAST_TIME;
				sprintf(buf, "message %d,%s\n", get_sound_dir(e, b, bot), msg);
				buf_load(b->buf_action, buf);
			}
		}
	}
	buf_load(bot->buf_action, "ok\n");
}
