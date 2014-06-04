/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sq_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 16:18:50 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/04 15:48:53 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
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
