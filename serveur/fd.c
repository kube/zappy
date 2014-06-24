/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:40 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 18:46:12 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

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

void			fd_destroy(t_env *e, int fd, char *msg)
{
	t_iterator		iter;
	int				*f;

	if (e->fds[fd].type == FD_CLIENT)
	{
		printf("Client #%d gone away", fd);
		if (msg)
			printf(": %s", msg);
		printf("\n");
	}
	iter = NULL;
	while ((f = (int *)ft_lst_iter_next_content(e->client_lst, &iter)))
	{
		if (*f == fd)
		{
			ft_lst_del_atom(e->client_lst, iter, free);
			break ;
		}
	}
	fd_clean(&e->fds[fd]);
	close(fd);
}

void			fd_watch(t_env *e, int fd)
{
	if (strlen(e->fds[fd].buf_write) > 0)
		FD_SET(fd, &e->fd_write);
	else
		FD_SET(fd, &e->fd_read);
	e->max = MAX(e->max, fd);
}

void			fd_check(t_env *e, int fd)
{
	if (FD_ISSET(fd, &e->fd_write))
		e->fds[fd].fct_write(e, fd);
	if (FD_ISSET(fd, &e->fd_read))
		e->fds[fd].fct_read(e, fd);
	if (FD_ISSET(fd, &e->fd_read) || FD_ISSET(fd, &e->fd_write))
		e->res--;
}

void			fd_iter_all(t_env *e, void (*fct)())
{
	t_iterator	iter;
	int			*fd;

	if (e->srv != -1)
		fct(e, e->srv);
	else
	{
		fct(e, e->bot_srv);
		fct(e, e->gfx_srv);
	}
	iter = NULL;
	while ((fd = (int *)ft_lst_iter_next_content(e->client_lst, &iter)))
		fct(e, *fd);
}
