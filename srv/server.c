/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:40 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/11 17:18:59 by vdefilip         ###   ########.fr       */
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

int					main(int ac, char **av)
{
	t_env				e;
	struct timeval		t;

	t_iterator			iter;
	t_bot				*bot;
	int					sq;

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
		while ((bot = (t_bot *)ft_lst_iter_next_content(e.bot_lst, &iter)))
		{
			if (bot->fd == 5)
			{
				sq = bot->sq;
				step(&e, bot);
				printf("BOT #5 step from %d to %d (%d)\n", sq, bot->sq, bot->dir);
				printf("BOT #5 see : [ %s ]\n", look(&e, bot));
			}
		}
		//print_board(&e);

	}
	return (EXIT_SUCCESS);
}
