/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:52 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:52 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdarg.h>

char	*ft_strmjoin(int freeflag, ...)
{
	va_list		ap;
	char		*src;
	char		*dest;
	int			i;

	va_start(ap, freeflag);
	dest = ft_strnew(0);
	i = 0;
	while ((src = va_arg(ap, char *)))
	{
		dest = ft_strjoin(dest, src, 1);
		if ((freeflag >> i) & 0x1)
			free(src);
		i++;
	}
	va_end(ap);
	return (dest);
}
