/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:25:03 by yadereve          #+#    #+#             */
/*   Updated: 2024/03/11 20:43:05 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	ft_count_line(int fd, int tmp)
{
	char	*line;
	int 	len;
	int		count_line;

	count_line = 0;
	line = get_next_line(fd);
	if (tmp == 0)
		tmp = ft_strlen(line);
	if (line)
	{
		len = ft_strlen(line);
		// printf("len = %d\n", len);
		if (len != tmp)
			return (-1);
		tmp = len;
		return (ft_count_line(fd, tmp));
	}
	return (count_line + 1);
}

int	ft_error_file_map(int fd)
{
ft_printf("len = %d\n", ft_count_line(fd, 0));
close(fd);
return (0);
}

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
	ft_printf("Error name map\n");
	exit(1);
}

void	ft_error(char *str)
{
	int	error_name_map;
	int	error_file_map;
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		perror("file opening filed");
	}
	error_name_map = ft_error_name_map(str);
	error_file_map = ft_error_file_map(fd);


}
