/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_bot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 11:58:31 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 12:07:42 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "libft.h"
#include "server.h"

static t_bot	*try_to_connect_from_queued(t_team *team)
{
	t_iterator		iter;
	t_bot			*bot;

	iter = NULL;
	while ((bot = (t_bot *)ft_lst_iter_next_content(team->queue, &iter)))
	{
		ft_lst_del_atom(team->queue, iter, NULL);
		ft_lst_pushend(team->connected, bot);
		return (bot);
	}
	return (NULL);
}

static t_bot	*try_to_connect_from_egg(t_team *team)
{
	t_iterator		iter;
	t_bot			*bot;

	iter = NULL;
	while ((bot = (t_bot *)ft_lst_iter_next_content(team->egg, &iter)))
	{
		ft_lst_del_atom(team->egg, iter, NULL);
		ft_lst_pushend(team->connected, bot);
		return (bot);
	}
	return (NULL);
}

static t_bot	*try_to_connect_from_unconnected(t_team *team)
{
	t_iterator		iter;
	t_bot			*bot;

	iter = NULL;
	while ((bot = (t_bot *)ft_lst_iter_next_content(team->unconnected, &iter)))
	{
		ft_lst_del_atom(team->unconnected, iter, NULL);
		ft_lst_pushend(team->connected, bot);
		return (bot);
	}
	return (NULL);
}

t_bot			*connect_bot(t_env *e, t_team *team)
{
	t_bot			*bot;

	(void)e;
	if ((bot = try_to_connect_from_queued(team)) != NULL)
		return (bot);
	if ((bot = try_to_connect_from_egg(team)) != NULL)
		return (bot);
	if ((bot = try_to_connect_from_unconnected(team)) != NULL)
		return (bot);
	return (NULL);
}

void			unconnect_bot(t_env *e, t_bot *bot)
{
	t_list			*connected;
	t_iterator		iter;
	t_bot			*b;

	(void)e;
	connected = bot->team->connected;
	iter = NULL;
	while ((b = (t_bot *)ft_lst_iter_next_content(connected, &iter)))
	{
		if (b == bot)
		{
			ft_lst_del_atom(connected, iter, NULL);
			ft_lst_pushend(bot->team->queue, b);
			break ;
		}
	}
}
