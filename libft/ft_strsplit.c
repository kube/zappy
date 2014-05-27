/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
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

static void		*free_tab(char **tab, size_t size)
{
	unsigned int	i;

	i = 0;
	while (i < size)
		ft_strdel(tab + i);
	free(tab);
	return (NULL);
}

static size_t	count_substr(char const *s, char c)
{
	size_t			i;
	unsigned int	num;
	char			prev_c;

	num = 0;
	i = 0;
	prev_c = c;
	while (s[i])
	{
		if (prev_c == c && s[i] != c)
			num++;
		prev_c = s[i];
		i++;
	}
	return (num);
}

char			**ft_strsplit(char const *s, char c)
{
	char			**tab;
	size_t			i;
	unsigned int	num;
	unsigned int	start;
	unsigned int	end;

	num = count_substr(s, c);
	if ((tab = (char **)malloc(sizeof(*tab) * (num + 1))) == NULL)
		return (NULL);
	start = 0;
	end = 0;
	i = 0;
	while (i < num)
	{
		if ((end == 0 || s[end - 1] == c) && s[end] != c && s[end] != '\0')
			start = end;
		if ((end != 0 && s[end - 1] != c) && (s[end] == c || s[end] == '\0'))
		{
			if ((tab[i++] = ft_strsub(s, start, end - start)) == NULL)
				return (free_tab(tab, i));
		}
		end++;
	}
	tab[i] = NULL;
	return (tab);
}
