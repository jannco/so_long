/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:41:49 by yadereve          #+#    #+#             */
/*   Updated: 2024/03/14 18:28:34 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	error_message(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void	free_map(t_map *map)
{
	int i;

	i = -1;
	while (map->map[++i])
		free(map->map[i]);
	free(map->map);
}
