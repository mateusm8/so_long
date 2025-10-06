/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:01:06 by matmagal          #+#    #+#             */
/*   Updated: 2025/10/06 17:01:47 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	fill_strs(all);
	draw_map(all, 0, 0);
	mlx_loop_hook(all->mlx.mlx_ptr, animate_portal, all);
	mlx_loop(all->mlx.mlx_ptr);
}

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
