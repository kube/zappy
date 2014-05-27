/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:40 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/27 17:37:55 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include "libft.h"
#include "server.h"

void			fd_destroy(t_env *e, int cs, char *msg)
{
	fd_clean(&e->fds[cs]);
	printf("Client #%d gone away", cs);
	if (msg)
		printf(": %s", msg);
	printf("\n");
	e->nb_user--;
	close(cs);
}

void			fd_clean(t_fd *fd)
{
	fd->type = FD_FREE;
	ft_bzero(&fd->buf_read, BUF_SIZE + 1);
	ft_bzero(&fd->buf_write, BUF_SIZE + 1);
	fd->fct_read = NULL;
	fd->fct_write = NULL;
	fd->addr = NULL;
	fd->port = -1;
}

void			fd_init(t_env *e)
{
	int		i;

	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	i = 0;
	e->max = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type != FD_FREE)
		{
			FD_SET(i, &e->fd_read);
			if (strlen(e->fds[i].buf_write) > 0)
				FD_SET(i, &e->fd_write);
			e->max = i;
		}
		i++;
	}
}

void			fd_check(t_env *e)
{
	int		i;

	i = 0;
	while (i < e->maxfd && e->res > 0)
	{
		if (FD_ISSET(i, &e->fd_read))
			e->fds[i].fct_read(e, i);
		if (FD_ISSET(i, &e->fd_write))
			e->fds[i].fct_write(e, i);
		if (FD_ISSET(i, &e->fd_read) || FD_ISSET(i, &e->fd_write))
			e->res--;
		i++;
	}
}
