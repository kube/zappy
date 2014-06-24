/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_smg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:21:34 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:35:42 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			smg(t_env *e, int fd, char *msg)
{
	char			buf[128];

	sprintf(buf, "smg %s\n", msg);
	ft_strcat(e->fds[fd].buf_write, buf);
}
