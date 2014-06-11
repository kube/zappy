/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 12:23:13 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/11 17:19:35 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "server.h"

t_bot			*bot_new(int fd)
{
	t_bot	*new;

	new = (t_bot *)try_void(ft_memalloc(sizeof(*new)), NULL, "malloc");
	new->fd = fd;
	new->sq = -1;
	new->dir = dir_rand();
	new->life_unit = 10;
	new->inventory = ft_lst_new(NULL);
	new->level = 1;
	return (new);
}

static void		bot_free(t_bot *bot)
{
	free(bot);
}

void			bot_destroy(t_env *e, int fd, char *msg)
{
	t_bot			*bot;
	t_iterator		iter;

	printf("Client #%d (BOT) gone away", fd);
	if (msg)
		printf(": %s", msg);
	printf("\n");
	iter = NULL;
	while ((bot = (t_bot *)ft_lst_iter_next_content(e->bot_lst, &iter)))
	{
		if (bot->fd == fd)
		{
			ft_lst_del_atom(e->bot_lst, iter, bot_free);
			break ;
		}
	}
	fd_clean(&e->fds[fd]);
	close(fd);
}

