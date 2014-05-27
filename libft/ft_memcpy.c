/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:01:00 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:01:00 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	unsigned char			*u8_s1;
	const unsigned char		*u8_s2;

	u8_s1 = (unsigned char *)s1;
	u8_s2 = (const unsigned char *)s2;
	while (n--)
		*u8_s1++ = *u8_s2++;
	return (s1);
}
