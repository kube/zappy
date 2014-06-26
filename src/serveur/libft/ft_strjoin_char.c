/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:51 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:51 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin_char(char *s1, char c, int mode_free)
{
	int		len;
	char	*str;

	len = (s1 ? ft_strlen(s1) : 0);
	str = ft_strnew(len + 1);
	if (!str)
		return (NULL);
	if (s1)
		ft_strcpy(str, s1);
	*(str + len) = c;
	if (mode_free)
		free(s1);
	return (str);
}
