/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:41 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/04 23:05:44 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/select.h>
# include "libft.h"

#define CONNEXION_QUEUE   42

# define FD_FREE          0
# define FD_BOT_SERVER    1
# define FD_GFX_SERVER    2
# define FD_BOT_CLIENT    3
# define FD_GFX_CLIENT    4

# define FD_SERVER        1
# define FD_CLIENT        3

# define DEFAULT_BOT_PORT 1942
# define DEFAULT_GFX_PORT 1984
# define DEFAULT_WIDTH    30
# define DEFAULT_HEIGHT   20
# define DEFAULT_LIMIT    10
# define DEFAULT_T        7

# define MAX_WIDTH  100
# define MAX_HEIGHT 100
# define MAX_LIMIT  20
# define MAX_T      100

# define BUF_SIZE   4096

# define DEFAULT   "\033[0m"
# define HIGHLIGHT "\033[1m"
# define UNDERLINE "\033[4m"
# define BLINK     "\033[5m"

# define BLACK     "\033[30m"
# define RED       "\033[31m"
# define GREEN     "\033[32m"
# define YELLOW    "\033[33m"
# define BLUE      "\033[34m"
# define PURPLE    "\033[35m"
# define CYAN      "\033[36m"
# define WHITE     "\033[37m"

# define MAX(a, b) (a > b ? a : b);
# define MIN(a, b) (a < b ? a : b);

# define OBJ_NB    7
# define OBJ_FOOD  0
# define OBJ_ROCK1 1
# define OBJ_ROCK2 2
# define OBJ_ROCK3 3
# define OBJ_ROCK4 4
# define OBJ_ROCK5 5
# define OBJ_ROCK6 6

typedef struct rlimit	t_rlimit;

typedef struct	s_opt
{
	char		*prog_name;
	int			bot_port;
	int			gfx_port;
	int			width;
	int			height;
	t_list		*team_name;
	int			limit;
	int			t;
}				t_opt;

typedef struct	s_gfx
{
	int			fd;
}				t_gfx;

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

typedef struct	s_team
{
	char		*name;
	int			limit;
	int			nb_bot;
}				t_team;

typedef struct	s_bot
{
	int			fd;
}				t_bot;

typedef struct	s_obj
{
	int			type;
	int			lock;
}				t_obj;

typedef struct	s_sq
{
	t_list		*obj;
	t_list		*bot;
}				t_sq;

typedef struct	s_env
{
	t_opt		opt;

	int			maxfd;
	int			max;
	int			res;
	fd_set		fd_read;
	fd_set		fd_write;
	int			gfx_srv;
	int			bot_srv;
	t_fd		*fds;

	t_list		*gfx_lst;

	int			n_sq;
	t_list		*team;
	t_list		*bot_lst;
	t_sq		*board;
}				t_env;

typedef void (*t_accept)(t_env *);

int				try_int(int res, int err, char *str);
void			*try_void(void *res, void *err, char *str);
int				sq_rand(t_env *e);

void			get_opt(int ac, char **av, t_opt *opt);

void			fd_clean(t_fd *fd);
void			fd_watch(t_env *e, int fd);
void			fd_check(t_env *e, int fd);
void			fd_iter_all(t_env *e, void (*fct)());

t_obj			*obj_new(int type);
t_bot			*bot_new(int fd);
void			bot_destroy(t_env *e, int fd, char *msg);
t_gfx			*gfx_new(int fd);
void			gfx_destroy(t_env *e, int fd, char *msg);

void			client_read(t_env *e, int cs);
void			client_write(t_env *e, int cs);

void			init_connection(t_env *e);
void			init_game(t_env *e);

void			parse_request(char *str, t_env *e, int cs);

#endif
