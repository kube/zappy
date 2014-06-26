/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/28 15:19:39 by vdefilip          #+#    #+#             */
/*   Updated: 2014/06/24 18:49:50 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void		usage(t_opt *opt)
{
	fprintf(stderr, "%s%sUsage: %s ", DEFAULT, GREEN, opt->prog_name);
	fprintf(stderr, "-n %steam1%s%s ", UNDERLINE, DEFAULT, GREEN);
	fprintf(stderr, "[ %steam2%s%s ", UNDERLINE, DEFAULT, GREEN);
	fprintf(stderr, "%s...%s%s ] ", UNDERLINE, DEFAULT, GREEN);
	fprintf(stderr, "[ -p %sport%s%s ] ", UNDERLINE, DEFAULT, GREEN);
	fprintf(stderr, "[ -g %sport%s%s ] ", UNDERLINE, DEFAULT, GREEN);
	fprintf(stderr, "[ -t %stime%s%s ] ", UNDERLINE, DEFAULT, GREEN);
	fprintf(stderr, "\n\t\t [ -x %swidth%s%s ] ", UNDERLINE, DEFAULT, GREEN);
	fprintf(stderr, "[ -y %sheight%s%s ] ", UNDERLINE, DEFAULT, GREEN);
	fprintf(stderr, "[ -c %slimit%s%s ] ", UNDERLINE, DEFAULT, GREEN);
	fprintf(stderr, "[ -h ]\n");
	fprintf(stderr, "\t-n team1 team2 ...\n");
	fprintf(stderr, "\t-p bot's client port ");
	fprintf(stderr, "(default:%d)\n", DEFAULT_BOT_PORT);
	fprintf(stderr, "\t-g gfx's client port ");
	fprintf(stderr, "(default:%d)\n", DEFAULT_GFX_PORT);
	fprintf(stderr, "\t-x map width ");
	fprintf(stderr, "(default:%d, min:%d, max:%d)\n", DEFAULT_W, MIN_W, MAX_W);
	fprintf(stderr, "\t-y map height ");
	fprintf(stderr, "(default:%d, min:%d, max:%d)\n", DEFAULT_H, MIN_H, MAX_H);
	fprintf(stderr, "\t-c bot's client limitation ");
	fprintf(stderr, "(default:%d, max:%d)\n", DEFAULT_LIMIT, MAX_LIMIT);
	fprintf(stderr, "\t-h display this help\n\t-t time unit ");
	fprintf(stderr, "(default:%d, max:%d)%s\n", DEFAULT_T, MAX_T, DEFAULT);
	exit(1);
}

static int		opt_error(char *str, int val, char *arg)
{
	fprintf(stderr, "%s", RED);
	if (arg == NULL)
		fprintf(stderr, "ERROR [ options ] : %s (%d).\n", str, val);
	else
		fprintf(stderr, "ERROR [ options ] : %s (%s).\n", str, arg);
	fprintf(stderr, "%s", DEFAULT);
	return (-1);
}

static int		check_opt(t_opt *opt)
{
	int				ret;
	t_iterator		iter;
	char			*team;

	ret = 0;
	if (opt->width < MIN_W || opt->width > MAX_W)
		ret = opt_error("Invalid width", opt->width, NULL);
	if (opt->height < MIN_H || opt->height > MAX_H)
		ret = opt_error("Invalid height", opt->height, NULL);
	if (opt->team_name->len == 0)
	{
		fprintf(stderr, "ERROR [ options ] : Missing team.\n");
		ret = -1;
	}
	iter = NULL;
	while ((team = (char *)ft_lst_iter_next_content(opt->team_name, &iter)))
	{
		if (ft_strequ(team, "GRAPHIC"))
			ret = opt_error("Invalid team name", 0, team);
	}
	if (opt->limit <= 0 || opt->limit > MAX_LIMIT)
		ret = opt_error("Invalid client limit", opt->limit, NULL);
	if (opt->t < 1 || opt->t > MAX_T)
		ret = opt_error("Invalid time", opt->t, NULL);
	return (ret);
}

static int		save_opt(char **av, t_opt *opt)
{
	int		i;

	i = 0;
	if (ft_strequ(av[i], "-p") && av[i + 1])
		opt->bot_port = atoi(av[i + 1]);
	else if (ft_strequ(av[i], "-g") && av[i + 1])
		opt->gfx_port = atoi(av[i + 1]);
	else if (ft_strequ(av[i], "-x") && av[i + 1])
		opt->width = atoi(av[i + 1]);
	else if (ft_strequ(av[i], "-y") && av[i + 1])
		opt->height = atoi(av[i + 1]);
	else if (ft_strequ(av[i], "-c") && av[i + 1])
		opt->limit = atoi(av[i + 1]);
	else if (ft_strequ(av[i], "-t") && av[i + 1])
		opt->t = atoi(av[i + 1]);
	else if (ft_strequ(av[i], "-h"))
		usage(opt);
	else if (ft_strequ(av[i], "-n") && av[i + 1])
	{
		while (av[++i] && av[i][0] != '-')
			ft_lst_pushend(opt->team_name, av[i]);
	}
	else
		return (opt_error("Invalid option", 0, av[i]));
	return (0);
}

void			get_opt(int ac, char **av, t_opt *opt)
{
	int		i;

	opt->prog_name = av[0];
	opt->bot_port = DEFAULT_BOT_PORT;
	opt->gfx_port = DEFAULT_GFX_PORT;
	opt->width = DEFAULT_W;
	opt->height = DEFAULT_H;
	opt->team_name = ft_lst_new(NULL);
	opt->limit = DEFAULT_LIMIT;
	opt->t = DEFAULT_T;
	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			if (save_opt(&av[i], opt) == -1)
				usage(opt);
		}
		i++;
	}
	if (check_opt(opt) == -1)
		usage(opt);
}
