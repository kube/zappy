/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:40:39 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 18:37:43 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int		get_top_left(t_env *e, int sq, int dir)
{
	if (dir == NORTH)
		return (get_west(e, get_north(e, sq)));
	else if (dir == SOUTH)
		return (get_east(e, get_south(e, sq)));
	else if (dir == EAST)
		return (get_north(e, get_east(e, sq)));
	return (get_south(e, get_west(e, sq)));
}

static int		get_right(t_env *e, int sq, int dir)
{
	if (dir == NORTH)
		return (get_east(e, sq));
	else if (dir == SOUTH)
		return (get_west(e, sq));
	else if (dir == EAST)
		return (get_south(e, sq));
	return (get_north(e, sq));
}

static void		add_sq_content(t_env *e, char **s, t_bot *bot, int sq)
{
	t_iterator	iter;
	t_obj		*obj;
	int			n;

	iter = NULL;
	while ((obj = (t_obj*)ft_lst_iter_next_content(e->board[sq].obj, &iter)))
	{
		if (obj->lock == OBJ_LOCKED)
			continue ;
		if ((*s)[ft_strlen(*s) - 1] != '{' && (*s)[ft_strlen(*s) - 1] != ' ')
			*s = ft_strjoin(*s, " ", FT_JOIN_FREE1);
		*s = ft_strjoin(*s, get_obj_name(obj->type), FT_JOIN_FREE1);
	}
	n = (bot->sq != sq ? e->board[sq].bot->len : e->board[sq].bot->len - 1);
	while (n--)
	{
		if ((*s)[ft_strlen(*s) - 1] != '{' && (*s)[ft_strlen(*s) - 1] != ' ')
			*s = ft_strjoin(*s, " ", FT_JOIN_FREE1);
		*s = ft_strjoin(*s, "joueur", FT_JOIN_FREE1);
	}
}

static void		get_content(t_env *e, t_bot *bot, int first_sq, char **s)
{
	int			i;
	int			j;
	int			sq;

	i = 0;
	while (i < bot->level + 1)
	{
		sq = first_sq;
		j = 0;
		while (j < (i * 2 + 1))
		{
			add_sq_content(e, s, bot, sq);
			*s = ft_strjoin(*s, ", ", FT_JOIN_FREE1);
			sq = get_right(e, sq, bot->dir);
			j++;
		}
		first_sq = get_top_left(e, first_sq, bot->dir);
		i++;
	}
}

void			look(t_env *e, t_bot *bot)
{
	char		*s;

	bot->action_timer = LOOK_TIME;
	s = ft_strdup("{");
	get_content(e, bot, bot->sq, &s);
	ft_strcpy(s + ft_strlen(s) - 2, "}\n");
	printf("BOT #%d see %s\n", bot->id, s);
	buf_load(bot->buf_action, s);
	free(s);
}
