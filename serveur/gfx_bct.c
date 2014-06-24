/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_bct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:11:39 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:11:56 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int		get_sq_arg(t_env *e, int fd, char **req)
{
	int		sq;

	if (req[1] == NULL || req[2] == NULL)
	{
		printf("Client #%d (GFX): Invalid request (too few arguments)\n", fd);
		sbp(e, fd);
		return (-1);
	}
	if ((sq = (ft_atoi(req[2]) * e->opt.width) + ft_atoi(req[1])) >= e->n_sq)
	{
		printf("Client #%d (GFX): Invalid request (invalid arguments)\n", fd);
		sbp(e, fd);
		return (-1);
	}
	return (sq);
}

void			bct(t_env *e, int fd, char **req, int square)
{
	t_iterator		iter;
	t_obj			*o;
	int				obj[7];
	char			buf[128];
	int				sq;

	if (req != NULL)
	{
		if ((sq = get_sq_arg(e, fd, req)) == -1)
			return ;
	}
	else
		sq = square;
	ft_bzero(obj, sizeof(int) * 7);
	iter = NULL;
	while ((o = (t_obj *)ft_lst_iter_next_content(e->board[sq].obj, &iter)))
		obj[o->type]++;
	sprintf(buf, "bct %d %d %d %d %d %d %d %d %d\n",
		sq % e->opt.width, sq / e->opt.width,
		obj[0], obj[1], obj[2], obj[3], obj[4], obj[5], obj[6]);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			notify_all_gfx_bct(t_env *e, int sq)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		bct(e, gfx->fd, NULL, sq);
}
