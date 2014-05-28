/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:41 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/28 03:48:21 by cfeijoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/select.h>
# include "libft.h"

# define FD_FREE 0
# define FD_CLIENT 1
# define FD_SERVER 2
# define FD_GRAFX 3

# define BUF_SIZE 4096

# define USAGE "Usage: %s port\n"

typedef struct rlimit	t_rlimit;

typedef struct	s_fd
{
	int			type;
	void		(*fct_read)();
	void		(*fct_write)();
	char		buf_read[BUF_SIZE + 1];
	char		buf_write[BUF_SIZE + 1];
	char		*addr;
	int			port;
}				t_fd;

typedef struct	s_env
{
	int			port;
	int			maxfd;
	t_fd		*fds;
	t_fd		*srv;
	int			nb_user;
	fd_set		fd_read;
	fd_set		fd_write;
	int			max;
	int			res;
}				t_env;

int				try_int(int res, int err, char *str);
void			*try_void(void *res, void *err, char *str);

void			fd_destroy(t_env *e, int cs, char *msg);
void			fd_clean(t_fd *fd);
void			fd_init(t_env *e);
void			fd_check(t_env *e);

void			client_read(t_env *e, int cs);
void			client_write(t_env *e, int cs);

void			parse_request(char *str, t_env *e, int cs);

#endif
