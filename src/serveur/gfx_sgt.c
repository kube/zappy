/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_sgt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:14:20 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 20:04:15 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			sgt(t_env *e, int fd)
{
	char			buf[BUF_SIZE];

	sprintf(buf, "sgt %d\n", e->opt.t);
	buf_load(e->fds[fd].buf_write, buf);
}

void			notify_all_gfx_sgt(t_env *e)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		sgt(e, gfx->fd);
}
