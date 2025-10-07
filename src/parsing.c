/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:51:13 by matmagal          #+#    #+#             */
/*   Updated: 2025/10/07 21:52:27 by matmagal         ###   ########.fr       */
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
	all->map_info.c_player = line_check(map, 'P');
	all->map_info.c_collect += line_check(map, 'C');
	all->map_info.c_escape += line_check(map, 'E');
	if ((*all).map_info.c_player != 1 || (*all).map_info.c_collect < 1
		|| (*all).map_info.c_escape != 1)
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
	int	x;
	int	y;

	y = 0;
	while (y < all->map_info.map_h)
	{
		x = 0;
		while (x < all->map_info.map_l)
		{
			if (map[y][x] == 'P')
			{
				all->p_pos.x = x;
				all->p_pos.y = y;
			}
			x++;
		}
		y++;
	}
}
