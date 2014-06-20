/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requests.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/28 02:25:29 by cfeijoo           #+#    #+#             */
/*   Updated: 2014/05/28 03:49:48 by cfeijoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <string.h>
#include "libft.h"
#include "server.h"
#include "requests.h"

void			req_msz(char **args, t_env *e, int cs)
{
	/*
	**	Map Size
	**	Request model: msz
	**	Response model: msz X Y
	*/
	(void)args;
	res_msz(e->fds[cs].buf_write);
}

void			req_bct(char **args, t_env *e, int cs)
{
	/*
	**	Block Content
	**	Request model: bct X Y
	**	Response model: bct X Y q q q q q q q
	*/
	res_bct(e->fds[cs].buf_write, ft_atoi(args[0]), ft_atoi(args[1]));
}

void			req_mct(char **args, t_env *e, int cs)
{
	/*
	**	Map Blocks content
	**	Request model: mct
	**	Response model: bct X Y q q q q q q q
	**	(for each block in map)
	*/
	(void)args;
	res_mct(e->fds[cs].buf_write);
}

void			req_tna(char **args, t_env *e, int cs)
{
	/*
	**	Teams names
	**	Request model: tna
	**	Response model: tna [team name]
	**	(for each team)
	*/
	(void)args;
	res_tna(e->fds[cs].buf_write);
}

void			req_ppo(char **args, t_env *e, int cs)
{
	/*
	**	Player Position
	**	Request model: ppo #[player number]
	**	Response model: ppo #[player number] X Y O
	*/
	(void)args;
	res_ppo(e->fds[cs].buf_write, ft_atoi(args[0]));
}

void			req_plv(char **args, t_env *e, int cs)
{
	/*
	**	Player Level
	**	Request model: plv #[player number]
	**	Response model: plv #[player number] L
	*/
	(void)args;
	res_plv(e->fds[cs].buf_write, ft_atoi(args[0]));
}

void			req_pin(char **args, t_env *e, int cs)
{
	/*
	**	Player Inventory
	**	Request model: pin #[player number]
	**	Response model: pin #[player number] X Y q q q q q q q
	*/
	(void)args;
	res_pin(e->fds[cs].buf_write, ft_atoi(args[0]));
}

void			req_sgt(char **args, t_env *e, int cs)
{
	/*
	**	Get Server Time Unit
	**	Request model: sgt
	**	Response model: sgt [time]
	*/
	(void)args;
	res_sgt(e->fds[cs].buf_write);
}

void			req_sst(char **args, t_env *e, int cs)
{
	/*
	**	Set Server Time Unit
	**	(Replace Server Time Unit with args[0] value
	**
	**	Request model: sgt [time]
	**	Response model: sgt [time]
	*/
	(void)args;
	res_sgt(e->fds[cs].buf_write);
}
