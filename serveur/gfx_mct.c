/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_mct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:12:09 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:12:19 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			mct(t_env *e, int fd)
{
	t_iterator		iter;
	t_obj			*o;
	int				obj[7];
	char			buf[128];
	int				sq;

	sq = 0;
	while (sq < e->n_sq)
	{
		ft_bzero(obj, sizeof(int) * 7);
		iter = NULL;
		while ((o = (t_obj *)ft_lst_iter_next_content(e->board[sq].obj, &iter)))
			obj[o->type]++;
		sprintf(buf, "bct %d %d %d %d %d %d %d %d %d\n",
			sq % e->opt.width, sq / e->opt.width,
			obj[0], obj[1], obj[2], obj[3], obj[4], obj[5], obj[6]);
		ft_strcat(e->fds[fd].buf_write, buf);
		sq++;
	}
}
