/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 15:06:39 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/03 17:51:24 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "server.h"

void			board_fill(t_env *e)
{
	(void)e;
}

void			board_create(t_env *e)
{
	int		n;
	int		size;
	int		i;

	n = e->opt.height * e->opt.width;
	size = sizeof(t_list *) * n;
	e->board = (t_list **)try_void(ft_memalloc(size), NULL, "malloc");
	i = 0;
	while (i < n)
	{
		e->board[i] = ft_lst_new(NULL);
		i++;
	}
	board_fill(e);
}
