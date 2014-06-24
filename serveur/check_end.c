/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 18:45:17 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 18:45:57 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int					check_end(t_env *e)
{
	t_iterator		iter_t;
	t_iterator		iter_b;
	t_bot			*b;
	t_team			*t;
	int				n;

	iter_t = NULL;
	while ((t = (t_team *)ft_lst_iter_next_content(e->team, &iter_t)))
	{
		n = 0;
		iter_b = NULL;
		while ((b = (t_bot *)ft_lst_iter_next_content(t->connected, &iter_b)))
		{
			if (b->life_unit > 0 && b->level == 8)
			{
				if (++n == 6)
				{
					notify_all_gfx_seg(e, t);
					while (1)
						sleep(1);
				}
			}
		}
	}
	return (0);
}
