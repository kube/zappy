/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:56 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:00:56 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned char	neg;
	int				nb;

	neg = 0;
	nb = 0;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	if (ft_isdigit((int)*str) == 0 && *str != '-' && *str != '+')
		return (0);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = 1;
		str++;
		if (ft_isdigit((int)*str) == 0)
			return (0);
	}
	while (*str == '0')
		str++;
	while (ft_isdigit((int)*str))
		nb = nb * 10 + *str++ - '0';
	if (neg)
		nb *= -1;
	return (nb);
}
