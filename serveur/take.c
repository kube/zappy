/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:53:27 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 14:01:33 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int		error(t_bot *bot, char *msg)
{
	printf("Client #%d (BOT): %s\n", bot->fd, msg);
	ft_strcat(bot->buf_action, "ko\n");
	return (-1);
}

int				take(t_env *e, t_bot *bot, char *obj_name)
{
	int				sq;
	t_obj			*obj;
	int				type;

	bot->action_timer = TAKE_TIME;
	if ((type = get_obj_type(obj_name)) == -1)
		return (error(bot, "Invalid object"));
	if ((obj = get_obj(e, bot->sq, type)) == NULL)
		return (error(bot, "Object not found"));
	if (type == OBJ_FOOD)
	{
		bot->life_unit += FOOD_UNIT;
		sq = sq_rand(e);
		ft_lst_pushend(e->board[sq].obj, obj_new(OBJ_FOOD));
		notify_all_gfx_bct(e, sq);
	}
	else
		ft_lst_pushend(bot->inventory, obj);
	printf("BOT #%d take %s\n", bot->id, obj_name);
	notify_all_gfx_take(e, bot, type);
	ft_strcat(bot->buf_action, "ok\n");
	return (0);
}
