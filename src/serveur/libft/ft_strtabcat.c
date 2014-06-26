/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:53 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 16:54:25 by lseguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtabcat(char *dest, char **src, char *sep)
{
	int		i;
	int		len;
	int		len_sep;

	i = 0;
	len = ft_strlen(dest);
	len_sep = (sep ? ft_strlen(sep) : 0);
	while (src[i])
	{
		ft_strcpy(dest + len, src[i]);
		len += ft_strlen(src[i]);
		if (len_sep && src[i + 1])
		{
			ft_strcpy(dest + len, sep);
			len += len_sep;
		}
		i++;
	}
	return (dest);
}
