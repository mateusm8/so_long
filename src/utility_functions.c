/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateus <mateus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 22:19:43 by matmagal          #+#    #+#             */
/*   Updated: 2025/10/06 22:51:11 by mateus           ###   ########.fr       */
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
			return (free(line), close (fd), 0);
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

int	map_start(char *str)
{
	int	i;
	int	last_slash;

	if (!str)
		return (0);
	i = 0;
	last_slash = - 1;
	while (str[i])
	{
		if (str[i] == '/')
			last_slash = i;
		i++;
	}
	return (last_slash + 1);
}

int	check_file(char *map_name, char *extension)
{
	int	i;
	int	k;
	int	start;
	int	fd;

	k = 0;
	start = map_start(map_name);
	if (ft_strlen(map_name + start) <= ft_strlen(extension))
		return (0);
	i = start + ft_strlen(map_name + start) - ft_strlen(extension);
	fd = open(map_name, O_RDONLY);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	while (extension[k])
	{
		if (map_name[i + k] != extension[k])
			return (0);
		k++;
	}
	if (map_name[i + k] != '\0' || extension[k] != '\0')
		return (0);
	close (fd);
	return (1);
}
