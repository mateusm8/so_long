/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:12:05 by matmagal          #+#    #+#             */
/*   Updated: 2025/09/24 22:19:33 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifdef __linux__
#  include "keys_linux.h"
# else
#  include "keys_macos.h"
# endif

# include "mlx.h"
# include "get_next_line.h"

typedef struct	s_map_info
{
	int	player;
	int	collect;
	int	escape;
	int	wall;
	int	floor;
}	t_map_info;

typedef struct s_allst
{
	t_map_info	map_info;
}	t_allst;

int	check_file(char *map_name, char *extension);
int	map_height(char	*file);
int	map_lenght(char *file);
char	**create_map(char *file);
int	map_check(char **map, t_allst *all);
int	line_check(char **map, char c);
int	check_border(char **map, char *map_name);

#endif
