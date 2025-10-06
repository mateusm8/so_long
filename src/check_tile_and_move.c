/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tile_and_move.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateus <mateus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:56:20 by matmagal          #+#    #+#             */
/*   Updated: 2025/10/06 23:04:30 by mateus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

	all->p_pos.move_count++;
	ft_printf("Moves: %d\n", all->p_pos.move_count);
	next = all->map_info.map[y][x];
	if (next == 'C')
		all->map_info.c_count++;
	if (next != 'E')
		all->map_info.map[y + mv][x] = 'P';	
	all->map_info.map[y][x] = '0';
	all->p_pos.y = y + mv;
	draw_map(all, 0, 0);
	if (all->p_pos.x == all->p_pos.exit_x && all->p_pos.y == all->p_pos.exit_y)
		close_window(all);
}

void	player_move_x(t_allst *all, int x, int y, int mv)
{
	char	next;

	all->p_pos.move_count++;
	ft_printf("Moves: %d\n", all->p_pos.move_count);
	next = all->map_info.map[y][x];
	if (next == 'C')
		all->map_info.c_count++;
	if (next != 'E')
		all->map_info.map[y][x + mv] = 'P';
	all->map_info.map[y][x] = '0';
	all->p_pos.x = x + mv;
	draw_map(all, 0, 0);
	if (all->p_pos.x == all->p_pos.exit_x && all->p_pos.y == all->p_pos.exit_y)
		 close_window(all);
}
