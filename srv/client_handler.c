/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:40 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/27 17:37:25 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <string.h>
#include "libft.h"
#include "server.h"

static int		check_buf_read(t_env *e, int cs)
{
	int			n;
	char		*p;

	if ((n = recv(cs, e->fds[cs].buf_read, BUF_SIZE, MSG_PEEK)) <= 0)
		fd_destroy(e, cs, "Connection closed.");
	else
	{
		e->fds[cs].buf_read[n] = '\0';
		if ((p = ft_strchr(e->fds[cs].buf_read, '\n')))
		{
			n = p - e->fds[cs].buf_read + 1;
			recv(cs, e->fds[cs].buf_read, n, 0);
			e->fds[cs].buf_read[n - 1] = '\0';
			return (n);
		}
	}
	return (0);
}

void			client_read(t_env *e, int cs)
{
	char	*send = "HELLO\nWORLD";

	if (check_buf_read(e, cs) > 0)
	{
		printf("[%s]\n", e->fds[cs].buf_read);
		//ft_strcpy(e->fds[cs].buf_write, e->fds[cs].buf_read);
		ft_strcpy(e->fds[cs].buf_write, send);
		ft_bzero(e->fds[cs].buf_read, BUF_SIZE);
	}
}

void			client_write(t_env *e, int cs)
{
	int		ret;

	ft_strcat(e->fds[cs].buf_write, "\n");
	ret = send(cs, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
	if (ret == -1)
		fprintf(stderr, "Cannot send message to Client #%d\n", cs);
	ft_bzero(e->fds[cs].buf_write, BUF_SIZE);
}
