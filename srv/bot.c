/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 12:23:13 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/13 18:15:33 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "libft.h"
#include "server.h"

t_bot			*bot_new(t_team *team)
{
	static int		id = 1;
	t_bot			*new;

	new = (t_bot *)try_void(ft_memalloc(sizeof(*new)), NULL, "malloc");
	new->id = id++;
	new->team = team;
	new->fd = -1;
	new->sq = -1;
	new->dir = dir_rand();
	new->life_unit = 10 * FOOD_UNIT;
	new->inventory = ft_lst_new(NULL);
	new->level = 1;
	gettimeofday(&new->time, NULL);
	new->timer = 0;
	new->food_timer = 0;
	new->action_timer = -1;
	ft_bzero(&new->buf_action, BUF_SIZE - 1);
	return (new);
}

t_bot			*connect_bot(t_env *e, t_team *team)
{
	t_atom			*atom;

	if ((atom = ft_lst_pop(team->unconnected)))
	{
		ft_lst_pushend(team->connected, atom->content);
		ft_lst_pushend(e->bot_lst, atom->content);
		return (atom->content);
	}
	return (NULL);
}

void			unconnect_bot(t_env *e, t_bot *bot)
{
	t_list			*connected;
	t_iterator		iter;
	t_bot			*b;

	connected = bot->team->connected;
	iter = NULL;
	while ((b = (t_bot *)ft_lst_iter_next_content(connected, &iter)))
	{
		if (b == bot)
		{
			ft_lst_del_atom(connected, iter, NULL);
			ft_lst_push(bot->team->unconnected, b);
			break ;
		}
	}
	iter = NULL;
	while ((bot = (t_bot *)ft_lst_iter_next_content(e->bot_lst, &iter)))
	{
		if (b == bot)
		{
			ft_lst_del_atom(e->bot_lst, iter, NULL);
			break ;
		}
	}
}

void			bot_destroy(t_env *e, int fd, char *msg)
{
	t_bot			*bot;
	t_iterator		iter;

	iter = NULL;
	while ((bot = (t_bot *)ft_lst_iter_next_content(e->bot_lst, &iter)))
	{
		if (bot->fd == fd)
		{
			printf("Client #%d (BOT #%d) gone away", fd, bot->id);
			if (msg)
				printf(": %s", msg);
			printf("\n");
			unconnect_bot(e, bot);
		}
	}
	fd_clean(&e->fds[fd]);
	close(fd);
}

