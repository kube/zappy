/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pbc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:16:08 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:33:02 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			pbc(t_env *e, int fd, t_bot *bot, char *msg)
{
	char			buf[128];

	sprintf(buf, "pbc #%d %s\n", bot->id, msg);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			notify_all_gfx_pbc(t_env *e, t_bot *bot, char *msg)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		pbc(e, gfx->fd, bot, msg);
}
