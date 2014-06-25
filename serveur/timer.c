/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 11:02:20 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 12:53:22 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int			check_life(t_env *e, t_bot *bot, int unit)
{
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
		buf_load(e->fds[bot->fd].buf_write, "mort\n");
		return (-1);
	}
	return (0);
}

static void			handle_status_fork_and_egg(t_env *e, t_bot *bot)
{
	t_bot			*egg;

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
}

static void			handle_status_incantation(t_env *e, t_bot *bot)
{
	int				i;

	bot->status = STATUS_NONE;
	bot->level++;
	if (bot->incant.parent != NULL)
		bot->incant.parent = NULL;
	else
	{
		notify_all_gfx_incant(e, bot, 1);
		move_rocks_after_incant(e, bot);
		i = 0;
		while (i < 7)
			ft_lst_del(bot->incant.req[i++], NULL);
	}
}

void				timer(t_env *e, t_bot *bot)
{
	struct timeval			cur;
	t_ulong					diff;
	t_ulong					unit;
	char					buf[BUF_SIZE];

	if (bot->life_unit <= 0)
		return ;
	gettimeofday(&cur, NULL);
	diff = (t_ulong)(cur.tv_sec - bot->time.tv_sec) * 1000000UL;
	diff += (t_ulong)(cur.tv_usec - bot->time.tv_usec);
	bot->time = cur;
	bot->timer += diff;
	unit = ((bot->timer * e->opt.t) / 1000000UL);
	bot->timer = bot->timer - (unit * 1000000UL / e->opt.t);
	check_life(e, bot, unit);
	if (bot->action_timer > 0 && (bot->action_timer -= unit) <= 0)
	{
		if (bot->status == STATUS_FORK || bot->status == STATUS_EGG)
			handle_status_fork_and_egg(e, bot);
		else if (bot->status == STATUS_INCANTATION)
			handle_status_incantation(e, bot);
		bot->action_timer = -1;
		if (buf_unload(bot->buf_action, &buf) != -1)
			buf_load(e->fds[bot->fd].buf_write, buf);
	}
}
