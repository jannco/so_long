/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:05:06 by yadereve          #+#    #+#             */
/*   Upmlxd: 2024/03/23 12:34:49 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx/minilibx_opengl_20191021/mlx.h"
# include "../minilibx/minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <errno.h>

typedef struct s_point
{
	int x;
	int y;

}	t_point;

typedef struct s_map
{
	char	**map;
	int		player;
	int		collect;
	int		space;
	int		exit;
	t_point	start;
	t_point	size;
	t_point	finish;

}	t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
	int		x;
	int		y;
	int		width;
	int		height;
	int		cor;
	struct s_img	*next;

}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	t_map	*map;
	t_img	*bar;
	t_img	*hero;

}	t_mlx;

#ifndef NULL
// MAC_OS
# define ESC 53
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
#else
// Linux
# define ESC 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
#endif

// void	ft_create_map(char *str, t_map *mapa);
// int		ft_error_name_map(char *str);
// int		ft_error_file_map(int fd, t_map **mapa);
// void	ft_count_mapa(int fd, int tmp, int count_line, int *parameters);

void	error_message(char *str);
void	free_map(t_map *map);
void	fill(char **valimlx, t_point size, t_point move, int *collect);
void	flood_fill(char **valimlx, t_map *map, int *collect);
bool	access_validate(char **valid, t_map *map);
char	**copy_map(t_map *map);
void	free_copy_map(char **copy);
void	check_access(t_map *map);
void	check_arround_walls(t_map *map);
void	check_char(char *str, t_map *map);
void	print_map(t_map *map);
void	find_player_exit(t_map *map, int i);
void	validate_map(t_map *map);
void	read_map(int fd, t_map *map, int rows);
void	read_input(int ac, char **av, t_map *map);
void	mlx_start(t_map *map);

#endif
