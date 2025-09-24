/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:46:21 by matmagal          #+#    #+#             */
/*   Updated: 2025/09/23 21:38:10 by matmagal         ###   ########.fr       */
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
	
	map = NULL;
	if (ac == 2)
	{
		if (check_file(av[1], ".ber") && map_lenght(av[1]))
			map = create_map(av[1]);
	}
	return (0);
}
