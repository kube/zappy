/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_iter_next_content.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:58 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:00:58 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_lst_iter_next_content(t_list *lst, t_iterator *iterator)
{
	if (!*iterator)
	{
		*iterator = lst->first;
		if (*iterator)
			return ((*iterator)->content);
		return (NULL);
	}
	if ((*iterator = (*iterator)->next))
		return ((*iterator)->content);
	return (NULL);
}
