/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 11:02:20 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/20 15:02:00 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include "server.h"

void			timer(t_env *e, t_bot *bot)
{
	struct timeval			cur;
	t_ulong					diff;
	t_ulong					unit;
	t_bot					*egg;

	if (bot->life_unit <= 0)
		return ;
	gettimeofday(&cur, NULL);
	diff = (t_ulong)(cur.tv_sec - bot->time.tv_sec) * 1000000UL;
	diff += (t_ulong)(cur.tv_usec - bot->time.tv_usec);
	bot->time = cur;
	bot->timer += diff;
	unit = ((bot->timer * e->opt.t) / 1000000UL);
	bot->timer = bot->timer - (unit * 1000000UL / e->opt.t);
	if (bot->status != STATUS_EGG && (bot->life_unit -= unit) <= 0)
	{
		if (bot->parent == NULL)
		{
			printf("BOT #%d is dead\n", bot->id);
			notify_all_gfx_pdi(e, bot);
		}
		else
		{
			printf("EGG #%d is dead\n", bot->id);
			notify_all_gfx_edi(e, bot);
		}
		ft_strcat(e->fds[bot->fd].buf_write, "mort\n");
	}
	if (bot->action_timer > 0 && (bot->action_timer -= unit) <= 0)
	{
		if (bot->status == STATUS_FORK)
		{
			bot->status = STATUS_NONE;
			egg = bot_new(bot->team);
			egg->sq = bot->sq;
			move(e, egg, egg->sq);
			gettimeofday(&egg->time, NULL);
			egg->status = STATUS_EGG;
			egg->parent = bot;
			ft_lst_pushend(bot->team->egg, egg);
			notify_all_gfx_enw(e, bot, egg);
			egg->action_timer = EGG_TIME;
		}
		else if (bot->status == STATUS_EGG)
		{
			bot->status = STATUS_NONE;
			notify_all_gfx_eht(e, bot);
		}
		bot->action_timer = -1;
		ft_strcat(e->fds[bot->fd].buf_write, bot->buf_action);
		ft_bzero(bot->buf_action, BUF_SIZE);
	}
}
