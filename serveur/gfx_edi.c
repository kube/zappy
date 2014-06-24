/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_edi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:20:42 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:32:38 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			edi(t_env *e, int fd, t_bot *bot)
{
	char			buf[128];

	sprintf(buf, "edi #%d\n", bot->id);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			notify_all_gfx_edi(t_env *e, t_bot *bot)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		edi(e, gfx->fd, bot);
}
