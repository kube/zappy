/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:44 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:44 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_atoi_size(char *str, int i)
{
	char	*s;
	int		res;

	s = ft_strndup(str, i);
	res = ft_atoi(s);
	ft_strdel(&s);
	return (res);
}

float		ft_atof(char *str)
{
	float		tmp;
	float		val;
	int			i;
	int			flag;

	i = 0;
	val = (float)ft_atoi(str);
	flag = (str[0] == '-' ? -1 : 1);
	while (*str && *str != '.' && *str != ',')
		str++;
	if (!*str++)
		return (val);
	while (ft_isdigit(str[i]) && i < 9)
		(i)++;
	if (!i)
		return (val);
	while (--(i) >= 0 && str[i] == '0')
		;
	tmp = (float)ft_atoi_size(str, ++(i));
	if (tmp <= 0)
		return (val);
	tmp /= (float)ft_power(10, i);
	val = val + (tmp * flag);
	return (val);
}
