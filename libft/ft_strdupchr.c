/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:01:02 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:01:02 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdupchr(const char *s, char c)
{
	char	*str;
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (s[i] != c && s[i])
		i++;
	if (!(str = ft_strnew(i)))
		return (NULL);
	while (n < i)
	{
		str[n] = s[n];
		n++;
	}
	return (str);
}
