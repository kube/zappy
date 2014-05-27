/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secure_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:01:02 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:01:02 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int		ft_secure_pipe(int fd[2], char *prog_name)
{
	int		ret;

	if ((ret = pipe(fd)) < 0)
		ft_exit(prog_name, FT_ERR_PIPE);
	return (1);
}
