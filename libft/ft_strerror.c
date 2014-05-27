/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:01:03 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:01:03 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strerror(int errcode)
{
	char		*errmsg[9];

	errmsg[FT_ERR_NO_ERROR] = "No error";
	errmsg[FT_ERR_MALLOC] = "Cannot allocate memary";
	errmsg[FT_ERR_EXIST] = "No such file or directory";
	errmsg[FT_ERR_FORK] = "Cannot fork process";
	errmsg[FT_ERR_PROCESS] = "Process error";
	errmsg[FT_ERR_PIPE] = "Pipe error";
	errmsg[FT_ERR_ACCESS] = "Access denied";
	errmsg[FT_ERR_OPEN] = "Open error";
	errmsg[FT_ERR_CMD_NOT_FOUND] = "Command not found";
	return (errmsg[errcode]);
}
