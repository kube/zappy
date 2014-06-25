/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 15:29:25 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 15:33:08 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static t_parse		g_gfx_parse[9] =
{
	{"bct", bct},
	{"ppo", ppo},
	{"plv", plv},
	{"pin", pin},
	{"sst", sst},
	{"msz", msz},
	{"mct", mct},
	{"tna", tna},
	{"sgt", sgt}
};

static void		notify_bot_for_connected_gfx(t_env *e, int fd, t_team *t)
{
	t_iterator		iter_b;
	t_bot			*b;

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

void			gfx_connection(t_env *e, int fd)
{
	t_iterator		iter_t;
	t_team			*t;

	e->fds[fd].type = FD_GFX_CLIENT;
	ft_lst_pushend(e->gfx_lst, gfx_new(fd));
	printf("Client #%d: Connected as GFX\n", fd);
	msz(e, fd);
	sgt(e, fd);
	mct(e, fd);
	tna(e, fd);
	iter_t = NULL;
	while ((t = (t_team *)ft_lst_iter_next_content(e->team, &iter_t)))
		notify_bot_for_connected_gfx(e, fd, t);
}

void			gfx_parse_request(t_env *e, int fd, char *str)
{
	char		**req;
	int			i;

	req = (char **)try_void(ft_strsplit(str, ' '), NULL, "malloc");
	if (!req[0])
		printf("Client #%d (GFX): Invalid request (too few arguments)\n", fd);
	else
	{
		i = 0;
		while (i < 9)
		{
			if (ft_strequ(req[0], g_gfx_parse[i].cmd))
			{
				if (i < 5)
					g_gfx_parse[i].fct(e, fd, req, 0);
				else
					g_gfx_parse[i].fct(e, fd);
				break ;
			}
			i++;
		}
	}
	if (i == 9)
		suc(e, fd);
	ft_free_strtab(req);
}
