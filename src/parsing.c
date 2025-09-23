/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:51:13 by matmagal          #+#    #+#             */
/*   Updated: 2025/09/23 13:33:25 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_file(char *map_name, char *extension)
{
	int	i;
	int	j;
	int	fd;

	j = 0;
	if (ft_strlen(map_name) < ft_strlen(extension))
		return (0);
	i = ft_strlen(map_name) - ft_strlen(extension);
	fd = open(map_name, O_RDONLY);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	while(extension[j])
	{
		if (map_name[i + j] != extension[j])
			return (0);
		j++;
	}
	close (fd);
	return (1);
}
int	map_height(char	*map)
{
	int		height;
	int		fd;
	char	*line;

	height = 0;
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		height++;
	}
	close (fd);
	return (height);
}
