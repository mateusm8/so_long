/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:47:06 by matmagal          #+#    #+#             */
/*   Updated: 2025/10/08 22:12:08 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_str(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_all(t_allst *all, char **map, char **copy_map)
{
	if (map)
		ft_free_str(map);
	if (copy_map)
		ft_free_str(copy_map);
	if (all)
		free(all);
}

void	free_imgs(t_allst *all)
{
	int	i;

	i = 0;
	if (all->imgs.wall)
		mlx_destroy_image(all->mlx.mlx_ptr, all->imgs.wall);
	if (all->imgs.player)
		mlx_destroy_image(all->mlx.mlx_ptr, all->imgs.player);
	if (all->imgs.item)
		mlx_destroy_image(all->mlx.mlx_ptr, all->imgs.item);
	if (all->imgs.floor)
		mlx_destroy_image(all->mlx.mlx_ptr, all->imgs.floor);
	while (i <= 6)
	{
		if (all->imgs.exit[i])
			mlx_destroy_image(all->mlx.mlx_ptr, all->imgs.exit[i]);
		i++;
	}
}

void	mlx_free(t_allst *all)
{
	free_imgs(all);
	if (all->mlx.win_ptr)
		mlx_destroy_window(all->mlx.mlx_ptr, all->mlx.win_ptr);
	if (all->mlx.mlx_ptr)
	{
		mlx_destroy_display(all->mlx.mlx_ptr);
		free(all->mlx.mlx_ptr);
	}
	if (all->strs.exit)
		free(all->strs.exit);
	if (all->map_info.map)
		ft_free_str(all->map_info.map);
	free(all);
}

int	close_window(t_allst *all)
{
	mlx_free(all);
	exit (0);
}
