/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_sst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:14:40 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 20:04:09 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			sst(t_env *e, int fd, char **req, int tmp)
{
	int		t;

	(void)tmp;
	if (req[1] == NULL)
	{
		printf("Client #%d (GFX): Invalid request (too few arguments)\n", fd);
		sbp(e, fd);
		return ;
	}
	t = ft_atoi(req[1]);
	if (t < 1 || t > MAX_T)
	{
		printf("Client #%d (GFX): Invalid request (1 <= t <= %d\n", fd, MAX_T);
		sbp(e, fd);
		return ;
	}
	e->opt.t = t;
	notify_all_gfx_sgt(e);
}
