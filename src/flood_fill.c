/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:16:18 by matmagal          #+#    #+#             */
/*   Updated: 2025/10/07 22:06:46 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(char **map, int x, int y, t_allst *all)
{
	if (map[y][x] == '1' || map[y][x] == 'X')
		return ;
	if (map[y][x] == 'C')
		all->p_pos.c_count += 1;
	if (map[y][x] == 'E')
		all->p_pos.e_check = 1;
	map[y][x] = 'X';
	flood_fill(map, x, y + 1, all);
	flood_fill(map, x, y - 1, all);
	flood_fill(map, x + 1, y, all);
	flood_fill(map, x - 1, y, all);
}

void	flood_fill_exit_wall(char **map, int x, int y, t_allst *all)
{
	if (map[y][x] == '1' || map[y][x] == 'X' || map[y][x] == 'E')
		return ;
	if (map[y][x] == 'C')
		all->ffwe.ffwe += 1;
	map[y][x] = 'X';
	flood_fill_exit_wall(map, x, y + 1, all);
	flood_fill_exit_wall(map, x, y - 1, all);
	flood_fill_exit_wall(map, x + 1, y, all);
	flood_fill_exit_wall(map, x - 1, y, all);
}
