/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incantation_req.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 12:56:26 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 15:34:44 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int		g_req[7][7] =
{
	{1, 1, 0, 0, 0, 0, 0},
	{2, 1, 1, 1, 0, 0, 0},
	{2, 2, 0, 1, 0, 2, 0},
	{4, 1, 1, 2, 0, 1, 0},
	{4, 1, 2, 1, 3, 0, 0},
	{6, 1, 2, 3, 0, 1, 0},
	{6, 2, 2, 2, 2, 2, 1}
};

int				*incant_get_requirements(int level)
{
	return (g_req[level - 1]);
}

void			incant_get_elements(t_env *e, t_bot *bot)
{
	int				i;
	t_iterator		itr;
	t_obj			*o;
	t_bot			*b;

	i = 0;
	while (i < 7)
		bot->incant.req[i++] = ft_lst_new(NULL);
	itr = NULL;
	while ((o = (t_obj *)ft_lst_iter_next_content(e->board[bot->sq].obj, &itr)))
	{
		if (o->type != 0 && o->lock == OBJ_UNLOCKED)
			ft_lst_pushend(bot->incant.req[o->type], o);
	}
	itr = NULL;
	while ((b = (t_bot *)ft_lst_iter_next_content(e->board[bot->sq].bot, &itr)))
	{
		if (b != bot && b->life_unit > 0 && b->level == bot->level
			&& b->status == STATUS_NONE)
			ft_lst_pushend(bot->incant.req[0], b);
	}
}

void			incant_del_elements(t_env *e, t_bot *bot)
{
	int				i;

	(void)e;
	i = 0;
	while (i < 7)
		ft_lst_del(bot->incant.req[i++], NULL);
}
