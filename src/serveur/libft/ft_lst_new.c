/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:47 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:47 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lst_new(void *content)
{
	t_list		*new_lst;

	if ((new_lst = (t_list *)ft_memalloc(sizeof(*new_lst))) == NULL)
		return (NULL);
	new_lst->len = 0;
	new_lst->curr = NULL;
	if (content != NULL)
		ft_lst_push(new_lst, content);
	return (new_lst);
}
