/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:01:05 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:01:05 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strtrim(char const *s)
{
	int		len;
	int		endchar;
	int		startchar;

	if (!s)
		return (NULL);
	endchar = 0;
	startchar = 0;
	len = ft_strlen(s);
	while (ft_iswhitespace(s[len - 1 - endchar]))
		endchar++;
	while (ft_iswhitespace(s[startchar]))
		startchar++;
	if ((len - startchar - endchar) <= 0)
		return (ft_strnew(0));
	return (ft_strsub(s, startchar, (size_t) (len - startchar - endchar)));
}
