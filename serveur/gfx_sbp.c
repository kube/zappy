/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_sbp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:22:15 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 12:34:40 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			sbp(t_env *e, int fd)
{
	char			buf[BUF_SIZE];

	sprintf(buf, "sbp\n");
	buf_load(e->fds[fd].buf_write, buf);
}
