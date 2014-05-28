/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfilename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:45 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:45 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getfilename(char *path)
{
	char	*p;

	if (ft_strequ(path, "/"))
		return (path);
	if ((p = ft_strrchr(path, '/')) == NULL)
		return (path);
	return (++p);
}
