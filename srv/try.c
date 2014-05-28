/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:41 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/28 15:56:06 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int		try_int(int res, int err, char *str)
{
	if (res == err)
	{
		fprintf(stderr, "ERROR [ %s ] : %s\n", str, strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (res);
}

void	*try_void(void *res, void *err, char *str)
{
	if (res == err)
	{
		fprintf(stderr, "ERROR [ %s ] : %s\n", str, strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (res);
}
