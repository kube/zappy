/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:51 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:51 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		n;
	size_t		dst_len;

	d = dst;
	s = src;
	n = size;
	while (n-- && *d != '\0')
		d++;
	dst_len = d - dst;
	n = size - dst_len;
	if (n == 0)
		return (dst_len + ft_strlen(src));
	while (n-- > 1 && *s != '\0')
		*d++ = *s++;
	*d = '\0';
	return (dst_len + ft_strlen(src));
}
