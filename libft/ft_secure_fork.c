/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secure_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:50 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:50 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int		ft_secure_fork(char *prog_name)
{
	int		pid;

	if ((pid = fork()) < 0)
		ft_exit(prog_name, FT_ERR_FORK);
	return (pid);
}
