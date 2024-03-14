/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:17:20 by yadereve          #+#    #+#             */
/*   Updated: 2024/03/14 18:40:32 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	access_validate(char **validate)
{
	int	player;
	int	collect;
	int	space;
	int	exit;

	player = 0;
	collect = 0;
	space = 0;
	exit = 0;
	if ()
}

char	**copy_map(t_map *map)
{
	char **copy;
	int	i;

	i = -1;
	copy = calloc(map->line + 1, sizeof(char *));
	if (copy == NULL)
		free_map(map);
	while (++i < map->line)
		copy[i] = ft_strdup(map->map[i]);
	copy[i] = NULL;
	return (copy);
}

void	free_copy_map(char **copy)
{
	int i;

	i = -1;
	while (copy[++i])
		free(copy[i]);
	free(copy);
}

void	check_access(t_map *map)
{
	char	**validate;
	int		i;

	i = 0;
	validate = copy_map(map);
	if (access_validate(validate))
		free_copy_map(validate);
	else
	{
		error_message("not map val");
		free_copy_map(validate);
		free_map(map);
	}
}

void	check_arround_walls(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while(++i < map->line)
	{
		if (map->map[i][0] != '1' || map->map[i][map->lenght - 1] != '1')
		{
			error_message("Map must be surronded not by walls");
			free_map(map);
		}
		else
		{
			j = 0;
			if (i == 0 || i == map->line - 1)
			{
				while (j++ < map->lenght - 1)
					if (map->map[i][j] != '1')
						{
							error_message("Map must be surronded not by walls");
							free_map(map);
						}
			}
		}
	}
}

void	check_char(char *str, t_map *map)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'P')
			{
			map->player++;
			map->x = i;
			}
		if (str[i] == '0')
			map->space++;
		if (str[i] == 'C')
			map->collect++;
		if (str[i] == 'E')
			map->exit++;
		if (!ft_strchr("0CEP1", str[i]))
		{
			error_message("Invalid character in map");
			free_map(map);
		}
		i++;
	}
}

void	print_map(t_map *map)
{
	int i;

	i = -1;
	while (map->map[++i])
		ft_putendl_fd(map->map[i], 1);
}

void	validate_map(t_map *map)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(map->map[0]);
	while (map->map[++i])
	{
		map->lenght = ft_strlen(map->map[i]);
		if (map->lenght != len)
		{
			error_message("Invalid map dimensions");
			free_map(map);
		}
		len = map->lenght;
		check_char(map->map[i], map);
		if (map->player == 1)
			map->y = i;
	}
	if (map->player != 1 || map->collect <= 0 || map->space <= 0
		|| map->exit != 1)
	{
		error_message("Player, Collectible, Exit or Space not found");
		free_map(map);
	}
	check_arround_walls(map);
}

void	read_map(int fd, t_map *map, int rows)
{
	char	*line;

	line = get_next_line(fd);
	if (line)
		read_map(fd, map, rows + 1);
	else
	{
		map->map = ft_calloc(rows + 1, sizeof(char *));
		if (map->map == NULL)
			error_message("Invalid memory allocatin.");
		map->line = rows;
	}
	if (line)
	{
		map->map[rows] = ft_strtrim(line, "\n");
		if (map->map[rows] == NULL)
			error_message("Invalid memory allocatin.");
		free(line);
	}
}

void	read_input(int ac, char **av, t_map *map)
{
	int	fd;

	map->player = 0;
	map->collect = 0;
	map->space = 0;
	map->exit = 0;
	if (ac != 2)
		error_message("Too many arguments.");
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".ber", 4))
		error_message("The map file must have a .ber extension.");
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error_message("Invalid file");
	read_map(fd, map, 0);
	// print_map(map);
	close(fd);
	validate_map(map);
	check_access(map);
}
