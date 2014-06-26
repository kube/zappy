/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:54:51 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 12:52:00 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		get_inventory(t_env *e, t_bot *bot)
{
	t_iterator		iter;
	t_obj			*o;
	int				obj[7];
	char			str[BUF_SIZE];

	(void)e;
	bot->action_timer = INVENTORY_TIME;
	ft_bzero(obj, sizeof(int) * 7);
	obj[0] = bot->life_unit / FOOD_UNIT;
	iter = NULL;
	while ((o = (t_obj *)ft_lst_iter_next_content(bot->inventory, &iter)))
		obj[o->type]++;
	sprintf(str, "{%s %d, %s %d, %s %d, %s %d, %s %d, %s %d, %s %d}\n",
		FOOD, obj[0],
		ROCK1, obj[1],
		ROCK2, obj[2],
		ROCK3, obj[3],
		ROCK4, obj[4],
		ROCK5, obj[5],
		ROCK6, obj[6]);
	printf("BOT #%d has %s", bot->id, str);
	buf_load(bot->buf_action, str);
}
