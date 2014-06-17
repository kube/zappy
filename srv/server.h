/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:41 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/17 17:48:33 by vdefilip         ###   ########.fr       */
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
# define DEFAULT_T        100

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

# define FOOD  "nourriture"
# define ROCK1 "linemate"
# define ROCK2 "deraumere"
# define ROCK3 "sibur"
# define ROCK4 "mendiane"
# define ROCK5 "phiras"
# define ROCK6 "thystame"

# define NORTH 1
# define EAST  2
# define SOUTH 3
# define WEST  4

# define FOOD_UNIT 126

# define STEP_TIME 7

typedef struct rlimit	t_rlimit;
typedef struct timeval	t_tv;
typedef unsigned long	t_ulong;

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
	t_list		*connected;
	t_list*		unconnected;
	t_list*		queue;
}				t_team;

typedef struct	s_bot
{
	int			id;
	t_team		*team;
	int			fd;
	int			sq;
	int			dir;
	int			life_unit;
	t_list		*inventory;
	int			level;
	t_tv		time;
	t_ulong		timer;
	t_ulong		food_timer;
	t_ulong		action_timer;
	char		buf_action[BUF_SIZE + 1];
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
	t_list		*bot_fd_lst;
	t_sq		*board;
}				t_env;

typedef void (*t_accept)(t_env *);

int				try_int(int res, int err, char *str);
void			*try_void(void *res, void *err, char *str);
int				sq_rand(t_env *e);
int				dir_rand();

void			get_opt(int ac, char **av, t_opt *opt);

void			fd_clean(t_fd *fd);
void			fd_watch(t_env *e, int fd);
void			fd_check(t_env *e, int fd);
void			fd_iter_all(t_env *e, void (*fct)());

t_obj			*obj_new(int type);
t_bot			*bot_new(t_team *team);
void			bot_iter_all_connected_and_queued(t_env *e, void (*fct)());
t_bot			*get_bot_by_fd(t_env *e, int fd);
void			bot_destroy(t_env *e, int fd, char *msg);
t_gfx			*gfx_new(int fd);
void			gfx_destroy(t_env *e, int fd, char *msg);

void			client_read(t_env *e, int cs);
void			client_write(t_env *e, int cs);

void			init_connection(t_env *e);
void			init_game(t_env *e);
void 			print_board(t_env *e);

void			bot_parse_request(t_env *e, int cs, char *str);

void			turn_left(t_env *e, t_bot *bot);
void			turn_right(t_env *e, t_bot *bot);
void			step(t_env *e, t_bot *bot);
void			move(t_env *e, t_bot *bot, int sq);

int				get_north(t_env *e, int sq);
int				get_south(t_env *e, int sq);
int				get_east(t_env *e, int sq);
int				get_west(t_env *e, int sq);

void			look(t_env *e, t_bot *bot);
void			get_inventory(t_env *e, t_bot *bot);
int				take(t_env *e, t_bot *bot, char *obj_name);
int				put(t_env *e, t_bot *bot, char *obj_name);

t_bot			*connect_bot(t_env *e, t_team *team);

void			timer(t_env *e, t_bot *bot);

#endif
