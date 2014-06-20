/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/18 16:49:50 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/20 10:52:17 by vdefilip         ###   ########.fr       */
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
	char	buf[128];

	sprintf(buf, "msz %d %d\n", e->opt.width, e->opt.height);
	ft_strcat(e->fds[fd].buf_write, buf);
}

static int		get_sq_arg(t_env *e, int fd, char **req)
{
	int		sq;

	if (req[1] == NULL || req[2] == NULL)
	{
		printf("Client #%d (GFX): Invalid request (too few arguments)\n", fd);
		return (-1);
	}
	if ((sq = (ft_atoi(req[2]) * e->opt.width) + ft_atoi(req[1])) >= e->n_sq)
	{
		printf("Client #%d (GFX): Invalid request (invalid arguments)\n", fd);
		return (-1);
	}
	return (sq);
}

void			bct(t_env *e, int fd, char **req, int square)
{
	t_iterator		iter;
	t_obj			*o;
	int				obj[7];
	char			buf[128];
	int				sq;

	(void)e;
	if (req != NULL)
	{
		if ((sq = get_sq_arg(e, fd, req)) == -1)
			return ;
	}
	else
		sq = square;
	ft_bzero(obj, sizeof(int) * 7);
	iter = NULL;
	while ((o = (t_obj *)ft_lst_iter_next_content(e->board[sq].obj, &iter)))
		obj[o->type]++;
	sprintf(buf, "bct %d %d %d %d %d %d %d %d %d\n",
		sq / e->opt.width, sq % e->opt.width,
		obj[0], obj[1], obj[2], obj[3], obj[4], obj[5], obj[6]);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			mct(t_env *e, int fd)
{
	t_iterator		iter;
	t_obj			*o;
	int				obj[7];
	char			buf[128];
	int				sq;

	sq = 0;
	while (sq < e->n_sq)
	{
		ft_bzero(obj, sizeof(int) * 7);
		iter = NULL;
		while ((o = (t_obj *)ft_lst_iter_next_content(e->board[sq].obj, &iter)))
			obj[o->type]++;
		sprintf(buf, "bct %d %d %d %d %d %d %d %d %d\n",
			sq % e->opt.width, sq / e->opt.width,
			obj[0], obj[1], obj[2], obj[3], obj[4], obj[5], obj[6]);
		ft_strcat(e->fds[fd].buf_write, buf);
		sq++;
	}
}

void			tna(t_env *e, int fd)
{
	t_iterator		iter;
	t_team			*team;
	char			buf[128];

	iter = NULL;
	while ((team = (t_team *)ft_lst_iter_next_content(e->team, &iter)))
	{
		sprintf(buf, "tna %s\n", team->name);
		ft_strcat(e->fds[fd].buf_write, buf);
	}
}

static t_bot	*get_bot_by_id_arg(t_env *e, int fd, char **req)
{
	t_bot			*bot;

	if (req[1] == NULL)
	{
		printf("Client #%d (GFX): Invalid request (too few arguments)\n", fd);
		return (NULL);
	}
	if (req[1][0] != '#')
	{
		printf("Client #%d (GFX): Invalid request (invalid arguments)\n", fd);
		return (NULL);
	}
	if ((bot = get_bot_by_id(e, ft_atoi(&req[1][1]))) == NULL)
	{
		printf("Client #%d (GFX): Invalid request (invalid bot id)\n", fd);
		return (NULL);
	}
	return (bot);
}

void			ppo(t_env *e, int fd, char **req, t_bot *b)
{
	char			buf[128];
	t_bot			*bot;

	if (req != NULL)
	{
		if ((bot = get_bot_by_id_arg(e, fd, req)) == NULL)
			return ;
	}
	else
		bot = b;
	sprintf(buf, "ppo #%d %d %d %d\n",
		bot->id,
		bot->sq % e->opt.width, bot->sq / e->opt.width,
		bot->dir);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			plv(t_env *e, int fd, char **req, t_bot *b)
{
	char			buf[128];
	t_bot			*bot;

	if (req != NULL)
	{
		if ((bot = get_bot_by_id_arg(e, fd, req)) == NULL)
			return ;
	}
	else
		bot = b;
	sprintf(buf, "plv #%d %d\n",
		bot->id,
		bot->level);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			pin(t_env *e, int fd, char **req, t_bot *b)
{
	t_iterator		iter;
	t_bot			*bot;
	t_obj			*o;
	int				obj[7];
	char			buf[128];

	if (req != NULL)
	{
		if ((bot = get_bot_by_id_arg(e, fd, req)) == NULL)
			return ;
	}
	else
		bot = b;
	ft_bzero(obj, sizeof(int) * 7);
	obj[0] = bot->life_unit / FOOD_UNIT;
	iter = NULL;
	while ((o = (t_obj *)ft_lst_iter_next_content(bot->inventory, &iter)))
		obj[o->type]++;
	sprintf(buf, "pin #%d %d %d %d %d %d %d %d %d %d\n",
		bot->id,
		bot->sq % e->opt.width, bot->sq / e->opt.width,
		obj[0], obj[1], obj[2], obj[3], obj[4], obj[5], obj[6]);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			sgt(t_env *e, int fd)
{
	char			buf[128];

	sprintf(buf, "sgt %d\n", e->opt.t);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			sst(t_env *e, int fd, char **req)
{
	int		t;

	if (req[1] == NULL)
	{
		printf("Client #%d (GFX): Invalid request (too few arguments)\n", fd);
		return ;
	}
	t = ft_atoi(req[1]);
	if (t < 1 || t > MAX_T)
	{
		printf("Client #%d (GFX): Invalid request (1 <= t <= %d\n", fd, MAX_T);
		return ;
	}
	e->opt.t = t;
	sgt(e, fd);
}

void			pnw(t_env *e, int fd, t_bot *bot)
{
	char			buf[128];

	sprintf(buf, "pnw #%d %d %d %d %d %s\n",
		bot->id,
		bot->sq % e->opt.width, bot->sq / e->opt.width,
		bot->dir,
		bot->level,
		bot->team->name);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			pex(t_env *e, int fd, t_bot *bot)
{
	char			buf[128];

	sprintf(buf, "pex #%d\n", bot->id);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			pbc(t_env *e, int fd, t_bot *bot, char *msg)
{
	char			buf[128];

	sprintf(buf, "pbc #%d %s\n", bot->id, msg);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			pic(t_env *e, int fd, t_bot *bot, int *ids)
{
	char			buf[128];
	int				i;

	sprintf(buf, "pic %d %d %d #%d",
		bot->sq % e->opt.width, bot->sq / e->opt.width,
		bot->level,
		bot->id);
	ft_strcat(e->fds[fd].buf_write, buf);
	i = 0;
	while (ids[i] != -1)
	{
		sprintf(buf, " #%d", ids[i]);
		ft_strcat(e->fds[fd].buf_write, buf);
		i++;
	}
	ft_strcat(e->fds[fd].buf_write, "\n");
}

void			pie(t_env *e, int fd, t_bot *bot, int res)
{
	char			buf[128];

	sprintf(buf, "pie %d %d %d\n",
		bot->sq % e->opt.width, bot->sq / e->opt.width,
		res);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			pfk(t_env *e, int fd, t_bot *bot)
{
	char			buf[128];

	sprintf(buf, "pfk #%d\n", bot->id);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			pdr(t_env *e, int fd, t_bot *bot, int type)
{
	char			buf[128];

	sprintf(buf, "pdr #%d %d\n", bot->id, type);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			pgt(t_env *e, int fd, t_bot *bot, int type)
{
	char			buf[128];

	sprintf(buf, "pgt #%d %d\n", bot->id, type);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			pdi(t_env *e, int fd, t_bot *bot)
{
	char			buf[128];

	sprintf(buf, "pdi #%d\n", bot->id);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			enw(t_env *e, int fd, t_bot *bot, t_bot *new_bot)
{
	char			buf[128];

	sprintf(buf, "enw #%d #%d %d %d\n",
		new_bot->id,
		bot->id,
		bot->sq % e->opt.width, bot->sq / e->opt.width);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			eht(t_env *e, int fd, t_bot *bot)
{
	char			buf[128];

	sprintf(buf, "eht #%d\n", bot->id);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			ebo(t_env *e, int fd, t_bot *bot)
{
	char			buf[128];

	sprintf(buf, "ebo #%d\n", bot->id);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			edi(t_env *e, int fd, t_bot *bot)
{
	char			buf[128];

	sprintf(buf, "ebo #%d\n", bot->id);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			seg(t_env *e, int fd, t_team *team)
{
	char			buf[128];

	sprintf(buf, "seg %s\n", team->name);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			smg(t_env *e, int fd, char *msg)
{
	char			buf[128];

	sprintf(buf, "smg %s\n", msg);
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			suc(t_env *e, int fd)
{
	char			buf[128];

	sprintf(buf, "suc\n");
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			sbp(t_env *e, int fd)
{
	char			buf[128];

	sprintf(buf, "sbp\n");
	ft_strcat(e->fds[fd].buf_write, buf);
}

void			notify_all_gfx_pnw(t_env *e, t_bot *bot)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		pnw(e, gfx->fd, bot);
}

void			notify_all_gfx_ppo(t_env *e, t_bot *bot)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		ppo(e, gfx->fd, NULL, bot);
}

void		notify_all_gfx_take(t_env *e, t_bot *bot, int type)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
	{
		pgt(e, gfx->fd, bot, type);
		pin(e, gfx->fd, NULL, bot);
		bct(e, gfx->fd, NULL, bot->sq);
	}
}

void		notify_all_gfx_put(t_env *e, t_bot *bot, int type)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
	{
		pdr(e, gfx->fd, bot, type);
		pin(e, gfx->fd, NULL, bot);
		bct(e, gfx->fd, NULL, bot->sq);
	}
}

void		notify_all_gfx_pdi(t_env *e, t_bot *bot)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		pdi(e, gfx->fd, bot);
}

void		notify_all_gfx_pex(t_env *e, t_bot *bot)
{
	t_iterator		iter;
	t_gfx			*gfx;

	iter = NULL;
	while ((gfx = (t_gfx *)ft_lst_iter_next_content(e->gfx_lst, &iter)))
		pex(e, gfx->fd, bot);
}

