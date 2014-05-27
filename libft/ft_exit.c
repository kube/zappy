/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:56 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:00:56 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void			ft_exit(char *errmsg, int errcode)
{
	if (errmsg != NULL)
	{
		ft_putstr_fd(errmsg, 2);
		if (errcode > -1)
			ft_putstr_fd(": ", 2);
		else
			ft_putstr_fd("\n", 2);
	}
	if (errcode > -1)
	{
		ft_putstr_fd(ft_strerror(errcode), 2);
		ft_putstr_fd("\n", 2);
	}
	exit(errcode);
}
