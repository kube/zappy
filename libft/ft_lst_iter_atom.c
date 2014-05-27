/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_iter_atom.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:58 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:00:58 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_iter_atom(t_list *lst, void (*f)(), void *param)
{
	int		i;
	t_atom	*atom;
	t_atom	*next;

	i = 0;
	atom = lst->first;
	while (atom)
	{
		next = atom->next;
		f(atom, param, i);
		atom = next;
		i++;
	}
}
