/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_popend_content.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseguin <lseguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/25 12:12:16 by lseguin           #+#    #+#             */
/*   Updated: 2014/06/25 12:57:17 by lseguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_lst_popend_content(t_list *list)
{
	t_atom	*atom;
	void	*content;

	atom = ft_lst_popend(list);
	content = atom->content;
	free(atom);
	return (content);
}
