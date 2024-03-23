/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:17:20 by yadereve          #+#    #+#             */
/*   Updated: 2024/03/23 11:51:05 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_copy_map(char **map, t_point size)
{
	for (int i = 0; i < size.y; i++)
		printf("%s\n", map[i]);
	printf("\n");
}

void	fill(char **validate, t_point size, t_point move, int *collect)
{
	// print_copy_map(validate, size);
	if (move.y < 0 || move.y > size.y || move.x < 0 || move.x > size.x
		|| !ft_strchr("0PEC", validate[move.y][move.x]))
		return ;
	if (validate[move.y][move.x] == 'C')
		(*collect)++;
	validate[move.y][move.x] = 'V';
	fill(validate, size, (t_point){move.x - 1, move.y}, collect);
	fill(validate, size, (t_point){move.x + 1, move.y}, collect);
	fill(validate, size, (t_point){move.x, move.y - 1}, collect);
	fill(validate, size, (t_point){move.x, move.y + 1}, collect);
}

void	flood_fill(char **validate, t_map *map, int *collect)
{
	fill(validate, map->size, map->start, collect);
}

bool	access_validate(char **valid, t_map *map)
{
	int	collect;

	collect = 0;
	flood_fill(valid, map, &collect);
	if (collect == map->collect && valid[map->finish.y][map->finish.x] == 'V')
		return (true);
	return (false);
}

char	**copy_map(t_map *map)
{
	char **copy;
	int	i;

	i = -1;
	copy = calloc(map->size.y + 1, sizeof(char *));
	if (copy == NULL)
		free_map(map);
	while (++i < map->size.y)
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

	validate = copy_map(map);
	if (access_validate(validate, map))
		free_copy_map(validate);
	else
	{
		free_copy_map(validate);
		free_map(map);
		error_message("Cannot reach exit or collectibles are unreachable.");
	}
}

void	check_arround_walls(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while(++i < map->size.y)
	{
		if (map->map[i][0] != '1' || map->map[i][map->size.x - 1] != '1')
		{
			free_map(map);
			error_message("Map must be surronded not by walls");
		}
		else
		{
			j = 0;
			if (i == 0 || i == map->size.y - 1)
			{
				while (j++ < map->size.x - 1)
					if (map->map[i][j] != '1')
					{
						free_map(map);
						error_message("Map must be surronded not by walls");
					}
			}
		}
	}
}

void	check_char(char *str, t_map *map)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 'P')
		{
			map->player++;
			map->start.x = i;
		}
		if (str[i] == '0')
			map->space++;
		if (str[i] == 'C')
			map->collect++;
		if (str[i] == 'E')
		{
			map->exit++;
			map->finish.x = i;
		}
		if (!ft_strchr("0CEP1", str[i]))
		{
			free_map(map);
			error_message("Invalid character in map");
		}
	}
}

void	print_map(t_map *map)
{
	int i;

	i = -1;
	while (map->map[++i])
		ft_putendl_fd(map->map[i], 1);
}

void	find_player_exit(t_map *map, int i)
{
	if (map->player == 1 && map->map[i][map->start.x] == 'P')
		map->start.y = i;
	if (map->exit == 1 && map->map[i][map->finish.x] == 'E')
		map->finish.y = i;
}

void	validate_map(t_map *map)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(map->map[0]);
	while (map->map[++i])
	{
		map->size.x = ft_strlen(map->map[i]);
		if (map->size.x != len)
		{
			free_map(map);
			error_message("Invalid map dimensions");
		}
		len = map->size.x;
		check_char(map->map[i], map);
		find_player_exit(map, i);
	}
	if (map->player != 1 || map->collect <= 0 || map->space <= 0
		|| map->exit != 1)
	{
		free_map(map);
		error_message("Player, Collectible, Exit or Space not found full");
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
		map->size.y = rows;
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
