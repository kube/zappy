/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:51 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:51 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*str;

	if ((str = (char *)malloc(ft_strlen(s1) + 1)) == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		str[i++] = *s1++;
	str[i] = '\0';
	return (str);
}
