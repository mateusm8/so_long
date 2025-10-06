/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:46:21 by matmagal          #+#    #+#             */
/*   Updated: 2025/10/06 17:01:53 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
