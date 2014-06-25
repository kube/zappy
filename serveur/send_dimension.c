/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_dimension.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 12:18:39 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 12:45:59 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			send_dimension(t_env *e, int fd)
{
	char		buf[BUF_SIZE];

	sprintf(buf, "%d %d\n", e->opt.width, e->opt.height);
	buf_load(e->fds[fd].buf_write, buf);
}
