/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:40 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/28 19:38:06 by vdefilip         ###   ########.fr       */
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
	t_iterator		iter;
	int				*id;
	t_list			*lst;

	if (e->fds[cs].type == FD_BOT_CLIENT)
	{
		lst = e->bot_lst;
		printf("Client #%d (BOT) gone away", cs);
	}
	else
	{
		lst = e->gfx_lst;
		printf("Client #%d (GFX) gone away", cs);
	}
	if (msg)
		printf(": %s", msg);
	printf("\n");
	iter = NULL;
	while ((id = (int *)ft_lst_iter_next_content(lst, &iter)))
	{
		if (*id == cs)
			ft_lst_del_atom(lst, iter, free);
	}
	fd_clean(&e->fds[cs]);
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

void			fd_init(t_env *e, int fd)
{
	FD_SET(fd, &e->fd_read);
	if (strlen(e->fds[fd].buf_write) > 0)
		FD_SET(fd, &e->fd_write);
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
	int			*id;

	fct(e, e->bot_srv);
	fct(e, e->gfx_srv);
	iter = NULL;
	while ((id = (int *)ft_lst_iter_next_content(e->bot_lst, &iter)))
		fct(e, *id);
	iter = NULL;
	while ((id = (int *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		fct(e, *id);
}
