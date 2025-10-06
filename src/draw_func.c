/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:58:59 by matmagal          #+#    #+#             */
/*   Updated: 2025/10/06 17:00:02 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	draw_map(t_allst *all, int x, int y)
{
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
