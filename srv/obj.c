/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 19:29:42 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/04 19:33:50 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "server.h"

t_obj		*obj_new(int type)
{
	t_obj		*new;

	new = (t_obj *)try_void(malloc(sizeof(t_obj)), NULL, "malloc");
	new->type = type;
	new->lock = 0;
	return (new);
}
