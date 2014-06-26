/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_before_atom.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:47 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:47 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lst_push_before_atom(t_list *lst, void *content, t_atom *atom)
{
	t_atom		*new_atom;
	t_atom		*tmp_atom;

	if (!(new_atom = ft_atom_new(content)))
		return ;
	if (atom)
	{
		tmp_atom = atom->prev;
		atom->prev = new_atom;
		new_atom->prev = tmp_atom;
		new_atom->next = atom;
		if (tmp_atom)
			tmp_atom->next = new_atom;
		if (atom == lst->first)
			lst->first = new_atom;
		lst->len++;
	}
	else
		ft_lst_pushend(lst, content);
}
