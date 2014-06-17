/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 11:02:20 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/17 17:48:23 by vdefilip         ###   ########.fr       */
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

	if (bot->life_unit <= 0)
		return ;
	gettimeofday(&cur, NULL);
	diff = (t_ulong)(cur.tv_sec - bot->time.tv_sec) * 1000000UL;
	diff += (t_ulong)(cur.tv_usec - bot->time.tv_usec);
	bot->time = cur;
	bot->timer += diff;
	unit = ((bot->timer * e->opt.t) / 1000000UL);
	bot->timer = bot->timer - (unit * 1000000UL / e->opt.t);
	if ((bot->life_unit -= unit) <= 0)
	{
		printf("Bot client #%d is dead\n", bot->fd);
		ft_strcat(e->fds[bot->fd].buf_write, "mort\n");
	}
	if (bot->action_timer > 0 && (bot->action_timer -= unit) <= 0)
	{
		bot->action_timer = -1;
		ft_strcat(e->fds[bot->fd].buf_write, bot->buf_action);
		ft_bzero(bot->buf_action, BUF_SIZE);
	}
}
