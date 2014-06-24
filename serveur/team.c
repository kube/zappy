/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 11:28:35 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:38:03 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "server.h"

t_team			*team_new(char *name, int limit)
{
	t_team		*team;

	team = (t_team *)try_void(malloc(sizeof(*team)), NULL, "malloc");
	team->name = name;
	team->limit = limit;
	team->unconnected = ft_lst_new(NULL);
	team->connected = ft_lst_new(NULL);
	team->queue = ft_lst_new(NULL);
	team->egg = ft_lst_new(NULL);
	return (team);
}

t_team			*get_team_by_name(t_env *e, char *name)
{
	t_iterator		iter;
	t_team			*team;

	iter = NULL;
	while ((team = (t_team *)ft_lst_iter_next_content(e->team, &iter)))
	{
		if (ft_strequ(team->name, name))
			return (team);
	}
	return (NULL);
}
