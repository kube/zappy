/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_buf.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseguin <lseguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/25 11:34:20 by lseguin           #+#    #+#             */
/*   Updated: 2014/06/26 11:47:26 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "server.h"

t_buf	*buf_new(void)
{
	t_buf	*buf;

	if ((buf = malloc(sizeof(t_buf))) == NULL)
		return (NULL);
	if ((buf->list = ft_lst_new(NULL)) == NULL)
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}

int		buf_load(t_buf *buffer, char *str)
{
	int		len;
	char	*tmp;

	if (str == NULL || ft_strlen(str) > BUF_SIZE || buffer == NULL
			|| buffer->list == NULL)
		return (-1);
	len = ft_strlen(str);
	if (str[len - 1] != '\n')
	{
		tmp = ft_strnew(len + 1);
		ft_strcpy(tmp, str);
		tmp[len] = '\n';
	}
	else
		tmp = ft_strdup(str);
	if (tmp == NULL)
		return (-1);
	ft_lst_pushend(buffer->list, tmp);
	return (0);
}

int		buf_unload(t_buf *buffer, char *res)
{
	char	*tmp;

	if (res == NULL || buffer == NULL || buffer->list == NULL)
		return (-1);
	if (!(tmp = (char *)ft_lst_pop_content(buffer->list)))
		return (-1);
	ft_strcpy(res, tmp);
	free(tmp);
	return (0);
}

int		buf_len(t_buf *buffer)
{
	if (buffer == NULL || buffer->list == NULL)
		return (-1);
	return ((int)buffer->list->len);
}
