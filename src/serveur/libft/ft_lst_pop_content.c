/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_pop_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseguin <lseguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/25 11:59:08 by lseguin           #+#    #+#             */
/*   Updated: 2014/06/25 13:20:39 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_lst_pop_content(t_list *list)
{
	t_atom	*atom;
	void	*content;

	if (!(atom = ft_lst_pop(list)))
		return (NULL);
	content = atom->content;
	free(atom);
	return (content);
}
