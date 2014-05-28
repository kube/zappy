/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:49 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:49 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*u8_b;

	u8_b = (unsigned char *)b;
	while (len--)
		*u8_b++ = (unsigned char)c;
	return (b);
}
