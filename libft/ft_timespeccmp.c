/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_timespeccmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:54 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/23 19:08:54 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

int		ft_timespeccmp(struct timespec t1, struct timespec t2)
{
	if ((t1.tv_sec < t2.tv_sec)
			|| (t1.tv_sec == t2.tv_sec && t1.tv_nsec < t2.tv_nsec))
		return (1);
	else if ((t1.tv_sec > t2.tv_sec)
			|| (t1.tv_sec == t2.tv_sec && t1.tv_nsec > t2.tv_nsec))
		return (-1);
	return (0);
}
