/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_iter_rev.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:58 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:00:58 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_iter_rev(t_list *lst, void (*f)(), void *param)
{
	int		i;
	t_atom	*atom;
	t_atom	*prev;

	i = 0;
	atom = lst->last;
	while (atom)
	{
		prev = atom->prev;
		f(atom->content, param, i);
		atom = prev;
		i++;
	}
}
