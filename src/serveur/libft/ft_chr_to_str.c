/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chr_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:44 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:44 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_chr_to_str(char c)
{
	char	*str;

	str = ft_strnew(1);
	if (str == NULL)
		return (NULL);
	str[0] = c;
	return (str);
}
