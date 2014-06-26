/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_after_atom.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:47 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:47 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lst_push_after_atom(t_list *lst, void *content, t_atom *atom)
{
	t_atom		*new_atom;
	t_atom		*tmp_atom;

	if (atom)
	{
		if (!(new_atom = ft_atom_new(content)))
			return ;
		tmp_atom = atom->next;
		atom->next = new_atom;
		new_atom->next = tmp_atom;
		new_atom->prev = atom;
		if (tmp_atom)
			tmp_atom->prev = new_atom;
		if (atom == lst->last)
			lst->last = new_atom;
		lst->len++;
	}
	else
		ft_lst_push(lst, content);
}
