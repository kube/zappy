/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_request.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/28 02:26:49 by cfeijoo           #+#    #+#             */
/*   Updated: 2014/06/17 17:57:56 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <string.h>
#include "libft.h"
#include "server.h"
#include "requests.h"

t_team			*get_team_by_name(t_env *e, char *name)
{
	t_iterator		iter;
	t_team			*team;

	iter = NULL;
	while ((team = (t_team *)ft_lst_iter_next_content(e->team, &iter)))
	{
		if (ft_strequ(team->name, name))
			return (team);
	}
	return (NULL);
}

void			send_nbr(t_env *e, int fd)
{
	t_bot		*bot;
	char		*nbr;

	bot = get_bot_by_fd(e, fd);
	nbr = ft_itoa(bot->team->unconnected->len + bot->team->queue->len);
	ft_strcat(e->fds[fd].buf_write, nbr);
	ft_strcat(e->fds[fd].buf_write, "\n");
	free(nbr);
}

void			send_dimension(t_env *e, int fd)
{
	char		*width;
	char		*height;

	width = ft_itoa(e->opt.width);
	height = ft_itoa(e->opt.height);
	ft_strcat(e->fds[fd].buf_write, width);
	ft_strcat(e->fds[fd].buf_write, " ");
	ft_strcat(e->fds[fd].buf_write, height);
	ft_strcat(e->fds[fd].buf_write, "\n");
	free(width);
	free(height);
}

void			bot_association(t_env *e, int fd, char ***req)
{
	t_bot		*bot;
	t_team		*team;

	if ((team = get_team_by_name(e, (*req)[0])) == NULL)
		printf(" Bot client #%d : Invalid request (invalid team)\n", fd);
	else if ((bot = connect_bot(e, team)) == NULL)
		printf(" Bot client #%d : Cannot connect bot\n", fd);
	else
	{
		bot->fd = fd;
		if (bot->sq == -1)
		{
			bot->sq = sq_rand(e);
			move(e, bot, bot->sq);
			gettimeofday(&bot->time, NULL);
		}
		printf("Bot client #%d connected to bot #%d\n", fd, bot->id);
		send_nbr(e, fd);
		send_dimension(e, fd);
	}
}

void			bot_parse_request(t_env *e, int fd, char *str)
{
	t_bot		*bot;
	char		**req;

	req = (char **)try_void(ft_strsplit(str, ' '), NULL, "malloc");
	if (!req[0] || ((ft_strequ(req[0], "prend") || ft_strequ(req[0], "pose")
		|| ft_strequ(req[0], "broadcast")) && !req[1]))
		printf("Bot client #%d : Invalid request (too few arguments)", fd);
	else if ((bot = get_bot_by_fd(e, fd)) == NULL)
		bot_association(e, fd, &req);
	else if (bot->life_unit <= 0)
	{
		printf("Bot client #%d is dead\n", fd);
		ft_strcat(e->fds[fd].buf_write, "mort\n");
	}
	else if (ft_strequ(req[0], "avance"))
		step(e, bot);
	else if (ft_strequ(req[0], "droite"))
		turn_right(e, bot);
	else if (ft_strequ(req[0], "gauche"))
		turn_left(e, bot);
	else if (ft_strequ(req[0], "voir"))
		look(e, bot);
	else if (ft_strequ(req[0], "inventaire"))
		get_inventory(e, bot);
	else if (ft_strequ(req[0], "prend"))
			take(e, bot, req[1]);
	else if (ft_strequ(req[0], "pose"))
			put(e, bot, req[1]);
	else if (ft_strequ(req[0], "inventaire"))
		get_inventory(e, bot);
	else if (ft_strequ(req[0], "expulse"))
		ft_strcat(e->fds[fd].buf_write, "ko\n");
	else if (ft_strequ(req[0], "broadcast"))
		ft_strcat(e->fds[fd].buf_write, "ko\n");
	else if (ft_strequ(req[0], "incantation"))
		ft_strcat(e->fds[fd].buf_write, "ko\n");
	else if (ft_strequ(req[0], "fork"))
		ft_strcat(e->fds[fd].buf_write, "ko\n");
	ft_free_strtab(req);
}
