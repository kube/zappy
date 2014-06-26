/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_plv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:13:35 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/26 16:29:49 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			plv(t_env *e, int fd, char **req, t_bot *b)
{
	char			buf[BUF_SIZE];
	t_bot			*bot;

	if (req != NULL)
	{
		if ((bot = get_bot_by_id_arg(e, fd, req)) == NULL)
			return ;
	}
	else
		bot = b;
	sprintf(buf, "plv #%d %d\n",
		bot->id,
		bot->level);
	buf_load(e->fds[fd].buf_write, buf);
}

void			notify_all_gfx_plv(t_env *e, t_bot *bot)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		plv(e, gfx->fd, NULL, bot);
}
