/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pie.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:17:12 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:17:24 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			pie(t_env *e, int fd, t_bot *bot, int res)
{
	char			buf[128];

	sprintf(buf, "pie %d %d %d\n",
		bot->sq % e->opt.width, bot->sq / e->opt.width,
		res);
	ft_strcat(e->fds[fd].buf_write, buf);
}
