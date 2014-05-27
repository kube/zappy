/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:40 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/27 17:38:07 by vdefilip         ###   ########.fr       */
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

static void			srv_accept(t_env *e, int s)
{
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			csin_len;

	csin_len = sizeof(csin);
	cs = try_int(accept(s, (struct sockaddr *)&csin, &csin_len), -1, "accept");
	e->fds[cs].type = FD_CLIENT;
	e->fds[cs].fct_read = client_read;
	e->fds[cs].fct_write = client_write;
	e->fds[cs].addr = inet_ntoa(csin.sin_addr);
	e->fds[cs].port = ntohs(csin.sin_port);
	printf("New client #%d from %s:%d\n", cs, e->fds[cs].addr, e->fds[cs].port);
	e->nb_user++;
}

static void			srv_create(t_env *e, int port)
{
	int					s;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	try_void(proto, NULL, "getprotobyname");
	s = try_int(socket(PF_INET, SOCK_STREAM, proto->p_proto), -1, "socket");
	e->srv = &e->fds[s];
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = INADDR_ANY;
	try_int(bind(s, (struct sockaddr *)&sin, sizeof(sin)), -1, "bind");
	try_int(listen(s, 42), -1, "listen");
	e->fds[s].type = FD_SERVER;
	e->fds[s].fct_read = srv_accept;
}

static void			env_init(t_env *e)
{
	int				i;
	t_rlimit		rlimit;

	try_int(getrlimit(RLIMIT_NOFILE, &rlimit), -1, "getrlimit");
	e->maxfd = rlimit.rlim_cur;
	e->fds = (t_fd *)try_void(malloc(sizeof(t_fd) * e->maxfd), NULL, "malloc");
	e->nb_user = 0;
	i = 0;
	while (i < e->maxfd)
	{
		fd_clean(&e->fds[i]);
		i++;
	}
}

int					main(int ac, char **av)
{
	t_env				e;

	if (ac != 2)
	{
		fprintf(stderr, USAGE, av[0]);
		exit(EXIT_FAILURE);
	}
	e.port = atoi(av[1]);
	env_init(&e);
	srv_create(&e, e.port);
	while (1)
	{
		fd_init(&e);
		e.res = select(e.max + 1, &e.fd_read, &e.fd_write, NULL, NULL);
		try_int(e.res, -1, "select");
		fd_check(&e);
	}
	return (EXIT_SUCCESS);
}
