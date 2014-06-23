/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:40 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/23 15:59:42 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include "libft.h"
#include "server.h"

int					check_end(t_env *e)
{
	t_iterator		iter_t;
	t_iterator		iter_b;
	t_bot			*b;
	t_team			*t;
	int				n;

	iter_t = NULL;
	while ((t = (t_team *)ft_lst_iter_next_content(e->team, &iter_t)))
	{
		n = 0;
		iter_b = NULL;
		while ((b = (t_bot *)ft_lst_iter_next_content(t->connected, &iter_b)))
		{
			if (b->life_unit > 0 && b->level == 8)
			{
				if (++n == 6)
				{
					notify_all_gfx_seg(e, t);
					return (1);
				}
			}
		}
	}
	return (0);
}

int					main(int ac, char **av)
{
	t_env				e;
	struct timeval		t;

	get_opt(ac, av, &e.opt);
	init_game(&e);
	init_connection(&e);
	while (1)
	{
		t.tv_sec = 0;
		t.tv_usec = 0;
		FD_ZERO(&e.fd_read);
		FD_ZERO(&e.fd_write);
		e.max = 0;
		fd_iter_all(&e, fd_watch);
		e.res = select(e.max + 1, &e.fd_read, &e.fd_write, NULL, &t);
		try_int(e.res, -1, "select");
		fd_iter_all(&e, fd_check);
		bot_iter_all_connected_queued_egg(&e, timer);
		if (check_end(&e))
			while (1);
	}
	return (EXIT_SUCCESS);
}
