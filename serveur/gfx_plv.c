/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_plv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:13:35 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 12:33:09 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			plv(t_env *e, int fd, char **req, t_bot *b)
{
	char			buf[BUF_SIZE];
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
	buf_load(e->fds[fd].buf_write, buf);
}
