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

	x = 350;
	y = 350;
	int box_x = date->img->height + x;
	int box_y = date->img->width + y;
	// printf("box_x = %d\t", x + date->box_x);
	// printf("box_y = %d\n", y + date->box_y);
	mlx_clear_window(date->mlx, date->win);
	while(x < box_x)
	{
		while (y < box_y)
		{
			mlx_pixel_put(date->mlx, date->win, x + date->img->x, y + date->img->y, 0xFF0000);
			y++;
		}
		y = 350;
		x++;
	}
	mlx_do_sync(date->mlx);
	return (1);
}

int	render_image(t_mlx *date)
{
	int	x;
	int	y;

	x = 350;
	y = 350;
	int obj_w = date->img->width + x;
	int obj_h = date->img->height + y;
	mlx_clear_window(date->mlx, date->win);
	while(x < obj_w)
	{
		while (y < obj_h)
		{
			mlx_put_image_to_window(date->mlx, date->win, date->img->img, date->img->x, date->img->y);
			y++;
		}
		y = 350;
		x++;
	}
	mlx_do_sync(date->mlx);
	return (1);
}

int	keys(int keycode, t_mlx *date)
{
	if (keycode == A_KEY || keycode == LEFT)
		date->img->x -= 50;
	if (keycode == D_KEY || keycode == RIGHT)
		date->img->x += 50;
	if (keycode == W_KEY || keycode == UP)
		date->img->y -= 50;
	if (keycode == S_KEY || keycode == DOWN)
		date->img->y += 50;

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

	date.height = 760;
	date.width = 1080;
	date.img->x = 0;
	date.img->y = 0;
	date.img->next = 0;
	date.img->img = mlx_xpm_file_to_image(date.mlx, "../textures/wall.xpm", &date.img->width, &date.img->height);
	// date.img->height = 50;
	// date.img->width = 50;
	date.img->cor = create_trgb(0, 255, 0, 0);

	initialization(map, &date);
	// * image * //
	mlx_loop_hook(date.mlx, render_image, &date);


	// * create_square * //
	// render_square(&date);
	// mlx_loop_hook(date.mlx, render_square, &date);

	// * keys * //
	mlx_hook(date.win, 2, 1L<<0, keys, &date);
	// printf("box_x = %d\t", date.img->box.x);
	// printf("box_y = %d\n", date.img->box.y);


	// var.mlx = mlx_init();
	// var.win = mlx_new_window(var.mlx, 1080, 760, "demo");
	// mlx_loop_hook(var.mlx, render_square, &var);
	// mlx_hook(var.win, 2, 1L<<0, keys, &var);
	// mlx_loop(var.mlx);



	// * loop mlx, not closed win * //
	mlx_loop(date.mlx);

}
