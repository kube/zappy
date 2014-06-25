/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:13:59 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 12:32:51 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			pin(t_env *e, int fd, char **req, t_bot *b)
{
	t_iterator		iter;
	t_bot			*bot;
	t_obj			*o;
	int				obj[7];
	char			buf[BUF_SIZE];

	if (req != NULL)
	{
		if ((bot = get_bot_by_id_arg(e, fd, req)) == NULL)
			return ;
	}
	else
		bot = b;
	ft_bzero(obj, sizeof(int) * 7);
	obj[0] = bot->life_unit / FOOD_UNIT;
	iter = NULL;
	while ((o = (t_obj *)ft_lst_iter_next_content(bot->inventory, &iter)))
		obj[o->type]++;
	sprintf(buf, "pin #%d %d %d %d %d %d %d %d %d %d\n",
		bot->id,
		bot->sq % e->opt.width, bot->sq / e->opt.width,
		obj[0], obj[1], obj[2], obj[3], obj[4], obj[5], obj[6]);
	buf_load(e->fds[fd].buf_write, buf);
}:w

