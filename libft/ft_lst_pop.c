/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_pop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:47 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:47 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_atom		*ft_lst_pop(t_list *lst)
{
	t_atom		*pop;

	if (lst->first == lst->curr)
		lst->curr = NULL;
	if (lst->first == NULL || lst->last == NULL)
		return (NULL);
	pop = lst->first;
	if (pop->next == NULL)
	{
		lst->first = NULL;
		lst->last = NULL;
	}
	else
	{
		lst->first = pop->next;
		lst->first->prev = NULL;
	}
	pop->next = NULL;
	pop->prev = NULL;
	lst->len--;
	return (pop);
}
