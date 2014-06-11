/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 19:29:42 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/11 17:24:14 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "server.h"

t_obj		*obj_new(int type)
{
	t_obj		*new;

	new = (t_obj *)try_void(malloc(sizeof(t_obj)), NULL, "malloc");
	new->type = type;
	new->lock = 0;
	return (new);
}

t_obj		*get_obj(t_env *e, int sq, int type)
{
	t_iterator		iter;
	t_obj			*obj;

	iter = NULL;
	while ((obj = (t_obj *)ft_lst_iter_next_content(e->board[sq].obj, &iter)))
	{
		if (obj->type == type)
		{
			ft_lst_del_atom(e->board[sq].obj, iter, NULL);
			return (obj);
		}
	}
	return (NULL);
}

int			take(t_env *e, t_bot *bot, int type)
{
	t_obj			*obj;

	if ((obj = get_obj(e, bot->sq, type)) == NULL)
		return (-1);
	if (type == OBJ_FOOD)
	{
		bot->life_unit++;
		ft_lst_pushend(e->board[sq_rand(e)].obj, obj_new(OBJ_FOOD));
	}
	else
		ft_lst_pushend(bot->inventory, obj);
	return (0);
}

int			put(t_env *e, t_bot *bot, int type)
{
	t_iterator		iter;
	t_obj			*obj;

	iter = NULL;
	while ((obj = (t_obj *)ft_lst_iter_next_content(bot->inventory, &iter)))
	{
		if (obj->type == type)
		{
			ft_lst_del_atom(bot->inventory, iter, NULL);
			ft_lst_pushend(e->board[bot->sq].obj, obj);
			return (0);
		}
	}
	return (-1);
}

char		*get_inventory(t_env *e, t_bot *bot)
{
	t_iterator		iter;
	t_obj			*o;
	int				obj[6];
	char			*str;

	(void)e;
	ft_bzero(obj, sizeof(int) * 6);
	iter = NULL;
	while ((o = (t_obj *)ft_lst_iter_next_content(bot->inventory, &iter)))
		obj[o->type - 1]++;
	str = ft_strdup("{");
	str = ft_strmjoin(0x5, str, "linemate ", ft_itoa(obj[0]));
	str = ft_strmjoin(0x5, str, ", deraumere ", ft_itoa(obj[1]));
	str = ft_strmjoin(0x5, str, ", sibur ", ft_itoa(obj[2]));
	str = ft_strmjoin(0x5, str, ", mendiane ", ft_itoa(obj[3]));
	str = ft_strmjoin(0x5, str, ", phiras ", ft_itoa(obj[4]));
	str = ft_strmjoin(0x5, str, ", thystame", ft_itoa(obj[5]));
	str = ft_strjoin(str, "}", FT_JOIN_FREE1);
	return (str);
}
