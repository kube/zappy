/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_raw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:01:04 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:01:04 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

static size_t	count_substr(char const *s, char c)
{
	size_t			i;
	unsigned int	num;

	i = 0;
	num = 0;
	while (s[i])
	{
		if (s[i] == c)
			num++;
		i++;
	}
	if (num == 0 && s[0] == '\0')
		return (0);
	return (num + 1);
}

char			**ft_strsplit_raw(char const *s, char c)
{
	size_t			i;
	unsigned int	num;
	char			**tab;
	const char		*p1;
	const char		*p2;

	num = count_substr(s, c);
	if ((tab = (char **)ft_memalloc(sizeof(*tab) * (num + 1))) == NULL)
		return (NULL);
	i = 0;
	p1 = s;
	while (i < num)
	{
		if ((p2 = ft_strchr(p1, c)) == NULL)
			p2 = s + ft_strlen(s);
		if ((tab[i] = ft_strndup(p1, p2 - p1)) == NULL)
		{
			ft_free_strtab(tab);
			return (NULL);
		}
		p1 = p2 + 1;
		i++;
	}
	return (tab);
}
