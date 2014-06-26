/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pfk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:17:37 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 12:29:54 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			pfk(t_env *e, int fd, t_bot *bot)
{
	char			buf[BUF_SIZE];

	sprintf(buf, "pfk #%d\n", bot->id);
	buf_load(e->fds[fd].buf_write, buf);
}

void			notify_all_gfx_pfk(t_env *e, t_bot *bot)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		pfk(e, gfx->fd, bot);
}
