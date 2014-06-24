/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_ppo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:12:57 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:33:54 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			ppo(t_env *e, int fd, char **req, t_bot *b)
{
	char			buf[128];
	t_bot			*bot;

	if (req != NULL)
	{
		if ((bot = get_bot_by_id_arg(e, fd, req)) == NULL)
			return ;
	}
	else
		bot = b;
	sprintf(buf, "ppo #%d %d %d %d\n",
		bot->id,
		bot->sq % e->opt.width, bot->sq / e->opt.width,
		bot->dir);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			notify_all_gfx_ppo(t_env *e, t_bot *bot)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		ppo(e, gfx->fd, NULL, bot);
}
