/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pgt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:18:37 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 12:28:47 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			pgt(t_env *e, int fd, t_bot *bot, int type)
{
	char			buf[BUF_SIZE];

	sprintf(buf, "pgt #%d %d\n", bot->id, type);
	buf_load(e->fds[fd].buf_write, buf);
}
