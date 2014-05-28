/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:47 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:47 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_push(t_list *lst, void *content)
{
	t_atom	*new_atom;

	new_atom = ft_atom_new(content);
	if (lst->first == NULL || lst->last == NULL)
	{
		lst->first = new_atom;
		lst->last = new_atom;
		lst->len = 1;
	}
	else
	{
		lst->first->prev = new_atom;
		new_atom->next = lst->first;
		lst->first = new_atom;
		lst->len++;
	}
}
