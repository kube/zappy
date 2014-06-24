/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_tna.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:12:37 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:12:46 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			tna(t_env *e, int fd)
{
	t_iterator		iter;
	t_team			*team;
	char			buf[128];

	iter = NULL;
	while ((team = (t_team *)ft_lst_iter_next_content(e->team, &iter)))
	{
		sprintf(buf, "tna %s\n", team->name);
		ft_strcat(e->fds[fd].buf_write, buf);
	}
}
