/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pdi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:19:07 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 12:35:59 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			pdi(t_env *e, int fd, t_bot *bot)
{
	char			buf[BUF_SIZE];

	sprintf(buf, "pdi #%d\n", bot->id);
	buf_load(e->fds[fd].buf_write, buf);
}

void			notify_all_gfx_pdi(t_env *e, t_bot *bot)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		pdi(e, gfx->fd, bot);
}
