/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pdr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:18:05 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 12:29:40 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			pdr(t_env *e, int fd, t_bot *bot, int type)
{
	char			buf[BUF_SIZE];

	sprintf(buf, "pdr #%d %d\n", bot->id, type);
	buf_load(e->fds[fd].buf_write, buf);
}
