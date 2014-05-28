/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_request.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/28 02:26:49 by cfeijoo           #+#    #+#             */
/*   Updated: 2014/05/28 15:58:39 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <string.h>
#include "libft.h"
#include "server.h"
#include "requests.h"

void			parse_request(char *str, t_env *e, int cs)
{
	char		**req;

	req = ft_strsplit(str, ' ');
	if (ft_strequ(req[0], "msz"))
		req_msz(req + 1, e, cs);
	else if (ft_strequ(req[0], "bct"))
		req_bct(req + 1, e, cs);
	else if (ft_strequ(req[0], "mct"))
		req_mct(req + 1, e, cs);
	else if (ft_strequ(req[0], "sgt"))
		req_sgt(req + 1, e, cs);
	else if (ft_strequ(req[0], "sst"))
		req_sst(req + 1, e, cs);
	else if (ft_strequ(req[0], "tna"))
		req_tna(req + 1, e, cs);
	else if (ft_strequ(req[0], "ppo"))
		req_ppo(req + 1, e, cs);
	else if (ft_strequ(req[0], "plv"))
		req_plv(req + 1, e, cs);
	else if (ft_strequ(req[0], "pin"))
		req_pin(req + 1, e, cs);
}
