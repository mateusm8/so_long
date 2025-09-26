/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 22:19:43 by matmagal          #+#    #+#             */
/*   Updated: 2025/09/26 22:21:33 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	map_len(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '/')
			j = i;
		i++;
	}
	return (i - j - 1);
}

int	check_file(char *map_name, char *extension)
{
	int	i;
	int	j;
	int	fd;

	j = 0;
	if (map_len(map_name) <= ft_strlen(extension))
		return (0);
	i = map_len(map_name) - ft_strlen(extension);
	fd = open(map_name, O_RDONLY);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	while (extension[j])
	{
		if (map_name[i + j] != extension[j])
			return (0);
		j++;
	}
	if (map_name[i + j] != '\0')
		return (0);
	close (fd);
	return (1);
}
