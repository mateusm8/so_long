/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateus <mateus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:46:21 by matmagal          #+#    #+#             */
/*   Updated: 2025/10/06 23:02:29 by mateus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	parse_one(char **av)
{
	if (!check_file(av[1], ".ber"))
	{
		ft_printf("Looks like something went wrong\n");
		exit (0);
	}
	if (!map_lenght(av[1]))
	{
		ft_printf("Wrong lenght\n");
		exit (0);
	}
}

void	parse_two(t_allst *all, char **av)
{
	if (!map_check(all->map_info.map, all))
	{
		free_all(all, all->map_info.map, 0);
		ft_printf("Invalid map\n");
		exit (0);
	}
	if (!check_border(all->map_info.map, av[1]))
	{
		free_all(all, all->map_info.map, 0);
		ft_printf("Border error\n");
		exit (0);
	}
}

void	parse_three(t_allst *all, char **av)
{
	char	**copy_map;

	copy_map = create_map(av[1]);
	flood_fill(copy_map, all->p_pos.x, all->p_pos.y, all);
	if (all->p_pos.c_count != all->map_info.c_collect
	|| all->p_pos.e_check != 1)
	{
		free_all(all, all->map_info.map, copy_map);
		ft_printf("Flood fill fail\n");
		exit (0);
	}
	ft_free_str(copy_map);
}

int main(int ac, char **av)
{
	t_allst	*all;

	if (ac == 2)
	{
		parse_one(av);
		all = malloc(sizeof(t_allst));
		all->map_info = (t_map_info){0, 0, 0, 0,
			map_height(av[1]), map_lenght(av[1]), NULL};
		all->p_pos = (t_pos){0, 0, 0, 0, 0, 0, 0, "so_long"};
		all->map_info.map = create_map(av[1]);
		parse_two(all, av);
		ft_printf("Map created\n");
		find_player(all->map_info.map, all);
		parse_three(all, av);
		ft_printf("Flood fill ok\n");
		init_screen(all, all->map_info.map_l, all->map_info.map_h);
	}
}
