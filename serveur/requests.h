/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requests.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/28 03:08:06 by cfeijoo           #+#    #+#             */
/*   Updated: 2014/05/28 12:21:27 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTS_H
# define REQUESTS_H
# include "server.h"

/*
**	Requests
*/
void	req_msz(char **args, t_env *e, int cs);
void	req_bct(char **args, t_env *e, int cs);
void	req_mct(char **args, t_env *e, int cs);
void	req_tna(char **args, t_env *e, int cs);
void	req_ppo(char **args, t_env *e, int cs);
void	req_plv(char **args, t_env *e, int cs);
void	req_pin(char **args, t_env *e, int cs);
void	req_sgt(char **args, t_env *e, int cs);
void	req_sst(char **args, t_env *e, int cs);

/*
**	Responses
*/
void	res_msz(char *buf_write);
void	res_bct(char *buf_write, int x, int y);
void	res_mct(char *buf_write);
void	res_tna(char *buf_write);
void	res_pnw(char *buf_write);
void	res_ppo(char *buf_write, int player);
void	res_plv(char *buf_write, int player);
void	res_pin(char *buf_write, int player);
void	res_pex(char *buf_write, int player);
void	res_pbc(char *buf_write, int player);
void	res_pic(char *buf_write, int x, int y, int l, int *players);
void	res_pie(char *buf_write, int x, int y, int result);
void	res_pfk(char *buf_write, int player);
void	res_pdr(char *buf_write, int player, int i);
void	res_pgt(char *buf_write, int player, int i);
void	res_pdi(char *buf_write, int player);
void	res_enw(char *buf_write, int egg, int player, int x, int y);
void	res_eht(char *buf_write, int egg);
void	res_ebo(char *buf_write, int egg);
void	res_edi(char *buf_write, int egg);
void	res_sgt(char *buf_write);
void	res_seg(char *buf_write, char *team);
void	res_smg(char *buf_write, char *message);
void	res_suc(char *buf_write);
void	res_sbp(char *buf_write);

#endif
