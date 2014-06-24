/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_enw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:19:30 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:32:51 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			enw(t_env *e, int fd, t_bot *bot, t_bot *new_bot)
{
	char			buf[128];

	sprintf(buf, "enw #%d #%d %d %d\n",
		new_bot->id,
		bot->id,
		bot->sq % e->opt.width, bot->sq / e->opt.width);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			notify_all_gfx_enw(t_env *e, t_bot *bot, t_bot *egg)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		enw(e, gfx->fd, bot, egg);
}
