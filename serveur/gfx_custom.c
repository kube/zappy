/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_custom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:22:35 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/26 11:17:47 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		notify_all_gfx_take(t_env *e, t_bot *bot, int type)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
	{
		pgt(e, gfx->fd, bot, type);
		pin(e, gfx->fd, NULL, bot);
		bct(e, gfx->fd, NULL, bot->sq);
	}
}

void		notify_all_gfx_put(t_env *e, t_bot *bot, int type)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
	{
		pdr(e, gfx->fd, bot, type);
		pin(e, gfx->fd, NULL, bot);
		bct(e, gfx->fd, NULL, bot->sq);
	}
}

void		notify_all_gfx_incant(t_env *e, t_bot *bot, int res)
{
	t_iterator		it_gfx;
	t_gfx			*gfx;
	t_iterator		it;
	t_bot			*b;

	it_gfx = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &it_gfx)))
	{
		pie(e, gfx->fd, bot, res);
		if (bot->life_unit > 0)
			plv(e, gfx->fd, NULL, bot);
		it = NULL;
		while ((b = (t_bot *)ft_lst_iter_next_content(bot->incant.req[0], &it)))
		{
			if (b->life_unit > 0)
				plv(e, gfx->fd, NULL, b);
		}
	}
}
