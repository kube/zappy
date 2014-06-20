/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:46 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:46 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lst_cpy(t_list *lst)
{
	t_list		*new_lst;
	t_atom		*atom;

	if ((new_lst = ft_lst_new(NULL)) == NULL)
		return (NULL);
	atom = lst->first;
	while (atom)
	{
		ft_lst_pushend(new_lst, atom->content);
		atom = atom->next;
	}
	return (new_lst);
}
