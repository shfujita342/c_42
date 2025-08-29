/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:54:16 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/29 21:29:16 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define TILE 64
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

typedef struct s_img
{
	void	*ptr;
	int		w;
	int		h;
}			t_img;

typedef struct s_map
{
	char	**grid;
	int		w;
	int		h;
	int		c_cnt;
	int		e_cnt;
	int		p_cnt;
	int		p_x;
	int		p_y;
}			t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_img	tex_wall;
	t_img	tex_floor;
	t_img	tex_player;
	t_img	tex_exit;
	t_img	tex_collect;
	int		moves;
	int		collected;
	int		need;
}			t_game;

/* init.c */
int			init_game(t_game *g, const char *path);
void		load_textures(t_game *g);
void		free_images(t_game *g);

/* map_load.c */
int			load_map(const char *path, t_map *m);
void		free_map(t_map *m);

/* map_validate.c */
int			check_map_charset(t_map *m);
int			is_rect_map(t_map *m);
int			check_map_walls(t_map *m);
int			locate_player_collect(t_map *m);

/* path_check.c */
int			check_path(t_map *m);

/* render.c */
void		render(t_game *g);

/* hooks.c */
int			on_close(t_game *g);
int			on_key(int key, t_game *g);

/* utils.c */
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
char		**split_lines(char *buf);
char		*read_file(const char *path);
void		putstr_fd(const char *s, int fd);

/* utils2.c */
void		putnbr_fd(int n, int fd);
void		*safe_malloc(size_t size);
char		**dup_grid(char **grid, int h);
void		free_grid(char **grid, int h);

/* free.c */
void		print_error(const char *msg);

#endif
