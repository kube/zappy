/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pie.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:17:12 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 12:30:46 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			pie(t_env *e, int fd, t_bot *bot, int res)
{
	char			buf[BUF_SIZE];

	sprintf(buf, "pie %d %d %d\n",
		bot->sq % e->opt.width, bot->sq / e->opt.width,
		res);
	buf_load(e->fds[fd].buf_write, buf);
}
