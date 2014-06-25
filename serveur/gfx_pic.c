/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:16:52 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 13:01:29 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			pic(t_env *e, int fd, t_bot *bot)
{
	char			buf1[BUF_SIZE];
	char			buf2[BUF_SIZE];
	t_iterator		iter;
	t_bot			*b;

	sprintf(buf1, "pic %d %d %d #%d",
		bot->sq % e->opt.width, bot->sq / e->opt.width,
		bot->level,
		bot->id);
	iter = NULL;
	while ((b = (t_bot *)ft_lst_iter_next_content(bot->incant.req[0], &iter)))
	{
		sprintf(buf2, " #%d", b->id);
		ft_strcat(buf1, buf2);
	}
	ft_strcat(buf1, "\n");
	buf_load(e->fds[fd].buf_write, buf1);
}

void			notify_all_gfx_pic(t_env *e, t_bot *bot)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		pic(e, gfx->fd, bot);
}
