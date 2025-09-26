/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:51:13 by matmagal          #+#    #+#             */
/*   Updated: 2025/09/26 22:21:28 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	line_check(char **map, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (map[i])
	{
		k = 0;
		while (map[i][k] && map[i][k] != '\n')
		{
			if (map[i][k] == c)
				j++;
			if (map[i][k] != '1' && map[i][k] != '0' && map[i][k] != 'P'
				&& map[i][k] != 'C' && map[i][k] != 'E')
				return (-1);
			k++;
		}
		i++;
	}
	return (j);
}

int	map_check(char **map, t_allst *all)
{
	all->map_info.player = line_check(map, 'P');
	all->map_info.collect += line_check(map, 'C');
	all->map_info.escape += line_check(map, 'E');
	if ((*all).map_info.player != 1 || (*all).map_info.collect < 1
		|| (*all).map_info.escape != 1)
		return (0);
	return (1);
}

int	check_border(char **map, char *map_name)
{
	int	i;
	int	j;
	int	last_line;
	int	map_len;

	i = 0;
	last_line = map_height(map_name) - 1;
	map_len = map_lenght(map_name) - 1;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && (map[0][j] != '\n' && map[0][j] != '\0'))
		{
			if ((map[0][j] != '1' || map[last_line][j] != '1'))
				return (0);
			if ((map[i][0] != '1' || map[i][map_len] != '1'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	find_player(char **map, t_allst *all)
{
	while (map[all->p_pos.y])
	{
		all->p_pos.x = 0;
		while (map[all->p_pos.y][all->p_pos.x])
		{
			if (map[all->p_pos.y][all->p_pos.x] == 'P')
				return ;
			all->p_pos.x++;
		}
		all->p_pos.y++;
	}
}

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
