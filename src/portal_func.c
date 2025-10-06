/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:58:03 by matmagal          #+#    #+#             */
/*   Updated: 2025/10/06 16:58:36 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_portal(t_allst *all, int w, int h)
{
	all->imgs.exit[0] = mlx_xpm_file_to_image(all->mlx.mlx_ptr,
		"sprites/portal_frame1.xpm", &w, &h);
	all->imgs.exit[1] = mlx_xpm_file_to_image(all->mlx.mlx_ptr,
		"sprites/portal_frame2.xpm", &w, &h);
	all->imgs.exit[2] = mlx_xpm_file_to_image(all->mlx.mlx_ptr,
		"sprites/portal_frame3.xpm", &w, &h);
	all->imgs.exit[3] = mlx_xpm_file_to_image(all->mlx.mlx_ptr,
		"sprites/portal_frame4.xpm", &w, &h);
	all->imgs.exit[4] = mlx_xpm_file_to_image(all->mlx.mlx_ptr,
		"sprites/portal_frame5.xpm", &w, &h);
	all->imgs.exit[5] = mlx_xpm_file_to_image(all->mlx.mlx_ptr,
		"sprites/portal_frame6.xpm", &w, &h);
	all->imgs.exit[6] = mlx_xpm_file_to_image(all->mlx.mlx_ptr,
		"sprites/portal_frame7.xpm", &w, &h);
	
}

int	animate_portal(t_allst *all)
{
	int					x;
	int					y;
	static long long	frame_counter;

	frame_counter++;
	if (frame_counter % 600 != 0)
		return (0);
	x = all->p_pos.exit_x * TILE;
	y = all->p_pos.exit_y * TILE;
	draw_floor(all, x, y);
	mlx_put_image_to_window(all->mlx.mlx_ptr,
		all->mlx.win_ptr, all->imgs.exit[all->imgs.exit_frame], x, y);
	all->imgs.exit_frame++;
	if (all->imgs.exit_frame > 6)
		all->imgs.exit_frame = 0;
	return (1);
}
