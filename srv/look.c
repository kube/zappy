/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:40:39 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/11 18:29:25 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "server.h"

int			get_top_left(t_env *e, int sq, int dir)
{
	if (dir == NORTH)
		return (get_west(e, get_north(e, sq)));
	else if (dir == SOUTH)
		return (get_east(e, get_south(e, sq)));
	else if (dir == EAST)
		return (get_north(e, get_east(e, sq)));
	return (get_south(e, get_west(e, sq)));
}

int			get_right(t_env *e, int sq, int dir)
{
	if (dir == NORTH)
		return (get_east(e, sq));
	else if (dir == SOUTH)
		return (get_west(e, sq));
	else if (dir == EAST)
		return (get_south(e, sq));
	return (get_north(e, sq));
}

void		add_sq_content(t_env *e, char **s, t_bot *bot, int sq)
{
	t_iterator	iter;
	t_obj		*obj;
	char		type[][16] = {FOOD, ROCK1, ROCK2, ROCK3, ROCK4, ROCK5, ROCK6};
	int			n;

	iter = NULL;
	while ((obj = (t_obj*)ft_lst_iter_next_content(e->board[sq].obj, &iter)))
	{
		if (*s[0] != '\0')
			*s = ft_strjoin(*s, " ", FT_JOIN_FREE1);
		*s = ft_strjoin(*s, type[obj->type], FT_JOIN_FREE1);
	}
	n = (bot->sq != sq ? e->board[sq].bot->len : e->board[sq].bot->len - 1);
	while (n--)
	{
		if (*s[0] != '\0')
			*s = ft_strjoin(*s, " ", FT_JOIN_FREE1);
		*s = ft_strjoin(*s, "joueur", FT_JOIN_FREE1);
	}
}

char		*look(t_env *e, t_bot *bot)
{
	char		*s;
	int			i;
	int			j;
	int			first_sq;
	int			sq;

	s = ft_strdup("{");
	first_sq = bot->sq;
	i = 0;
	while (i < bot->level + 1)
	{
		sq = first_sq;
		j = 0;
		while (j < (i * 2 + 1))
		{
			if (s[0] != '{')
				s = ft_strjoin(s, ",", FT_JOIN_FREE1);
			add_sq_content(e, &s, bot, sq);
			sq = get_right(e, sq, bot->dir);
			j++;
		}
		first_sq = get_top_left(e, first_sq, bot->dir);
		i++;
	}
	s = ft_strjoin(s, "}", FT_JOIN_FREE1);
	return (s);
}
