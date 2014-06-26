/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:53 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:53 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_tabrev(void *tab, size_t len, size_t width)
{
	size_t	i;
	size_t	j;
	char	*first;
	char	*last;
	char	tmp;

	i = 0;
	first = tab;
	last = tab + ((len - 1) * width);
	while (i < len / 2)
	{
		j = 0;
		while (j < width)
		{
			tmp = *(first + j);
			*(first + j) = *(last + j);
			*(last + j) = tmp;
			j++;
		}
		first += width;
		last -= width;
		i++;
	}
}
