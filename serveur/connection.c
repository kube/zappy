/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 13:20:00 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/19 14:30:00 by vdefilip         ###   ########.fr       */
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
#include <sys/time.h>
#include "libft.h"
#include "server.h"

static void			srv_accept(t_env *e, int fd)
{
	int					*cs;
	struct sockaddr_in	csin;
	socklen_t			csin_len;

	csin_len = sizeof(csin);
	cs = (int *)try_void(malloc(sizeof(*cs)), NULL, "malloc");
	*cs = accept(fd, (struct sockaddr *)&csin, &csin_len);
	try_int(*cs, -1, "accept");
	e->fds[*cs].type = FD_CLIENT;
	e->fds[*cs].fct_read = client_read;
	e->fds[*cs].fct_write = client_write;
	e->fds[*cs].addr = inet_ntoa(csin.sin_addr);
	e->fds[*cs].port = ntohs(csin.sin_port);
	ft_lst_pushend(e->client_lst, cs);
	printf("New client #%d ", *cs);
	printf("from %s:%d\n", e->fds[*cs].addr, e->fds[*cs].port);
	ft_strcpy(e->fds[*cs].buf_write, "BIENVENUE");
}

static int			srv_create(t_env *e, int port, int type)
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
	try_int(setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &sin, sizeof(sin)), -1,
		"setsockopt");
	try_int(bind(s, (struct sockaddr *)&sin, sizeof(sin)), -1, "bind");
	try_int(listen(s, CONNEXION_QUEUE), -1, "listen");
	e->fds[s].type = type;
	e->fds[s].fct_read = srv_accept;
	return (s);
}

void				init_connection(t_env *e)
{
	int				i;
	t_rlimit		rlimit;

	try_int(getrlimit(RLIMIT_NOFILE, &rlimit), -1, "getrlimit");
	e->maxfd = rlimit.rlim_cur;
	e->fds = (t_fd *)try_void(malloc(sizeof(t_fd) * e->maxfd), NULL, "malloc");
	i = 0;
	while (i < e->maxfd)
	{
		fd_clean(&e->fds[i]);
		i++;
	}
	if (e->opt.bot_port == e->opt.gfx_port)
		e->srv = srv_create(e, e->opt.bot_port, FD_SRV);
	else
	{
		e->srv = -1;
		e->bot_srv = srv_create(e, e->opt.bot_port, FD_BOT_SRV);
		e->gfx_srv = srv_create(e, e->opt.gfx_port, FD_GFX_SRV);
	}
}
