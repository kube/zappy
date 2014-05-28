/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:50 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:50 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_qsort(void *base, size_t nel, size_t width, \
			int (*compar)(const void *, const void *))
{
	size_t		i;
	int			ischange;
	void		*a;
	void		*b;

	ischange = 1;
	while (ischange)
	{
		i = 0;
		ischange = 0;
		while (i < nel - 1)
		{
			a = (base + (i * width));
			b = (base + ((i + 1) * width));
			if (compar(a, b))
			{
				ischange = 1;
				ft_swap(a, b);
			}
			i++;
		}
	}
}
