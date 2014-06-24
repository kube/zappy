/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pdr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:18:05 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:34:54 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			pdr(t_env *e, int fd, t_bot *bot, int type)
{
	char			buf[128];

	sprintf(buf, "pdr #%d %d\n", bot->id, type);
	ft_strcat(e->fds[fd].buf_write, buf);
}
