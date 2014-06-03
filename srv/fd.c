/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:40 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/03 14:15:27 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include "libft.h"
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

void			fd_watch(t_env *e, int fd)
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
	t_bot		*bot;
	t_gfx		*gfx;

	fct(e, e->bot_srv);
	fct(e, e->gfx_srv);
	iter = NULL;
	while ((bot = (t_bot *)ft_lst_iter_next_content(e->bot_lst, &iter)))
		fct(e, bot->fd);
	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		fct(e, gfx->fd);
}
