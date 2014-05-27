/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_warning.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:01:05 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:01:05 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void			ft_warning(char *warnmsg, int warncode)
{
	if (warnmsg != NULL)
	{
		ft_putstr_fd(warnmsg, 2);
		if (warncode > -1)
			ft_putstr_fd(": ", 2);
		else
			ft_putstr_fd("\n", 2);
	}
	if (warncode > -1)
	{
		ft_putstr_fd(ft_strerror(warncode), 2);
		ft_putstr_fd("\n", 2);
	}
}
