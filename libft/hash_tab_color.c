/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tab_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:01:06 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:01:06 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		hash_color(char *str)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = (int)*str++))
	{
		if (c >= 'A' && c <= 'Z')
			c += 32;
		hash = ((hash << 5) + hash) + c;
	}
	return ((int)(hash % 4300));
}
