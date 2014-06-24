/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_sbp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:22:15 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:22:22 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			sbp(t_env *e, int fd)
{
	char			buf[128];

	sprintf(buf, "sbp\n");
	ft_strcat(e->fds[fd].buf_write, buf);
}