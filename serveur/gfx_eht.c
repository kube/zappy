/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_eht.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:20:04 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:32:45 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			eht(t_env *e, int fd, t_bot *bot)
{
	char			buf[128];

	sprintf(buf, "eht #%d\n", bot->id);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			notify_all_gfx_eht(t_env *e, t_bot *bot)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		eht(e, gfx->fd, bot);
}
