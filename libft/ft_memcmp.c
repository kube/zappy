/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:01:00 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:01:00 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char		*u8_s1;
	const unsigned char		*u8_s2;

	u8_s1 = (const unsigned char *)s1;
	u8_s2 = (const unsigned char *)s2;
	while (n--)
	{
		if (*u8_s1 != *u8_s2)
			return ((int)*u8_s1 - (int)*u8_s2);
		else
		{
			u8_s1++;
			u8_s2++;
		}
	}
	return (0);
}
