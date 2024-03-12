/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:25:03 by yadereve          #+#    #+#             */
/*   Updated: 2024/03/12 18:59:46 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_count_mapa(int fd, int tmp, int count_line, int *parameters)
{
	char	*line;
	int 	len;

	len = 0;
	line = get_next_line(fd);
	if (tmp == 0)
		tmp = ft_strlen(line);
	if (line)
	{
		len = ft_strlen(line);
		// ft_printf("len = %d\n", len);
		if (len != tmp)
		{
			ft_printf("The map is not fixed");
			return ;
		}
		tmp = len;
		count_line++;
		ft_count_mapa(fd, tmp, count_line, parameters);
	}
	if (!line)
		parameters[0] = count_line;
	parameters[1] = len;
}

int	ft_error_file_map(int fd, t_mapa **mapa)
{
	int	*parameters;
	int	len;
	int	line;
	int	i;

	i = 0;
	parameters = malloc(sizeof(int) * 2);
	ft_count_mapa(fd, 0, 0, parameters);
	line = parameters[0];
	len = parameters[1];
	mapa = ft_calloc(line + 1, sizeof(char *));
	if (mapa == NULL)
		return (0);
	while (i < len)
		mapa[i++] = ft_calloc(len + 1, sizeof(char));
	free(parameters);
	ft_printf("line = %d\nlen = %d\n", line, len);
	close(fd);
	return (0);
}

// array[7]; = char *
// a b x d g w i

// malloc(sizeof(char) * len + 1)
// \0

// array[][] = char **
// NULL

// malloc(sizeof(char *) * (len + 1))

int	ft_error_name_map(char *str)
{
	int i;

	i = 0;
	while (*str++)
	{
		char *ber = ".ber";

		while (*str == *ber)
		{
			str++;
			ber++;
			if (*ber == '\0' && *str == '\0')
				return (0);
		}
	}
	ft_printf("Error name mapa\n");
	exit(1);
}

void	ft_create_map(char *str, t_mapa *mapa)
{
	int		error_name_map;
	int		error_file_map;
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		perror("file opening filed");
	}
	error_name_map = ft_error_name_map(str);
	error_file_map = ft_error_file_map(fd, &mapa);
}
