/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:48 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:48 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*u8_s;

	u8_s = (const unsigned char *)s;
	while (n--)
	{
		if (*u8_s == (unsigned char)c)
			return ((void *)u8_s);
		else
			u8_s++;
	}
	return (NULL);
}
