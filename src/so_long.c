/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateus <mateus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:46:21 by matmagal          #+#    #+#             */
/*   Updated: 2025/10/05 22:45:02 by mateus           ###   ########.fr       */
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
	if (all->map_info.map[all->p_pos.y][all->p_pos.x] == 'E')
		exit (0);
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
	if (all->map_info.map[all->p_pos.y][all->p_pos.x] == 'E')
		exit (0);
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
	char	next;

	next = all->map_info.map[y][x];
	if (next == 'C')
		all->map_info.c_count++;
	if (next != 'E')
		all->map_info.map[y + mv][x] = 'P';	
	all->map_info.map[y][x] = '0';
	all->p_pos.y = y + mv;
	draw_map(all);
	if (all->p_pos.x == all->p_pos.exit_x && all->p_pos.y == all->p_pos.exit_y)
		close_window(all);
}

void	player_move_x(t_allst *all, int x, int y, int mv)
{
	char	next;

	next = all->map_info.map[y][x];
	if (next == 'C')
		all->map_info.c_count++;
	if (next != 'E')
		all->map_info.map[y][x + mv] = 'P';
	all->map_info.map[y][x] = '0';
	all->p_pos.x = x + mv;
	draw_map(all);
	if (all->p_pos.x == all->p_pos.exit_x && all->p_pos.y == all->p_pos.exit_y)
		 close_window(all);
}

int	close_window(t_allst *all)
{
	mlx_free(all);
	exit (0);
}

void	init_screen(t_allst *all, int map_len, int	map_h)
{
	map_len *= TILE;
	map_h *= TILE;
	all->mlx.mlx_ptr = mlx_init();
	all->imgs.exit_frame = 0;
	all->mlx.win_ptr = mlx_new_window(all->mlx.mlx_ptr, map_len, map_h, all->p_pos.name);
	mlx_hook(all->mlx.win_ptr, 2, 1L<<0, callback, all);
	mlx_hook(all->mlx.win_ptr, 17, 0L, close_window, all);
	load_map(all);
	draw_map(all);
	mlx_loop_hook(all->mlx.mlx_ptr, animate_portal, all);
	mlx_loop(all->mlx.mlx_ptr);
}

void	load_portal(t_allst *all, int w, int h)
{
	all->imgs.exit[0] = mlx_xpm_file_to_image(all->mlx.mlx_ptr,
		"sprites/portal_frame1.xpm", &w, &h);
	all->imgs.exit[1] = mlx_xpm_file_to_image(all->mlx.mlx_ptr,
		"sprites/portal_frame2.xpm", &w, &h);
	all->imgs.exit[2] = mlx_xpm_file_to_image(all->mlx.mlx_ptr,
		"sprites/portal_frame3.xpm", &w, &h);
	all->imgs.exit[3] = mlx_xpm_file_to_image(all->mlx.mlx_ptr,
		"sprites/portal_frame4.xpm", &w, &h);
	all->imgs.exit[4] = mlx_xpm_file_to_image(all->mlx.mlx_ptr,
		"sprites/portal_frame5.xpm", &w, &h);
	all->imgs.exit[5] = mlx_xpm_file_to_image(all->mlx.mlx_ptr,
		"sprites/portal_frame6.xpm", &w, &h);
	all->imgs.exit[6] = mlx_xpm_file_to_image(all->mlx.mlx_ptr,
		"sprites/portal_frame7.xpm", &w, &h);
	
}

void	load_map(t_allst *all)
{
	int w;
	int h;

	w = TILE;
	h = TILE;
	all->imgs.floor = mlx_xpm_file_to_image(all->mlx.mlx_ptr, "sprites/planks.xpm", &w, &h);
	all->imgs.item = mlx_xpm_file_to_image(all->mlx.mlx_ptr, "sprites/potion.xpm", &w, &h);
	all->imgs.wall = mlx_xpm_file_to_image(all->mlx.mlx_ptr, "sprites/bluebricks.xpm", &w, &h);
	all->imgs.player = mlx_xpm_file_to_image(all->mlx.mlx_ptr, "sprites/whalkst.xpm", &w, &h);
	load_portal(all, w, h);
}
char	map_run(t_allst *all, int y, int x)
{
	return (all->map_info.map[y][x]);
}

void	draw_floor(t_allst *all, int x, int y)
{
	mlx_put_image_to_window(all->mlx.mlx_ptr,
		all->mlx.win_ptr, all->imgs.floor, x, y);
}

void	draw_wall(t_allst *all, int x, int y)
{
	mlx_put_image_to_window(all->mlx.mlx_ptr,
		all->mlx.win_ptr, all->imgs.wall, x, y);
}

void	draw_player(t_allst *all, int x, int y)
{
	draw_floor(all, x, y);
	mlx_put_image_to_window(all->mlx.mlx_ptr,
		all->mlx.win_ptr, all->imgs.player, x, y);
}

void	draw_collect(t_allst *all, int x, int y)
{
	draw_floor(all, x, y);
	mlx_put_image_to_window(all->mlx.mlx_ptr,
		all->mlx.win_ptr, all->imgs.item, x, y);
}

void	draw_map(t_allst *all)
{
	int	x;
	int	y;
	
	y = 0;
	while (y < all->map_info.map_h)
	{
		x = 0;
		while (x < all->map_info.map_l)
		{
			if (map_run(all, y, x) == '1')
				draw_wall(all, x * TILE, y * TILE);
			else if (map_run(all, y, x) == '0')
				draw_floor(all, x * TILE, y * TILE);
			else if (map_run(all, y, x) == 'P')
				draw_player(all, x * TILE, y * TILE);
			else if (map_run(all, y, x) == 'C')
				draw_collect(all, x * TILE, y * TILE);
			else if (map_run(all, y, x) == 'E')
			{
				all->p_pos.exit_x = x;
				all->p_pos.exit_y = y;
			}
			x++;
		}
		y++;
	}
}

int	animate_portal(t_allst *all)
{
	int					x;
	int					y;
	static long long	frame_counter;

	frame_counter++;
	if (frame_counter % 600 != 0)
		return (0);
	x = all->p_pos.exit_x * TILE;
	y = all->p_pos.exit_y * TILE;
	draw_floor(all, x, y);
	mlx_put_image_to_window(all->mlx.mlx_ptr, all->mlx.win_ptr,
		all->imgs.exit[all->imgs.exit_frame], x, y);
	all->imgs.exit_frame++;
	if (all->imgs.exit_frame > 6)
		all->imgs.exit_frame = 0;
	return (1);
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
		all->p_pos = (t_pos){0, 0, 0, 0, 0, 0, "so_long"};
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
		{
			printf("c_count = %d\nc_collect = %d\n e_check = %d\n", all->p_pos.c_count, all->map_info.c_collect, all->p_pos.e_check);
			return (free_all(all, all->map_info.map, copy_map), printf("Flood fill fail\n"), 0);
		}	
		else
		{
			printf("Flood fill ok\n");
			printf("l = %d\nh = %d\n", all->map_info.map_h, all->map_info.map_l);
			ft_free_str(copy_map);
			init_screen(all, all->map_info.map_l, all->map_info.map_h);
		}
	}
}
