/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:53 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:53 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtabjoin(char **src, char *sep)
{
	int		i;
	int		len;
	char	*buffer;

	i = 0;
	len = 0;
	while (src[i])
		len += ft_strlen(src[i++]);
	len += (sep ? ft_strlen(sep) * (i - 1) : 0);
	buffer = ft_strnew(len);
	return (ft_strtabcat(buffer, src, sep));
}
