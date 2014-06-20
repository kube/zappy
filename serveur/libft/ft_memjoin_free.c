/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:49 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:49 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memjoin_free(const void *s1, size_t l1, const void *s2, size_t l2)
{
	char	*s;
	char	*str1;
	char	*str2;

	str1 = (char *)s1;
	str2 = (char *)s2;
	s = (char *)ft_memalloc(l1 + l2);
	ft_memcpy(s, str1, l1);
	ft_memcpy(s + l1, str2, l2);
	free(str1);
	free(str2);
	return (s);
}
