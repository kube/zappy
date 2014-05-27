/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atom_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:56 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:00:56 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_atom		*ft_atom_new(void *content)
{
	t_atom		*new_atom;

	new_atom = (t_atom *)ft_memalloc(sizeof(*new_atom));
	if (new_atom)
	{
		new_atom->content = content;
		new_atom->next = NULL;
		new_atom->prev = NULL;
	}
	return (new_atom);
}
