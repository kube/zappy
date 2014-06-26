/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_iter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:46 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:46 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_iter(t_list *lst, void (*f)(), void *param)
{
	int		i;
	t_atom	*atom;
	t_atom	*next;

	i = 0;
	atom = lst->first;
	while (atom)
	{
		next = atom->next;
		f(atom->content, param, i);
		atom = next;
		i++;
	}
}
