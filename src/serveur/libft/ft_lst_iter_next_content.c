/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_iter_next_content.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:47 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:47 by vdefilip         ###   ########.fr       */
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
