/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:05:06 by yadereve          #+#    #+#             */
/*   Updated: 2024/03/13 20:04:35 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx/minilibx_opengl_20191021/mlx.h"
# include "../minilibx/minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <errno.h>

typedef struct s_data
{
	void	*mlx;
	void	*win;

}	t_data;

typedef struct s_map
{
	char	**map;
	int		line;
	int		lenght;
	int		player;
	int		collect;
	int		space;
	int		exit;

}	t_map;

// MAC_OS
// # define ESC 53
// # define W_KEY 13
// # define A_KEY 0
// # define S_KEY 1
// # define D_KEY 2

// Linux
# define ESC 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100

// void	ft_create_map(char *str, t_map *mapa);
// int		ft_error_name_map(char *str);
// int		ft_error_file_map(int fd, t_map **mapa);
// void	ft_count_mapa(int fd, int tmp, int count_line, int *parameters);

void	read_input(int ac, char **av, t_map *map);
void	message_error(char *str);
void	read_map(int fd, t_map *map, int rows);
void	validate_map(t_map *map);
void	free_map(t_map *map);

#endif
