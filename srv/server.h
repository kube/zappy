/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:41 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/19 16:28:45 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/select.h>
# include "libft.h"

#define CONNEXION_QUEUE   42

# define FD_FREE          0
# define FD_SRV           1
# define FD_BOT_SRV       2
# define FD_GFX_SRV       3
# define FD_CLIENT        4
# define FD_BOT_CLIENT    5
# define FD_GFX_CLIENT    6

# define DEFAULT_BOT_PORT 1984
# define DEFAULT_GFX_PORT 1984
# define DEFAULT_W        30
# define DEFAULT_H        20
# define DEFAULT_LIMIT    10
# define DEFAULT_T        100

# define MIN_W      10
# define MIN_H      10
# define MAX_W      100
# define MAX_H      100
# define MAX_LIMIT  20
# define MAX_T      100

# define BUF_SIZE   65536

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
# define TURN_RIGHT_TIME 7
# define TURN_LEFT_TIME 7
# define LOOK_TIME 7
# define INVENTORY_TIME 1
# define TAKE_TIME 7
# define PUT_TIME 7
# define EXPULSE_TIME 7
# define BROADCAST_TIME 7
# define INCANTATION_TIME 300
# define FORK_TIME 42

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
	int			id;
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
	long		timer;
	long		food_timer;
	long		action_timer;
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
	t_fd		*fds;
	int			srv;
	int			gfx_srv;
	int			bot_srv;
	t_list		*client_lst;
	t_list		*gfx_lst;
	int			n_sq;
	t_list		*team;
	t_list		*bot_fd_lst;
	t_sq		*board;
}				t_env;

int				try_int(int res, int err, char *str);
void			*try_void(void *res, void *err, char *str);
int				sq_rand(t_env *e);
int				dir_rand();

void			get_opt(int ac, char **av, t_opt *opt);

void			fd_destroy(t_env *e, int fd, char *msg);
void			fd_clean(t_fd *fd);
void			fd_watch(t_env *e, int fd);
void			fd_check(t_env *e, int fd);
void			fd_iter_all(t_env *e, void (*fct)());

t_obj			*obj_new(int type);
t_bot			*bot_new(t_team *team);
void			bot_iter_all_connected_and_queued(t_env *e, void (*fct)());
t_bot			*get_bot_by_fd(t_env *e, int fd);
t_bot			*get_bot_by_id(t_env *e, int id);
void			bot_destroy(t_env *e, int fd, char *msg);
t_gfx			*gfx_new(int fd);
void			gfx_destroy(t_env *e, int fd, char *msg);

void			gfx_connection(t_env *e, int fd);
void			bot_connection(t_env *e, int fd, char *team_name);

void			client_read(t_env *e, int cs);
void			client_write(t_env *e, int cs);

void			init_connection(t_env *e);
void			init_game(t_env *e);
void 			print_board(t_env *e);

void			bot_parse_request(t_env *e, int cs, char *str);
void			gfx_parse_request(t_env *e, int fd, char *str);

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

void			msz(t_env *e, int fd);
void			bct(t_env *e, int fd, char **req, int square);
void			mct(t_env *e, int fd);
void			tna(t_env *e, int fd);
void			ppo(t_env *e, int fd, char **req, t_bot *b);
void			plv(t_env *e, int fd, char **req, t_bot *b);
void			pin(t_env *e, int fd, char **req, t_bot *b);
void			sgt(t_env *e, int fd);
void			sst(t_env *e, int fd, char **req);

void			pnw(t_env *e, int fd, t_bot *bot);
void			pex(t_env *e, int fd, t_bot *bot);
void			pbc(t_env *e, int fd, t_bot *bot, char *msg);
void			pic(t_env *e, int fd, t_bot *bot, int *ids);
void			pie(t_env *e, int fd, t_bot *bot, int res);
void			pfk(t_env *e, int fd, t_bot *bot);
void			pdr(t_env *e, int fd, t_bot *bot, int type);
void			pgt(t_env *e, int fd, t_bot *bot, int type);
void			pdi(t_env *e, int fd, t_bot *bot);
void			enw(t_env *e, int fd, t_bot *bot, t_bot *new_bot);
void			eht(t_env *e, int fd, t_bot *bot);
void			ebo(t_env *e, int fd, t_bot *bot);
void			edi(t_env *e, int fd, t_bot *bot);
void			seg(t_env *e, int fd, t_team *team);
void			smg(t_env *e, int fd, char *msg);
void			suc(t_env *e, int fd);
void			sbp(t_env *e, int fd);

void			notify_all_gfx_pnw(t_env *e, t_bot *bot);
void			notify_all_gfx_ppo(t_env *e, t_bot *bot);
void			notify_all_gfx_take(t_env *e, t_bot *bot, int type);
void			notify_all_gfx_put(t_env *e, t_bot *bot, int type);
void			notify_all_gfx_pdi(t_env *e, t_bot *bot);

#endif
