/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_atom_index.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:58 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:00:58 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		ft_lst_atom_index(t_list *lst, t_atom *atom)
{
	int			i;
	t_atom		*atom_lst;

	if (!atom)
		return (0);
	i = 1;
	atom_lst = lst->first;
	while (atom_lst)
	{
		if (atom_lst == atom)
			return (i);
		i++;
		atom_lst = atom_lst->next;
	}
	return (-1);
}

int		ft_lst_curr_index(t_list *lst)
{
	return (ft_lst_atom_index(lst, lst->curr));
}
