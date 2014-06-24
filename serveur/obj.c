/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 19:29:42 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 14:03:41 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "server.h"

int			get_obj_type(char *obj_name)
{
	if (ft_strequ(obj_name, FOOD))
		return (OBJ_FOOD);
	if (ft_strequ(obj_name, ROCK1))
		return (OBJ_ROCK1);
	if (ft_strequ(obj_name, ROCK2))
		return (OBJ_ROCK2);
	if (ft_strequ(obj_name, ROCK3))
		return (OBJ_ROCK3);
	if (ft_strequ(obj_name, ROCK4))
		return (OBJ_ROCK4);
	if (ft_strequ(obj_name, ROCK5))
		return (OBJ_ROCK5);
	if (ft_strequ(obj_name, ROCK6))
		return (OBJ_ROCK6);
	return (-1);
}

char		*get_obj_name(int type)
{
	if (type == OBJ_FOOD)
		return (FOOD);
	if (type == OBJ_ROCK1)
		return (ROCK1);
	if (type == OBJ_ROCK2)
		return (ROCK2);
	if (type == OBJ_ROCK3)
		return (ROCK3);
	if (type == OBJ_ROCK4)
		return (ROCK4);
	if (type == OBJ_ROCK5)
		return (ROCK5);
	if (type == OBJ_ROCK6)
		return (ROCK6);
	return (NULL);
}

t_obj		*obj_new(int type)
{
	t_obj		*new;

	new = (t_obj *)try_void(malloc(sizeof(t_obj)), NULL, "malloc");
	new->type = type;
	new->lock = OBJ_UNLOCKED;
	return (new);
}

void		move_obj_random(t_env *e, t_obj *obj, int sq)
{
	t_iterator			iter;
	t_obj				*o;
	int					new_sq;

	new_sq = sq_rand(e);
	iter = NULL;
	while ((o = (t_obj *)ft_lst_iter_next_content(e->board[sq].obj, &iter)))
	{
		if (o == obj)
		{
			ft_lst_del_atom(e->board[sq].obj, iter, NULL);
			ft_lst_pushend(e->board[new_sq].obj, obj);
			notify_all_gfx_bct(e, sq);
			notify_all_gfx_bct(e, new_sq);
			return ;
		}
	}
}

t_obj		*get_obj(t_env *e, int sq, int type)
{
	t_iterator		iter;
	t_obj			*obj;

	iter = NULL;
	while ((obj = (t_obj *)ft_lst_iter_next_content(e->board[sq].obj, &iter)))
	{
		if (obj->type == type && obj->lock == OBJ_UNLOCKED)
		{
			ft_lst_del_atom(e->board[sq].obj, iter, NULL);
			return (obj);
		}
	}
	return (NULL);
}
