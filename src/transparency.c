/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparency.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:54:02 by matmagal          #+#    #+#             */
/*   Updated: 2025/10/06 16:55:03 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill_strs(t_allst *all)
{
	int	bit;
	int	size;
	int	edian;
	int	i;

	bit = 0;
	size = 0;
	edian = 0;
	i = 0;
	all->strs.player = mlx_get_data_addr(all->imgs.player, &bit, &size, &edian);
	all->strs.item = mlx_get_data_addr(all->imgs.item, &bit, &size, &edian);
	all->strs.floor = mlx_get_data_addr(all->imgs.floor, &bit, &size, &edian);
	all->strs.exit = malloc(sizeof(int *) * 7);
	if (!all->strs.exit)
		return ;
	while (i <= 6)
	{
		all->strs.exit[i] = mlx_get_data_addr(all->imgs.exit[i], &bit, &size, &edian);
		i++;
	}
	player_sprite_check(all);
	item_sprite_check(all);
	exit_sprite_check(all);
}

void	player_sprite_check(t_allst *all)
{
	int	i;
	int	total_pixel;
	int	*p_data;
	int	*f_data;

	i = 0;
	total_pixel = TILE * TILE;
	p_data = (int *)all->strs.player;
	f_data = (int *)all->strs.floor;
	while (i < total_pixel)
	{
		if (p_data[i] == (int)0xff000000)
			p_data[i] = f_data[i];
		i++;
	}
}

void	item_sprite_check(t_allst *all)
{
	int	i;
	int	total_pixel;
	int	*i_data;
	int	*f_data;

	i = 0;
	total_pixel = TILE * TILE;
	i_data = (int *)all->strs.item;
	f_data = (int *)all->strs.floor;
	while (i < total_pixel)
	{
		if (i_data[i] == (int)0xff000000)
			i_data[i] = f_data[i];
		i++;
	}
}

void	exit_sprite_check(t_allst *all)
{
	int	i;
	int	j;
	int	total_pixel;
	int	*e_data;
	int	*f_data;

	total_pixel = TILE * TILE;
	i = 0;
	f_data = (int *)all->strs.floor;
	while (i < 7)
	{
		e_data = (int *)all->strs.exit[i];
		j = 0;
		while (j < total_pixel)
		{
			if (e_data[j] == (int)0xff000000)
				e_data[j] = f_data[j];
			j++;
		}
		i++;
	}
}
