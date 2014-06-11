/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:53:13 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/11 17:24:55 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int			get_north(t_env *e, int sq)
{
	sq -= e->opt.width;
	if (sq < 0)
		sq += e->n_sq;
	return (sq);
}

int			get_south(t_env *e, int sq)
{
	sq += e->opt.width;
	if (sq >= e->n_sq)
		sq -= e->n_sq;
	return (sq);
}

int			get_east(t_env *e, int sq)
{
	sq++;
	if (sq % e->opt.width == 0)
		sq -= e->opt.width;
	return (sq);
}

int			get_west(t_env *e, int sq)
{
	if (sq % e->opt.width == 0)
		sq += e->opt.width;
	sq--;
	return (sq);
}
