/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateus <mateus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:12:05 by matmagal          #+#    #+#             */
/*   Updated: 2025/10/06 23:02:20 by mateus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

# ifdef __linux__
#  include "keys_linux.h"
# else
#  include "keys_macos.h"
# endif

# include "mlx.h"
# include "get_next_line.h"
# include "ft_printf.h"

# ifndef TILE
#  define TILE 64
# endif

typedef struct	s_map_info
{
	int		c_player;
	int		c_collect;
	int		c_escape;
	int		c_count;
	int		map_h;
	int		map_l;
	char	**map;
}				t_map_info;

typedef struct	s_pos
{
	int	x;
	int	y;
	int	c_count;
	int	e_check;
	int	exit_x;
	int	exit_y;
	int	move_count;
	char	*name;
}				t_pos;

typedef	struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

typedef struct	s_imgs
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*item;
	void	*exit[7];
	int		exit_frame;
}				t_imgs;

typedef struct s_str
{
	char	*floor;
	char	*item;
	char	*player;
	char	**exit;
}				t_str;


typedef struct	s_allst
{
	t_map_info	map_info;
	t_pos		p_pos;
	t_mlx		mlx;
	t_imgs		imgs;
	t_str		strs;
}				t_allst;

int		check_file(char *map_name, char *extension);
int		map_height(char	*file);
int		map_lenght(char *file);
int		map_check(char **map, t_allst *all);
int		line_check(char **map, char c);
int		check_border(char **map, char *map_name);
int		ft_strlen(char *str);
int		check_border(char **map, char *map_name);
int		map_start(char *str);
char	**create_map(char *file);
void	flood_fill(char **map, int x, int y, t_allst *all);
void	find_player(char **map, t_allst *all);
void	ft_free_str(char **str);
void	free_all(t_allst *all, char **map, char **copy_map);
void	mlx_free(t_allst *all);
void	init_screen(t_allst *all, int map_len, int	map_h);
int		close_window(t_allst *all);
void	free_imgs(t_allst *all);
void	player_move_x(t_allst *all, int x, int y, int mv);
void	player_move_y(t_allst *all, int x, int y, int mv);
void	check_tile_x(t_allst *all, int x, int y, int mv);
void	check_tile_y(t_allst *all, int x, int y, int mv);
int		animate_portal(t_allst *all);
int		callback(int keycode, t_allst *all);
void	draw_map(t_allst *all, int x, int y);
void	draw_collect(t_allst *all, int x, int y);
void	draw_player(t_allst *all, int x, int y);
void	draw_wall(t_allst *all, int x, int y);
void	draw_floor(t_allst *all, int x, int y);
char	map_run(t_allst *all, int y, int x);
void	load_map(t_allst *all);
void	load_portal(t_allst *all, int w, int h);
void	fill_strs(t_allst *all);
void	player_sprite_check(t_allst *all);
void	item_sprite_check(t_allst *all);
void	exit_sprite_check(t_allst *all);
void	parse_three(t_allst *all, char **av);
void	parse_two(t_allst *all, char **av);
void	parse_one(char **av);

#endif
