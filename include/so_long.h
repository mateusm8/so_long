/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:12:05 by matmagal          #+#    #+#             */
/*   Updated: 2025/09/30 21:58:20 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifdef __linux__
#  include "keys_linux.h"
# else
#  include "keys_macos.h"
# endif

# include "mlx.h"
# include "get_next_line.h"
# include "X11/X.h"
# include "X11/keysym.h"

typedef struct	s_map_info
{
	int		player;
	int		collect;
	int		escape;
	int		wall;
	int		floor;
	int		c_count;
	int		map_h;
	int		map_l;
	char	**map;
}	t_map_info;

typedef struct	s_pos
{
	int	x;
	int	y;
	int	c_count;
	int	e_check;
}				t_pos;

typedef	struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
}	t_mlx;

typedef struct s_allst
{
	t_map_info	map_info;
	t_pos		p_pos;
	t_mlx		mlx;
}	t_allst;

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
void	player_move_x(t_allst *all, int x, int y, int mv);
void	player_move_y(t_allst *all, int x, int y, int mv);
void	check_tile_x(t_allst *all, int x, int y, int mv);
void	check_tile_y(t_allst *all, int x, int y, int mv);
int		callback(int keycode, t_allst *all);

#endif
