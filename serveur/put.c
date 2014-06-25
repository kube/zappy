/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:54:22 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 13:02:03 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void		error(t_bot *bot, char *msg)
{
	printf("Client #%d (BOT): %s\n", bot->fd, msg);
	buf_load(bot->buf_action, "ko\n");
}

void			put(t_env *e, t_bot *bot, char *obj_name)
{
	t_iterator		iter;
	t_obj			*obj;
	int				type;

	bot->action_timer = PUT_TIME;
	if ((type = get_obj_type(obj_name)) == -1)
		return (error(bot, "Invalid object"));
	iter = NULL;
	while ((obj = (t_obj *)ft_lst_iter_next_content(bot->inventory, &iter)))
	{
		if (obj->type == type)
		{
			ft_lst_del_atom(bot->inventory, iter, NULL);
			ft_lst_pushend(e->board[bot->sq].obj, obj);
			printf("BOT #%d put %s\n", bot->id, obj_name);
			notify_all_gfx_put(e, bot, type);
			buf_load(bot->buf_action, "ok\n");
			return ;
		}
	}
	return (error(bot, "Object not found"));
}
