/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:40 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/03 17:54:32 by vdefilip         ###   ########.fr       */
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


static void			bot_srv_accept(t_env *e)
{
	int					*cs;
	struct sockaddr_in	csin;
	socklen_t			csin_len;

	csin_len = sizeof(csin);
	cs = (int *)try_void(malloc(sizeof(*cs)), NULL, "malloc");
	*cs = accept(e->bot_srv, (struct sockaddr *)&csin, &csin_len);
	try_int(*cs, -1, "accept");
	e->fds[*cs].type = FD_BOT_CLIENT;
	e->fds[*cs].fct_read = client_read;
	e->fds[*cs].fct_write = client_write;
	e->fds[*cs].addr = inet_ntoa(csin.sin_addr);
	e->fds[*cs].port = ntohs(csin.sin_port);
	ft_lst_pushend(e->bot_lst, bot_new(*cs));
	printf("New client #%d (BOT) ", *cs);
	printf("from %s:%d\n", e->fds[*cs].addr, e->fds[*cs].port);
}

static void			gfx_srv_accept(t_env *e)
{
	int					*cs;
	struct sockaddr_in	csin;
	socklen_t			csin_len;

	csin_len = sizeof(csin);
	cs = (int *)try_void(malloc(sizeof(*cs)), NULL, "malloc");
	*cs = accept(e->gfx_srv, (struct sockaddr *)&csin, &csin_len);
	try_int(*cs, -1, "accept");
	e->fds[*cs].type = FD_GFX_CLIENT;
	e->fds[*cs].fct_read = client_read;
	e->fds[*cs].fct_write = client_write;
	e->fds[*cs].addr = inet_ntoa(csin.sin_addr);
	e->fds[*cs].port = ntohs(csin.sin_port);
	ft_lst_pushend(e->gfx_lst, gfx_new(*cs));
	printf("New client #%d (GFX) ", *cs);
	printf("from %s:%d\n", e->fds[*cs].addr, e->fds[*cs].port);
}

static int			srv_create(t_env *e, int port, int type, t_accept accept)
{
	int					s;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	try_void(proto, NULL, "getprotobyname");
	s = try_int(socket(PF_INET, SOCK_STREAM, proto->p_proto), -1, "socket");
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	try_int(bind(s, (struct sockaddr *)&sin, sizeof(sin)), -1, "bind");
	try_int(listen(s, CONNEXION_QUEUE), -1, "listen");
	e->fds[s].type = type;
	e->fds[s].fct_read = accept;
	return (s);
}

static void			env_init(t_env *e)
{
	int				i;
	t_rlimit		rlimit;
	t_iterator		iter;
	char			*name;
	t_team			*team;

	try_int(getrlimit(RLIMIT_NOFILE, &rlimit), -1, "getrlimit");
	e->maxfd = rlimit.rlim_cur;
	e->fds = (t_fd *)try_void(malloc(sizeof(t_fd) * e->maxfd), NULL, "malloc");
	e->bot_lst = ft_lst_new(NULL);
	e->gfx_lst = ft_lst_new(NULL);
	i = 0;
	while (i < e->maxfd)
	{
		fd_clean(&e->fds[i]);
		i++;
	}
	e->team = ft_lst_new(NULL);
	iter = NULL;
	while ((name = (char *)ft_lst_iter_next_content(e->opt.team_name, &iter)))
	{
		team = (t_team *)try_void(malloc(sizeof(*team)), NULL, "malloc");
		team->name = name;
		team->limit = e->opt.limit;
		team->nb_player = 0;
		ft_lst_pushend(e->team, team);
	}
}

int					main(int ac, char **av)
{
	t_env				e;

	get_opt(ac, av, &e.opt);
	env_init(&e);
	board_create(&e);
	e.bot_srv = srv_create(&e, e.opt.bot_port, FD_BOT_SERVER, bot_srv_accept);
	e.gfx_srv = srv_create(&e, e.opt.gfx_port, FD_GFX_SERVER, gfx_srv_accept);
	while (1)
	{
		FD_ZERO(&e.fd_read);
		FD_ZERO(&e.fd_write);
		e.max = 0;
		fd_iter_all(&e, fd_watch);
		e.res = select(e.max + 1, &e.fd_read, &e.fd_write, NULL, NULL);
		try_int(e.res, -1, "select");
		fd_iter_all(&e, fd_check);
	}
	return (EXIT_SUCCESS);
}
