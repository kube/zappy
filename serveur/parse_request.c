/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_request.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/28 02:26:49 by cfeijoo           #+#    #+#             */
/*   Updated: 2014/06/24 14:21:30 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			gfx_connection(t_env *e, int fd)
{
	t_iterator		iter_t;
	t_iterator		iter_b;
	t_team			*t;
	t_bot			*b;

	e->fds[fd].type = FD_GFX_CLIENT;
	ft_lst_pushend(e->gfx_lst, gfx_new(fd));
	printf("Client #%d: Connected as GFX\n", fd);
	msz(e, fd);
	sgt(e, fd);
	mct(e, fd);
	tna(e, fd);
	iter_t = NULL;
	while ((t = (t_team *)ft_lst_iter_next_content(e->team, &iter_t)))
	{
		iter_b = NULL;
		while ((b = (t_bot *)ft_lst_iter_next_content(t->connected, &iter_b)))
		{
			pnw(e, fd, b);
			if (b->life_unit <= 0)
				pdi(e, fd, b);
		}
		iter_b = NULL;
		while ((b = (t_bot *)ft_lst_iter_next_content(t->queue, &iter_b)))
		{
			pnw(e, fd, b);
			if (b->life_unit <= 0)
				pdi(e, fd, b);
		}
		iter_b = NULL;
		while ((b = (t_bot *)ft_lst_iter_next_content(t->egg, &iter_b)))
		{
			enw(e, fd, b->parent, b);
			if (b->life_unit <= 0)
				edi(e, fd, b);
		}
	}
}

void			bot_connection(t_env *e, int fd, char *team_name)
{
	t_bot		*bot;
	t_team		*team;

	if ((team = get_team_by_name(e, team_name)) == NULL)
		printf("Client #%d: Invalid request (team doesn't exists)\n", fd);
	else if ((bot = connect_bot(e, team)) == NULL)
		printf("Client #%d: Cannot connect to any BOT\n", fd);
	else
	{
		e->fds[fd].type = FD_BOT_CLIENT;
		bot->fd = fd;
		if (bot->sq == -1)
		{
			bot->sq = sq_rand(e);
			move(e, bot, bot->sq);
			gettimeofday(&bot->time, NULL);
			notify_all_gfx_pnw(e, bot);
		}
		else if (bot->parent)
		{
			if (bot->life_unit < 0)
				bot->parent = NULL;
			notify_all_gfx_ebo(e, bot);
			notify_all_gfx_pnw(e, bot);
		}
		printf("Client #%d: Connected to BOT #%d\n", fd, bot->id);
		send_nbr(e, fd);
		send_dimension(e, fd);
	}
}

void			bot_parse_request(t_env *e, int fd, char *str)
{
	t_bot		*bot;
	char		**req;

	bot = get_bot_by_fd(e, fd);
	if (bot->status != STATUS_NONE)
		return ;
	req = (char **)try_void(ft_strsplit(str, ' '), NULL, "malloc");
	if (!req[0] || ((ft_strequ(req[0], "prend") || ft_strequ(req[0], "pose")
		|| ft_strequ(req[0], "broadcast")) && !req[1]))
		printf("Client #%d (BOT): Invalid request (too few arguments)\n", fd);
	else if (bot->life_unit <= 0)
	{
		if (bot->parent == NULL)
			printf("BOT #%d is dead\n", bot->id);
		else
			printf("EGG #%d is dead\n", bot->id);
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
		expulse(e, bot);
	else if (ft_strequ(req[0], "broadcast"))
		broadcast(e, bot, req[1]);
	else if (ft_strequ(req[0], "incantation"))
		incantation(e, bot);
	else if (ft_strequ(req[0], "fork"))
		fork_egg(e, bot);
	else if (ft_strequ(req[0], "connect_nbr"))
		send_nbr(e, fd);
	ft_free_strtab(req);
}

void			gfx_parse_request(t_env *e, int fd, char *str)
{
	char		**req;

	req = (char **)try_void(ft_strsplit(str, ' '), NULL, "malloc");
	if (!req[0])
		printf("Client #%d (GFX): Invalid request (too few arguments)\n", fd);
	else if (ft_strequ(req[0], "msz"))
		msz(e, fd);
	else if (ft_strequ(req[0], "bct"))
		bct(e, fd, req, 0);
	else if (ft_strequ(req[0], "mct"))
		mct(e, fd);
	else if (ft_strequ(req[0], "tna"))
		tna(e, fd);
	else if (ft_strequ(req[0], "ppo"))
		ppo(e, fd, req, 0);
	else if (ft_strequ(req[0], "plv"))
		plv(e, fd, req, 0);
	else if (ft_strequ(req[0], "pin"))
		pin(e, fd, req, 0);
	else if (ft_strequ(req[0], "sgt"))
		sgt(e, fd);
	else if (ft_strequ(req[0], "sst"))
		sst(e, fd, req);
	else
		suc(e, fd);
	ft_free_strtab(req);
}
