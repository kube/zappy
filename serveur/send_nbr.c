/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_nbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 12:18:02 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 12:18:26 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			send_nbr(t_env *e, int fd)
{
	t_bot			*bot;
	int				n;
	char			*nbr;
	t_iterator		iter;
	t_bot			*egg;

	bot = get_bot_by_fd(e, fd);
	n = bot->team->unconnected->len + bot->team->queue->len;
	iter = NULL;
	while ((egg = (t_bot *)ft_lst_iter_next_content(bot->team->egg, &iter)))
	{
		if (bot->status == STATUS_NONE)
			n++;
	}
	nbr = ft_itoa(n);
	ft_strcat(e->fds[fd].buf_write, nbr);
	ft_strcat(e->fds[fd].buf_write, "\n");
	free(nbr);
}
