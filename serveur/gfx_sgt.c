/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_sgt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:14:20 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:14:28 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			sgt(t_env *e, int fd)
{
	char			buf[128];

	sprintf(buf, "sgt %d\n", e->opt.t);
	ft_strcat(e->fds[fd].buf_write, buf);
}
