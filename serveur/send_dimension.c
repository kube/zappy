/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_dimension.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 12:18:39 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 12:19:18 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			send_dimension(t_env *e, int fd)
{
	char		*width;
	char		*height;

	width = ft_itoa(e->opt.width);
	height = ft_itoa(e->opt.height);
	ft_strcat(e->fds[fd].buf_write, width);
	ft_strcat(e->fds[fd].buf_write, " ");
	ft_strcat(e->fds[fd].buf_write, height);
	ft_strcat(e->fds[fd].buf_write, "\n");
	free(width);
	free(height);
}
