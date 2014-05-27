/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:01:00 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:01:00 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memdup(const void *s, size_t n)
{
	void	*new;

	if ((new = (void *)malloc(n)) == NULL)
		return (NULL);
	return (ft_memcpy(new, s, n));
}
