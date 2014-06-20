/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responses.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/28 02:25:29 by cfeijoo           #+#    #+#             */
/*   Updated: 2014/06/17 14:37:32 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <string.h>
#include "libft.h"
#include "server.h"

void			res_msz(char *buf_write)
{
	/*
	**	Map Size
	**	Response model: msz X Y
	*/
	ft_strcpy(buf_write,
		"msz 22 42");
}

void			res_bct(char *buf_write, int x, int y)
{
	/*
	**	Block Content
	**	Response model: bct X Y q q q q q q q
	*/
	(void)x;
	(void)y;
	ft_strcpy(buf_write,
		"bct x y 0 0 0 0 0 0 0");
}

void			res_mct(char *buf_write)
{
	/*
	**	Map Blocks content
	**	Response model: bct X Y q q q q q q q
	**	(for each block in map)
	*/
	ft_strcpy(buf_write,
		"bct x y 0 0 0 0 0 0 0");

	ft_strcpy(buf_write,
		"bct x y 0 0 0 0 0 0 0");

	ft_strcpy(buf_write,
		"bct x y 0 0 0 0 0 0 0");

	ft_strcpy(buf_write,
		"bct x y 0 0 0 0 0 0 0");
}

void			res_tna(char *buf_write)
{
	/*
	**	Teams names
	**	Response model: tna [team name]
	**	(for each team)
	*/
	ft_strcpy(buf_write,
		"tna Hello");

	ft_strcpy(buf_write,
		"tna World");

	ft_strcpy(buf_write,
		"tna 42");
}

void			res_pnw(char *buf_write)
{
	/*
	**	New Player Connection
	**	Response model: pnw [player number] X Y O L N
	**	(for each team)
	*/
	ft_strcpy(buf_write,
		"pnw 2 1 1 0 0 42");
}

void			res_ppo(char *buf_write, int player)
{
	/*
	**	Player Position
	**	Response model: ppo #[player number] X Y O
	*/
	(void)player;
	ft_strcpy(buf_write,
		"ppo [player] 1 1 0");
}

void			res_plv(char *buf_write, int player)
{
	/*
	**	Player Level
	**	Response model: plv #[player number] L
	*/
	(void)player;
	ft_strcpy(buf_write,
		"plv [player] 42");
}

void			res_pin(char *buf_write, int player)
{
	/*
	**	Player Inventory
	**	Response model: pin #[player number] X Y q q q q q q q
	*/
	(void)player;
	ft_strcpy(buf_write,
		"pin [player] 1 1 0 0 0 0 0 0 0");
}

void			res_pex(char *buf_write, int player)
{
	/*
	**	Player expels
	**	Response model: pex #[player number]
	*/
	(void)player;
	ft_strcpy(buf_write,
		"pex [player]");
}

void			res_pbc(char *buf_write, int player)
{
	/*
	**	Player broadcasts
	**	Response model: pbc #[player number] [message]
	*/
	(void)player;
	ft_strcpy(buf_write,
		"pbc [player] [message]");
}

void			res_pic(char *buf_write, int x, int y, int l, int *players)
{
	/*
	**	First player starts incantation for all others
	**	Response model: pic X Y L #[player] {#[player] #[player]...}
	*/
	(void)players;
	(void)x;
	(void)y;
	(void)l;
	ft_strcpy(buf_write,
		"pic X Y L 1 2 3 4");
}

void			res_pie(char *buf_write, int x, int y, int result)
{
	/*
	**	Incantation ends on block
	**	(Result will be 0 or 1)
	**	Response model: pie X Y [result]
	*/
	(void)buf_write;
	(void)x;
	(void)y;
	(void)result;
}

void			res_pfk(char *buf_write, int player)
{
	/*
	**	Player lays an egg
	**	Response model: pfk #[player]
	*/
	(void)buf_write;
	(void)player;
}

void			res_pdr(char *buf_write, int player, int i)
{
	/*
	**	Player drops a ressource
	**	Response model: pdr #[player] i
	*/
	(void)buf_write;
	(void)player;
	(void)i;
}

void			res_pgt(char *buf_write, int player, int i)
{
	/*
	**	Player takes a ressource
	**	Response model: pgt #[player] i
	*/
	(void)buf_write;
	(void)player;
	(void)i;
}

void			res_pdi(char *buf_write, int player)
{
	/*
	**	Player famishes
	**	Response model: pdi #[player]
	*/
	(void)buf_write;
	(void)player;
}

void			res_enw(char *buf_write, int egg, int player, int x, int y)
{
	/*
	**	Egg has been layed on block by player
	**	Response model: enw #[egg] #[player] X Y
	*/
	(void)buf_write;
	(void)egg;
	(void)player;
	(void)x;
	(void)y;
}

void			res_eht(char *buf_write, int egg)
{
	/*
	**	Egg hatches out
	**	Response model: eht #[egg]
	*/
	(void)buf_write;
	(void)egg;
}

void			res_ebo(char *buf_write, int egg)
{
	/*
	**	A player connects for the egg
	**	Response model: ebo #[egg]
	*/
	(void)buf_write;
	(void)egg;
}

void			res_edi(char *buf_write, int egg)
{
	/*
	**	Egg famishes
	**	Response model: edi #[egg]
	*/
	(void)buf_write;
	(void)egg;
}

void			res_sgt(char *buf_write)
{
	/*
	**	Get Server Time Unit
	**	Response model: sgt [time]
	*/
	ft_strcpy(buf_write,
		"sgt [time]");
}

void			res_seg(char *buf_write, char *team)
{
	/*
	**	End of Game
	**	Response model: seg [team]
	*/
	(void)buf_write;
	(void)team;
}

void			res_smg(char *buf_write, char *message)
{
	/*
	**	Server Message
	**	Response model: smg [message]
	*/
	(void)buf_write;
	(void)message;
}

void			res_suc(char *buf_write)
{
	/*
	**	Unknown Command
	**	Response model: suc
	*/
	ft_strcpy(buf_write,
		"suc");
}

void			res_sbp(char *buf_write)
{
	/*
	**	Bad parameter
	**	Response model: sbp
	*/
	ft_strcpy(buf_write,
		"sbp");
}
