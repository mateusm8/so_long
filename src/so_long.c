/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:46:21 by matmagal          #+#    #+#             */
/*   Updated: 2025/10/01 17:06:57 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**create_map(char *file)
{
	int		height;
	int		i;
	int		fd;
	char	**map;

	height = map_height(file);
	fd = open(file, O_RDONLY);
	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map[i] = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int	callback(int keycode, t_allst *all)
{
	if (keycode == KEY_ESC)
		close_window(all);
	if (keycode == KEY_W || keycode == KEY_UP)
		check_tile_y(all, all->p_pos.x, all->p_pos.y, -1);
	if (keycode == KEY_S || keycode == KEY_DOWN)
		check_tile_y(all, all->p_pos.x, all->p_pos.y, 1);
	if (keycode == KEY_A || keycode == KEY_LEFT)
		check_tile_x(all, all->p_pos.x, all->p_pos.y, -1);
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		check_tile_x(all, all->p_pos.x, all->p_pos.y, 1);
	return (1);
}

void	check_tile_y(t_allst *all, int x, int y, int mv)
{
	if (all->map_info.map[y + mv][x] == '0')
		player_move_y(all, all->p_pos.x, all->p_pos.y, mv);
	else if (all->map_info.map[y + mv][x] == 'C')
	{
		all->map_info.c_count += 1;
		player_move_y(all, all->p_pos.x, all->p_pos.y, mv);
	}
	else if (all->map_info.map[y + mv][x] == 'E'
			&& all->map_info.c_count == all->map_info.c_collect)
		player_move_y(all, all->p_pos.x, all->p_pos.y, mv);
}

void	check_tile_x(t_allst *all, int x, int y, int mv)
{
	if (all->map_info.map[y][x + mv] == '0')
		player_move_x(all, all->p_pos.x, all->p_pos.y, mv);
	else if (all->map_info.map[y][x + mv] == 'C')
	{
		all->map_info.c_count += 1;
		player_move_x(all, all->p_pos.x, all->p_pos.y, mv);
	}
	else if (all->map_info.map[y][x + mv] == 'E'
		&& all->map_info.c_count == all->map_info.c_collect)
		player_move_x(all, all->p_pos.x, all->p_pos.y, mv);
}

void	player_move_y(t_allst *all, int x, int y, int mv)
{

	all->map_info.map[y][x] = '0';
	all->map_info.map[y + mv][x] = 'P';
	all->p_pos.y = y + mv;
	// draw_map(all);
}

void	player_move_x(t_allst *all, int x, int y, int mv)
{
	all->map_info.map[y][x] = '0';
	all->map_info.map[y][x + mv] = 'P';
	all->p_pos.x = x + mv;
	// draw_map(all);
}

int	close_window(t_allst *all)
{
	mlx_free(all);
	exit (0);
}

void	init_screen(t_allst *all, int map_len, int	map_h)
{
	map_len *= 64;
	map_h *= 64;
	all->mlx.mlx_ptr = mlx_init();
	all->mlx.win_ptr = mlx_new_window(all->mlx.mlx_ptr, map_len, map_h, "so_long");
	mlx_hook(all->mlx.win_ptr, 2, 1L<<0, callback, all);
	mlx_hook(all->mlx.win_ptr, 17, 0L, close_window, all);
	mlx_loop(all->mlx.mlx_ptr);
}

int main(int ac, char **av)
{
	char	**copy_map;
	t_allst	*all;

	if (ac == 2)
	{
		if (!check_file(av[1], ".ber"))
			return (printf("Looks like something went wrong\n"), 0);
		if (!map_lenght(av[1]))
			return (printf("Wrong lenght\n"), 0);
		all = malloc(sizeof(t_allst));
		all->map_info = (t_map_info){0, 0, 0, 0, map_height(av[1]), map_lenght(av[1]), NULL};
		all->p_pos = (t_pos){0, 0, 0, 0};
		all->map_info.map = create_map(av[1]);
		if (!map_check(all->map_info.map, all))
			return (free_all(all, all->map_info.map, 0), printf("Invalid map\n"), 0);
		if (!check_border(all->map_info.map, av[1]))
			return (free_all(all, all->map_info.map, 0), printf("Border error\n"), 0);
		printf("Map created\n");
		copy_map = create_map(av[1]);
		find_player(all->map_info.map, all);
		flood_fill(copy_map, all->p_pos.x, all->p_pos.y, all);
		if (all->p_pos.c_count != all->map_info.c_collect
			|| all->p_pos.e_check != 1)
			return (free_all(all, all->map_info.map, copy_map), printf("Flood fill fail\n"), 0);
		else
		{
			printf("Flood fill ok\n");
			ft_free_str(copy_map);
			init_screen(all, all->map_info.map_l, all->map_info.map_h);
		}
	}
}
