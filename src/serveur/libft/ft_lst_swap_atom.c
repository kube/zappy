/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_swap_atom.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:48 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:48 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lst_swap_atom(t_atom *atom1, t_atom *atom2)
{
	void	*val;

	val = atom1->content;
	atom1->content = atom2->content;
	atom2->content = val;
}
