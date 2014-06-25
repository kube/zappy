/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:40 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/25 13:02:43 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int		check_buf_read(t_env *e, int cs, int type)
{
	int			n;
	char		*p;
	char		buf[BUF_SIZE + 1];

	if ((n = recv(cs, buf, BUF_SIZE, MSG_PEEK)) <= 0)
	{
		if (type == FD_BOT_CLIENT)
			bot_destroy(e, cs, "Connection closed");
		else if (type == FD_GFX_CLIENT)
			gfx_destroy(e, cs, "Connection closed");
		fd_destroy(e, cs, "Connection closed");
	}
	else
	{
		buf[n] = '\0';
		if ((p = ft_strchr(buf, '\n')))
		{
			n = p - buf + 1;
			recv(cs, buf, n, 0);
			buf[n - 1] = '\0';
			buf_load(e->fds[cs].buf_read, buf);
			return (n);
		}
	}
	return (0);
}

static void		parse(t_env *e, int cs, int type)
{
	if (type == FD_BOT_CLIENT)
	{
		printf("%s", PURPLE);
		printf("Client #%d (BOT) [%s]\n", cs, e->fds[cs].buf_read);
		printf("%s", DEFAULT);
		bot_parse_request(e, cs, e->fds[cs].buf_read);
	}
	else if (type == FD_GFX_CLIENT)
	{
		printf("%s", CYAN);
		printf("Client #%d (GFX) [%s]\n", cs, e->fds[cs].buf_read);
		printf("%s", DEFAULT);
		gfx_parse_request(e, cs, e->fds[cs].buf_read);
	}
	else
	{
		printf("%s", GREEN);
		printf("Client #%d [%s]\n", cs, e->fds[cs].buf_read);
		printf("%s", DEFAULT);
		if (ft_strequ(e->fds[cs].buf_read, "GRAPHIC"))
			gfx_connection(e, cs);
		else
			bot_connection(e, cs, e->fds[cs].buf_read);
	}
}

void			client_read(t_env *e, int cs)
{
	int		type;

	type = e->fds[cs].type;
	if (check_buf_read(e, cs, type) > 0)
		parse(e, cs, type);
}

void			client_write(t_env *e, int cs)
{
	int		ret;
	char	buf[BUF_SIZE];

	while (buf_unload(e->fds[cs].buf_write, &buf) == 0)
	{
		ret = send(cs, buf, ft_strlen(buf), 0);
		if (ret == -1)
		{
			fprintf(stderr, "Cannot send message to Client #%d ", cs);
			if (e->fds[cs].type == FD_BOT_CLIENT)
				fprintf(stderr, "(BOT)\n");
			else
				fprintf(stderr, "(GFX)\n");
		}
	}
}
