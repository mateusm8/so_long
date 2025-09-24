/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:51:13 by matmagal          #+#    #+#             */
/*   Updated: 2025/09/24 22:59:16 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

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
int	map_height(char	*file)
{
	int		height;
	int		fd;
	char	*line;

	height = 0;
	fd = open(file, O_RDONLY);
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

int	map_lenght(char *file)
{
	int		lenght;
	int		fd;
	char	*line;

	fd = open (file, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (close (fd), 0);
	lenght = ft_strlen(line);
	while (line)
	{
		if (lenght != ft_strlen(line))
			return (close (fd), 0);
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	return (lenght);
}

int	line_check(char **map, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (map[i])
	{
		k = 0;
		while (map[i][k])
		{
			if (map[i][k] == c)
				j++;
			k++;
		}	
		i++;
	}
	return (j);
}

int	map_check(char **map, t_allst *all)
{
	all->map_info.player = line_check(map, 'P');
	all->map_info.collect += line_check(map, 'C');
	all->map_info.escape += line_check(map, 'E');
	if ((*all).map_info.player != 1 || (*all).map_info.collect < 1
		|| (*all).map_info.escape != 1)
		return (0);
	return (1);
}

int	check_border(char **map, char *map_name)
{
	int	i;
	int	j;
	int	last_line;
	int	map_len;

	i = 0;
	last_line = map_height(map_name) - 1;
	map_len = map_lenght(map_name) - 1;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && (map[0][j] != '\n' && map[0][j] != '\0'))
		{
			if ((map[0][j] != '1' || map[last_line][j] != '1'))
				return (0);
			if ((map[i][0] != '1' || map[i][map_len] != '1'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
