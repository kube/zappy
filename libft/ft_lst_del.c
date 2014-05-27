/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:58 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:00:58 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lst_del(t_list *lst, void (*del)())
{
	t_atom	*atom;
	t_atom	*atom_next;

	atom = lst->first;
	while (atom)
	{
		atom_next = atom->next;
		ft_lst_del_atom(lst, atom, del);
		atom = atom_next;
	}
	free(lst);
}
