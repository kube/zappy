/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bot_by_id_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 13:25:12 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 13:31:39 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_bot			*get_bot_by_id_arg(t_env *e, int fd, char **req)
{
	t_bot			*bot;

	if (req[1] == NULL)
	{
		printf("Client #%d (GFX): Invalid request (too few arguments)\n", fd);
		sbp(e, fd);
		return (NULL);
	}
	if (req[1][0] != '#')
	{
		printf("Client #%d (GFX): Invalid request (invalid arguments)\n", fd);
		sbp(e, fd);
		return (NULL);
	}
	if ((bot = get_bot_by_id(e, ft_atoi(&req[1][1]))) == NULL)
	{
		printf("Client #%d (GFX): Invalid request (invalid bot id)\n", fd);
		sbp(e, fd);
		return (NULL);
	}
	return (bot);
}
