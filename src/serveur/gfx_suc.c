/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_suc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:21:55 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 12:35:25 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			suc(t_env *e, int fd)
{
	char			buf[BUF_SIZE];

	sprintf(buf, "suc\n");
	buf_load(e->fds[fd].buf_write, buf);
}
