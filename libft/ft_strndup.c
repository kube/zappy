/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:01:04 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:01:04 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	len;
	char	*str;
	size_t	i;

	len = ft_strlen(s1);
	if (n < len)
		len = n;
	if ((str = ft_strnew(len)) == NULL)
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = *s1++;
	return (str);
}
