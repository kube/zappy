/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:01:03 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:01:03 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

char	*ft_strmcat(char *dest, ...)
{
	va_list		ap;
	char		*src;

	va_start(ap, dest);
	while ((src = va_arg(ap, char *)))
		ft_strcat(dest, src);
	va_end(ap);
	return (dest);
}
