/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:47:07 by yadereve          #+#    #+#             */
/*   Updated: 2024/03/26 19:52:37 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	initialization(t_map *map, t_mlx *date)
{
	date->map = map;
	date->img->x = 0;
	date->img->y = 0;
	date->img->next = 0;
	date->width = 32 * date->map->size.x;
	date->height = 32 * date->map->size.y;
	date->mlx = mlx_init();
	date->win = mlx_new_window(date->mlx, date->width, date->height, "so_long");
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	render_square(t_mlx *date)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	int box_x = date->height;
	int box_y = date->width;
	// printf("box_x = %d\t", x + date->img->width);
	// printf("box_y = %d\n", y + date->box_y);
	mlx_clear_window(date->mlx, date->win);
	while(x < box_x)
	{
		while (y < box_y)
		{
			mlx_pixel_put(date->mlx, date->win, x, y, 0xFF0000);
			y++;
		}
		y = 0;
		x++;
	}
	mlx_do_sync(date->mlx);
	return (1);
}

int	render_image(t_mlx *date)
{
	mlx_clear_window(date->mlx, date->win);
	mlx_put_image_to_window(date->mlx, date->win, date->img->img, date->img->x, date->img->y);
	// mlx_put_image_to_window(date->mlx, date->win, date->wall->img, date->wall->x, date->wall->y);

	mlx_do_sync(date->mlx);
	return (1);
}

int	keys(int keycode, t_mlx *date)
{
	// printf("key = %d\n", keycode);
	if (keycode == A_KEY || keycode == LEFT)
		date->img->x -= 32;
	if (keycode == D_KEY || keycode == RIGHT)
		date->img->x += 32;
	if (keycode == W_KEY || keycode == UP)
		date->img->y -= 32;
	if (keycode == S_KEY || keycode == DOWN)
		date->img->y += 32;

	if (keycode == ESC)
	{
		mlx_destroy_window(date->mlx, date->win);
		exit(0);
	}
	return (0);
}

void	mlx_start(t_map *map)
{
	t_mlx	date;
	int		w;
	int		h;

	initialization(map, &date);
	// date.wall->x = 0;
	// date.wall->y = 0;
	// date.img->cor = create_trgb(0, 255, 0, 0);

	date.img->img = mlx_xpm_file_to_image(date.mlx, "./sprites/player.xpm", &w, &h);
	// date.wall->img = mlx_xpm_file_to_image(date.mlx, "./sprites/wall.xpm", &w, &h);

	// * create_square * //
	// render_square(&date);
	// mlx_loop_hook(date.mlx, render_square, &date);

	// * image * //
	mlx_loop_hook(date.mlx, render_image, &date);

	// * keys * //
	mlx_hook(date.win, 2, 1L<<0, keys, &date);

	// * loop mlx, not closed win * //
	mlx_loop(date.mlx);

}
