/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atomp_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:44 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:44 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_atomp		ft_atomp_new(t_atom *atom, int pos)
{
	t_atomp		atomp;

	atomp.atom = atom;
	atomp.pos = pos;
	return (atomp);
}
