/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:49 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:49 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	unsigned char			u8_buffer[n];

	ft_memcpy((void *)u8_buffer, s2, n);
	ft_memcpy(s1, (const void *)u8_buffer, n);
	return (s1);
}
