/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_popend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:47 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:47 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_atom		*ft_lst_popend(t_list *lst)
{
	t_atom		*pop;

	if (lst->curr && lst->last == lst->curr)
		lst->curr = lst->curr->prev;
	if (lst->first == NULL || lst->last == NULL)
		return (NULL);
	pop = lst->last;
	if (pop->prev == NULL)
	{
		lst->first = NULL;
		lst->last = NULL;
	}
	else
	{
		lst->last = pop->prev;
		lst->last->next = NULL;
	}
	pop->next = NULL;
	pop->prev = NULL;
	lst->len--;
	return (pop);
}
