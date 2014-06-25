/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expulse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 12:19:39 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 12:25:01 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int		get_step_sq(t_env *e, t_bot *bot)
{
	if (bot->dir == EAST)
		return (get_east(e, bot->sq));
	else if (bot->dir == WEST)
		return (get_west(e, bot->sq));
	else if (bot->dir == NORTH)
		return (get_north(e, bot->sq));
	else
		return (get_south(e, bot->sq));
}

void			expulse(t_env *e, t_bot *bot)
{
	t_iterator		itr;
	t_bot			*b;
	char			buf[128];
	int				ret;

	bot->action_timer = EXPULSE_TIME;
	notify_all_gfx_pex(e, bot);
	ret = 0;
	itr = NULL;
	while ((b = (t_bot *)ft_lst_iter_next_content(e->board[bot->sq].bot, &itr)))
	{
		if (b != bot && b->status == STATUS_NONE)
		{
			ret = 1;
			move(e, b, get_step_sq(e, bot));
			notify_all_gfx_ppo(e, bot);
			sprintf(buf, "deplacement %d\n", (bot->dir + 2) % 4);
			buf_load(e->fds[b->fd].buf_write, buf);
		}
	}
	if (ret == 0)
		buf_load(bot->buf_action, "ko\n");
	else
		buf_load(bot->buf_action, "ok\n");
}
