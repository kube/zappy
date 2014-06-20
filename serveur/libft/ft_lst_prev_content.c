/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_prev_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:47 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:47 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_lst_prev_content(t_list *lst)
{
	if (!lst->curr)
	{
		lst->curr = lst->last;
		if (lst->curr)
			return (lst->curr->content);
		return (NULL);
	}
	lst->curr = lst->curr->prev;
	if (lst->curr)
		return (lst->curr->content);
	return (NULL);
}
