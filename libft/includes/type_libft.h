/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_libft.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:01:10 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:01:10 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_LIBFT_H
# define TYPE_LIBFT_H

# include <string.h>

typedef struct		s_atom
{
	void			*content;
	struct s_atom	*next;
	struct s_atom	*prev;
}					t_atom;

typedef struct		s_atomp
{
	t_atom			*atom;
	int				pos;
}					t_atomp;

typedef struct		s_list
{
	t_atom			*first;
	t_atom			*last;
	t_atom			*curr;
	size_t			len;
}					t_list;

typedef t_atom		*t_iterator;
typedef int			(*t_cmp) (const void *, const void *);

#endif
