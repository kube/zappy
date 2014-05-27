/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:01:10 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:01:10 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "type_libft.h"
# include <string.h>
# include <time.h>

# define FT_ERR_NO_ERROR 0
# define FT_ERR_MALLOC 1
# define FT_ERR_EXIST 2
# define FT_ERR_FORK 3
# define FT_ERR_PROCESS 4
# define FT_ERR_PIPE 5
# define FT_ERR_ACCESS 6
# define FT_ERR_OPEN 7
# define FT_ERR_CMD_NOT_FOUND 8

# define GNL_BUFFSIZE 1024

# define FT_JOIN_FREE1 1
# define FT_JOIN_FREE2 2
# define FT_JOIN_FREE_ALL 3
# define FT_JOIN_FREE_NO 0

void	load_tab_color1(int *tab);
void	load_tab_color2(int *tab);
void	load_tab_color3(int *tab);
void	load_tab_color4(int *tab);
void	load_tab_color5(int *tab);
void	load_tab_color6(int *tab);

int		*ft_loadcolor(void);

int		hash_color(char *str);
int		ft_strtocolor(char *str);

t_atom	*ft_atom_new(void *content);
t_list	*ft_lst_new(void *content);
void	ft_lst_push(t_list *lst, void *content);
void	ft_lst_pushend(t_list *lst, void *content);
t_atom	*ft_lst_pop(t_list *lst);
t_atom	*ft_lst_popend(t_list *lst);
int		ft_lst_atom_index(t_list *lst, t_atom *atom);
int		ft_lst_curr_index(t_list *lst);
t_list	*ft_lst_cpy(t_list *lst);
void	ft_lst_iter(t_list *lst, void (*f)(), void *param);
void	ft_lst_iter_atom(t_list *lst, void (*f)(), void *param);
void	ft_lst_del_atom(t_list *lst, t_atom *atom, void (*del)());
void	ft_lst_del(t_list *lst, void (*del)());
void	*ft_lst_prev_content(t_list *lst);
void	*ft_lst_next_content(t_list *lst);
void	*ft_lst_iter_next_content(t_list *lst, t_iterator *iterator);
void	ft_lst_reset_curr(t_list *lst);
void	ft_lst_iter_rev(t_list *lst, void (*f)(), void *param);
void	**ft_lst_to_tab(t_list *list);
void	ft_lst_push_after_atom(t_list *lst, void *content, t_atom *atom);
void	ft_lst_push_after_curr(t_list *lst, void *content);
void	ft_lst_push_before_atom(t_list *lst, void *content, t_atom *atom);
void	ft_lst_push_before_curr(t_list *lst, void *content);
void	ft_lst_qsort(t_list *l, int cmp());
t_atomp	ft_atomp_new(t_atom *atom, int pos);
void	ft_lst_swap_atom(t_atom *atom1, t_atom *atom2);

char	*ft_litoa_base(long int val, int base, int output_size);
char	*ft_litoa_base_fitted(long int val, int base);
double	ft_atod(char *str);
float	ft_atof(char *str);
int		ft_power(int nb, int power);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *s1, const void *s2, size_t n);
void	*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void	*ft_memmove(void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memjoin_free(const void *s1, size_t l1, const void *s2, size_t l2);

void	*ft_memalloc(size_t size);
void	ft_memdel(void **ap);
void	*ft_memdup(const void *s, size_t n);

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strdupchr(const char *s, char c);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strcpy(char *s1, const char *s2);
char	*ft_strncpy(char *s1, const char *s2, size_t n);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strncat(char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *s1, const char *s2);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strmjoin(int freeflag, ...);
char	*ft_strtabcat(char *dest, char **src, char *sep);
char	*ft_strtabjoin(char **src, char *sep);
char	*ft_strmcat(char *dest, ...);

char	*ft_strnew(size_t size);
void	ft_strdel(char **as);
void	ft_strclr(char *s);
void	ft_striter(char *s, void (*f)(char *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmap(char const *s, char (*f)(char));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strequ(char const *s1, char const *s2);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2, int free_mode);
char	*ft_strjoin_char(char *s1, char c, int mode_free);
char	*ft_strjoin_sep(char const *s1, char const *s2, char sep);
char	*ft_strtrim(char const *s);
char	**ft_strsplit(char const *s, char c);
char	**ft_strsplit_raw(char const *s, char c);
void	ft_free_strtab(char **tab);
char	*ft_chr_to_str(char c);

int		ft_isdigit(int c);
int		ft_isnumber(char *str);
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_iswhitespace(int c);

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_itoa_base(int val, int base, int output_size);

void	ft_putptr(void *ptr);
void	ft_putstr(char const *s);
void	ft_putendl(char const *s);
void	ft_putnbr(int n);
void	ft_putchar(char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnspace(size_t n);

void	ft_qsort(void *q, size_t s1, size_t s2, t_cmp f);
void	ft_tabrev(void *tab, size_t len, size_t width);
void	ft_swap(void **ptr1, void **ptr2);
int		ft_timespeccmp(struct timespec t1, struct timespec t2);

char	*ft_getfilename(char *path);
int		ft_get_next_line(int const fd, char **line);
char	*ft_strerror(int errcode);
void	ft_exit(char *errmsg, int errcode);
void	ft_warning(char *warnmsg, int warncode);

int		ft_secure_fork(char *prog_name);
int		ft_secure_pipe(int fd[2], char *prog_name);

#endif
