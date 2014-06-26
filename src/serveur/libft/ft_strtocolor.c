/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtocolor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:53 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:53 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		stringtocolor(char *str)
{
	int		*hashtab;

	hashtab = ft_loadcolor();
	return (hashtab[hash_color(str)]);
}

static int		pos_in_hex(char c)
{
	int		i;
	char	*tab;

	tab = "0123456789abcdef";
	i = 0;
	while (tab[i])
	{
		if (tab[i] == c || (i > 9 && tab[i] - 32 == c))
			return (i);
		i++;
	}
	return (-1);
}

static int		ft_hextoi(char *hex)
{
	int			ret;
	int			res;

	res = 0;
	while ((ret = pos_in_hex(*hex)) >= 0)
	{
		res = (res * 16) + ret;
		hex++;
	}
	return (res);
}

int				ft_strtocolor(char *str)
{
	if (ft_isalpha(str[0]))
		return (stringtocolor(str));
	if (str[0] == '#')
		return (ft_hextoi(str + 1));
	if (str[0] == '0' && str[1] == 'x')
		return (ft_hextoi(str + 2));
	return (ft_atoi(str));
}
