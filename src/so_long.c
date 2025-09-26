/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:46:21 by matmagal          #+#    #+#             */
/*   Updated: 2025/09/26 22:18:35 by matmagal         ###   ########.fr       */
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

int main(int ac, char **av)
{
	char	**map;
	char	**copy_map;
	t_allst	*all;

	if (ac == 2)
	{
		all = malloc(sizeof(t_allst));
		all->map_info = (t_map_info){0, 0, 0, 1, 0};
		all->p_pos = (t_pos){0, 0, 0, 0};
		map = NULL;
		if (!check_file(av[1], ".ber") || !map_lenght(av[1]))
			return (printf("Looks like something went wrong"), 0);
		map = create_map(av[1]);
		if (!map_check(map, all))
			return (printf("Invalid map\n"), 0);
		if (!check_border(map, av[1]))
			return (printf("Border error\n"), 0);
		printf("Map created\n");
		copy_map = create_map(av[1]);
		find_player(copy_map, all);
		flood_fill(copy_map, all->p_pos.x, all->p_pos.y, all);
		if (all->p_pos.c_count != all->map_info.collect
			|| all->p_pos.e_check != 1)
			return (0);
		else
			printf("Flood fill ok\n");
		ft_free_str(copy_map);
		ft_free_str(map);
		free(all);
	}
}
