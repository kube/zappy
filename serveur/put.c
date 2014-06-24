/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:54:22 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 14:01:29 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int		error(t_bot *bot, char *msg)
{
	printf("Client #%d (BOT): %s\n", bot->fd, msg);
	ft_strcat(bot->buf_action, "ko\n");
	return (-1);
}

int				put(t_env *e, t_bot *bot, char *obj_name)
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
			ft_strcat(bot->buf_action, "ok\n");
			return (0);
		}
	}
	return (error(bot, "Object not found"));
}
