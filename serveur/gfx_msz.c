/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_msz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:11:14 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:11:26 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			msz(t_env *e, int fd)
{
	char	buf[128];

	sprintf(buf, "msz %d %d\n", e->opt.width, e->opt.height);
	ft_strcat(e->fds[fd].buf_write, buf);
}
