/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 15:31:42 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/26 15:08:18 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static t_parse	g_bot_parse[12] =
{
	{"broadcast", broadcast},
	{"prend", take},
	{"pose", put},
	{"avance", step},
	{"droite", turn_right},
	{"gauche", turn_left},
	{"voir", look},
	{"inventaire", get_inventory},
	{"expulse", expulse},
	{"incantation", incantation},
	{"fork", fork_egg},
	{"connect_nbr", send_nbr}
};

static t_bot	*get_connected_bot(t_env *e, int fd, char *team_name)
{
	t_team		*team;
	t_bot		*bot;

	if ((team = get_team_by_name(e, team_name)) == NULL)
	{
		printf("Client #%d: Invalid request (team doesn't exists)\n", fd);
		return (NULL);
	}
	else if ((bot = connect_bot(e, team)) == NULL)
	{
		printf("Client #%d: Cannot connect to any BOT\n", fd);
		return (NULL);
	}
	return (bot);
}

void			bot_connection(t_env *e, int fd, char *team_name)
{
	t_bot		*bot;

	if ((bot = get_connected_bot(e, fd, team_name)) == NULL)
		return ;
	e->fds[fd].type = FD_BOT_CLIENT;
	bot->fd = fd;
	if (bot->sq == -1)
	{
		bot->sq = sq_rand(e);
		move(e, bot, bot->sq);
		gettimeofday(&bot->time, NULL);
		notify_all_gfx_pnw(e, bot);
	}
	else if (bot->parent)
	{
		if (bot->life_unit < 0)
			bot->parent = NULL;
		notify_all_gfx_ebo(e, bot);
		notify_all_gfx_pnw(e, bot);
	}
	printf("Client #%d: Connected to BOT #%d\n", fd, bot->id);
	send_nbr(e, fd);
	send_dimension(e, fd);
}

static void		dead(t_env *e, t_bot *bot)
{
	if (bot->parent == NULL)
		printf("BOT #%d is dead\n", bot->id);
	else
		printf("EGG #%d is dead\n", bot->id);
	buf_load(e->fds[bot->fd].buf_write, "mort\n");
}

static void		bot_exec_cmd(t_env *e, t_bot *bot, char *str, char **req)
{
	int			i;

	i = 0;
	while (i < 12)
	{
		if (ft_strequ(req[0], g_bot_parse[i].cmd))
		{
			if (i == 0)
				g_bot_parse[i].fct(e, bot, &str[ft_strlen(req[0]) + 1]);
			else if (i < 3)
				g_bot_parse[i].fct(e, bot, req[1]);
			else if (i < 11)
				g_bot_parse[i].fct(e, bot);
			else
				g_bot_parse[i].fct(e, bot->fd);
		}
		i++;
	}
}

void			bot_parse_request(t_env *e, int fd, char *str)
{
	t_bot		*bot;
	char		**req;

	bot = get_bot_by_fd(e, fd);
	if (bot->action_timer > 0)
		return ;
	req = (char **)try_void(ft_strsplit(str, ' '), NULL, "malloc");
	if (!req[0] || ((ft_strequ(req[0], "prend") || ft_strequ(req[0], "pose")
		|| ft_strequ(req[0], "broadcast")) && !req[1]))
		printf("Client #%d (BOT): Invalid request (too few arguments)\n", fd);
	else if (bot->life_unit <= 0)
		dead(e, bot);
	else
		bot_exec_cmd(e, bot, str, req);
	ft_free_strtab(req);
}
