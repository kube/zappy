/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:49 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:49 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putptr(void *ptr)
{
	char	*str;

	str = ft_litoa_base((long int)ptr, 16, sizeof(ptr) * 2);
	str = ft_strjoin("0x", str, 2);
	ft_putstr(str);
	ft_strdel(&str);
}
