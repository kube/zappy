/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/18 16:49:50 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/18 17:26:02 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <string.h>
#include "libft.h"
#include "server.h"
#include "requests.h"

void			msz(t_env *e, int fd)
{
	char	buf[64];

	sprintf(buf, "msz %d %d\n", e->opt.width, e->opt.height);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			bct(t_env *e, int fd, char **req)
{
	t_iterator		iter;
	t_obj			*o;
	int				obj[7];
	char			str[128];
	int			sq;

	(void)e;
	if (req[1] == NULL || req[2] == NULL)
	{
		printf("Gfx client #%d :  Invalid request (too few arguments)\n", fd);
		return ;
	}
	if ((sq = (ft_atoi(req[2]) * e->opt.width) + ft_atoi(req[1])) >= e->n_sq)
	{
		printf("Gfx client #%d :  Invalid request (invalid arguments)\n", fd);
		return ;
	}
	ft_bzero(obj, sizeof(int) * 7);
	iter = NULL;
	while ((o = (t_obj *)ft_lst_iter_next_content(e->board[sq].obj, &iter)))
		obj[o->type]++;
	sprintf(str, "bct %s %s %d %d %d %d %d %d %d\n", req[1], req[2],
	obj[0], obj[1], obj[2], obj[3], obj[4], obj[5], obj[6]);
	ft_strcat(e->fds[fd].buf_write, str);
}
