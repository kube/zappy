/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pnw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:15:14 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:15:32 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			pnw(t_env *e, int fd, t_bot *bot)
{
	char			buf[128];

	sprintf(buf, "pnw #%d %d %d %d %d %s\n",
		bot->id,
		bot->sq % e->opt.width, bot->sq / e->opt.width,
		bot->dir,
		bot->level,
		bot->team->name);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			notify_all_gfx_pnw(t_env *e, t_bot *bot)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		pnw(e, gfx->fd, bot);
}
