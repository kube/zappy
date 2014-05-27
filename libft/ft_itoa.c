/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:57 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:00:57 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	buff[12];
	char	*p;
	int		neg;

	ft_bzero(buff, sizeof(char) * 12);
	neg = 0;
	p = buff + 11;
	if (n == 0)
		*--p = '0';
	else
	{
		if (n < 0)
			neg = 1;
		while (n != 0)
		{
			if (n < 0)
				*--p = '0' - (n % 10);
			else
				*--p = '0' + (n % 10);
			n /= 10;
		}
		if (neg)
			*--p = '-';
	}
	return (ft_strdup(p));
}
