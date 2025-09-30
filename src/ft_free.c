/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:47:06 by matmagal          #+#    #+#             */
/*   Updated: 2025/09/30 22:18:21 by matmagal         ###   ########.fr       */
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

void	mlx_free(t_allst *all)
{
	if (all->mlx.win_ptr)
		mlx_destroy_window(all->mlx.mlx_ptr, all->mlx.win_ptr);
	free(all->mlx.mlx_ptr);
	if (all->mlx.mlx_ptr)
		mlx_destroy_display(all->mlx.mlx_ptr);
	if (all->mlx.img_ptr)
		mlx_destroy_image(all->mlx.mlx_ptr, all->mlx.img_ptr);
	if (all->map_info.map)
		ft_free_str(all->map_info.map);
	if (all)
		free(all);
}
