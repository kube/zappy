/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_smg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:21:34 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 12:26:49 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			smg(t_env *e, int fd, char *msg)
{
	char			buf[BUF_SIZE];

	sprintf(buf, "smg %s\n", msg);
	buf_load(e->fds[fd].buf_write, buf);
}
