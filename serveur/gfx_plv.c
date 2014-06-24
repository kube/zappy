/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_plv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:13:35 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:13:45 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			plv(t_env *e, int fd, char **req, t_bot *b)
{
	char			buf[128];
	t_bot			*bot;

	if (req != NULL)
	{
		if ((bot = get_bot_by_id_arg(e, fd, req)) == NULL)
			return ;
	}
	else
		bot = b;
	sprintf(buf, "plv #%d %d\n",
		bot->id,
		bot->level);
	ft_strcat(e->fds[fd].buf_write, buf);
}
