/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 16:18:50 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 18:49:42 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int			sq_rand(t_env *e)
{
	static int		first = 1;

	if (first)
	{
		first = 0;
		srand(time(NULL));
	}
	return (rand() % e->n_sq);
}

int			dir_rand(void)
{
	static int		first = 1;

	if (first)
	{
		first = 0;
		srand(time(NULL));
	}
	return ((rand() % 4) + 1);
}
