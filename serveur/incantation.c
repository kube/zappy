/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incantation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 12:26:34 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/26 17:55:37 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void				move_rocks_after_incant(t_env *e, t_bot *bot)
{
	t_iterator		it;
	t_obj			*o;
	int				i;

	i = 1;
	while (i < 7)
	{
		it = NULL;
		while ((o = (t_obj *)ft_lst_iter_next_content(bot->incant.req[i], &it)))
		{
			o->lock = OBJ_UNLOCKED;
			move_obj_random(e, o, bot->sq);
		}
		i++;
	}
}

static void			mark_bots_for_incantation(t_env *e, t_bot *bot)
{
	t_iterator		itr;
	t_bot			*b;
	char			buf[128];

	bot->status = STATUS_INCANTATION;
	bot->action_timer = INCANTATION_TIME;
	buf_load(e->fds[bot->fd].buf_write, "elevation en cours\n");
	sprintf(buf, "niveau actuel : %d\n", bot->level + 1);
	buf_load(bot->buf_action, buf);
	itr = NULL;
	while ((b = (t_bot *)ft_lst_iter_next_content(bot->incant.req[0], &itr)))
	{
		b->status = STATUS_INCANTATION;
		b->action_timer = INCANTATION_TIME;
		buf_load(e->fds[b->fd].buf_write, "elevation en cours\n");
		buf_load(b->buf_action, buf);
		b->incant.parent = bot;
	}
}

static void			mark_obj_for_incantation(t_bot *bot, int req[7])
{
	t_atom			*curr;
	t_atom			*next;
	t_obj			*o;
	int				i;
	int				n;

	i = 1;
	while (i < 7)
	{
		n = 0;
		curr = bot->incant.req[i]->first;
		while (curr)
		{
			o = (t_obj *)curr->content;
			next = curr->next;
			if (n++ < req[i])
				o->lock = OBJ_LOCKED;
			else
				ft_lst_del_atom(bot->incant.req[i], curr, NULL);
			curr = next;
		}
		i++;
	}
}

void				incantation(t_env *e, t_bot *bot)
{
	int				i;
	int				*req;

	bot->action_timer = INCANTATION_TIME;
	req = incant_get_requirements(bot->level);
	if (bot->level < 8)
	{
		incant_get_elements(e, bot);
		i = 0;
		while (i < 7)
		{
			if ((int)bot->incant.req[i]->len < req[i])
			{
				incant_del_elements(e, bot);
				buf_load(bot->buf_action, "ko\n");
				return ;
			}
			i++;
		}
		mark_bots_for_incantation(e, bot);
		mark_obj_for_incantation(bot, req);
		notify_all_gfx_pic(e, bot);
		return ;
	}
	buf_load(bot->buf_action, "ko\n");
}
