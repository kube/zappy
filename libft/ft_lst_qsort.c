/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_qsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:59 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:00:59 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static void		next_atomp(t_atomp *atomp)
{
	atomp->atom = atomp->atom->next;
	atomp->pos++;
}

static void		prev_atomp(t_atomp *atomp)
{
	atomp->atom = atomp->atom->prev;
	atomp->pos--;
}

static t_atomp	partitionner_list(t_atomp p, t_atomp r, int cmp())
{
	void	*pivot;

	pivot = p.atom->content;
	prev_atomp(&p);
	next_atomp(&r);
	while (1)
	{
		prev_atomp(&r);
		while (r.atom->content != pivot && cmp(r.atom->content, pivot) > 0)
			prev_atomp(&r);
		next_atomp(&p);
		while (p.atom->content != pivot && cmp(p.atom->content, pivot) < 0)
			next_atomp(&p);
		if (p.pos < r.pos)
			ft_lst_swap_atom(p.atom, r.atom);
		else
			return (r);
	}
}

static void		ft_quicksort_list_extend(t_atomp p, t_atomp r, int cmp())
{
	t_atomp		q;

	if (p.pos < r.pos)
	{
		q = partitionner_list(p, r, cmp);
		ft_quicksort_list_extend(p, q, cmp);
		next_atomp(&q);
		ft_quicksort_list_extend(q, r, cmp);
	}
}

void			ft_lst_qsort(t_list *l, int cmp())
{
	t_atomp		atompf;
	t_atomp		atompl;

	if (l->len < 2)
		return ;
	atompf = ft_atomp_new(l->first, 0);
	atompl = ft_atomp_new(l->last, l->len - 1);
	ft_lst_pushend(l, NULL);
	ft_lst_push(l, NULL);
	ft_quicksort_list_extend(atompf, atompl, cmp);
	ft_lst_del_atom(l, l->first, NULL);
	ft_lst_del_atom(l, l->last, NULL);
}
