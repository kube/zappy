/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:01:00 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:01:00 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	**ft_lst_to_tab(t_list *list)
{
	void	**tab;
	void	*content;
	int		i;

	if (!(tab = (void **)malloc(sizeof(void *) * (list->len + 1))))
		return (NULL);
	i = 0;
	while ((content = ft_lst_next_content(list)))
		tab[i++] = content;
	tab[i] = NULL;
	return (tab);
}
