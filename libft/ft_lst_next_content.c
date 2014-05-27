/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_next_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:59 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:00:59 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_lst_next_content(t_list *lst)
{
	if (!lst->curr)
	{
		lst->curr = lst->first;
		if (lst->curr)
			return (lst->curr->content);
		return (NULL);
	}
	lst->curr = lst->curr->next;
	if (lst->curr)
		return (lst->curr->content);
	return (NULL);
}
