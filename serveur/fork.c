/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 12:25:11 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 12:25:33 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			fork_egg(t_env *e, t_bot *bot)
{
	bot->action_timer = FORK_TIME;
	bot->status = STATUS_FORK;
	notify_all_gfx_pfk(e, bot);
	ft_strcat(bot->buf_action, "ok\n");
}
