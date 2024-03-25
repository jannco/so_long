/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:47:07 by yadereve          #+#    #+#             */
/*   Updated: 2024/03/25 21:48:53 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_lenght + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

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

int	render_square(t_mlx *date, int i, int j)
{
	int	x;
	int	y;

	x = 350;
	y = 350;
	printf("box_x = %d\t", x + date->img->box.x);
	printf("box_y = %d\n", y + date->img->box.y);
	while(x < 450)
	{
		while (y < 450)
		{
			my_mlx_pixel_put(date->img, x + i, y + j, date->img->cor);
			// my_mlx_pixel_put(date->img, x, y, date->img->cor);
			y++;
		}
		y = 350;
		x++;
	}
	return (1);
}

int	keys(int keycode, t_mlx *date)
{
	//printf("KEY = %d\n", keycode);
	if (keycode == A_KEY || keycode == LEFT)
	{
		date->img->box.x -= 10;
		render_square(date, date->img->box.x, date->img->box.y);
	}
	if (keycode == D_KEY || keycode == RIGHT)
	{
		date->img->box.x += 10;
		render_square(date, date->img->box.x, date->img->box.y);
	}
	if (keycode == W_KEY || keycode == UP)
	{
		date->img->box.y += 10;
		render_square(date, date->img->box.x, date->img->box.y);
	}
	if (keycode == S_KEY || keycode == DOWN)
	{
		date->img->box.y -= 10;
		render_square(date, date->img->box.x, date->img->box.y);
	}

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
	t_img	img;

	date.height = 760;
	date.width = 1080;
	date.map = map;
	img.cor = create_trgb(0, 255, 0, 0);
	img.box.x = 0;
	img.box.y = 0;
	date.img = &img;

	initialization(map, &date);
	// image
	img.img = mlx_new_image(date.mlx, date.width, date.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_lenght,
			&img.endian);

	for (int i = 0; i < 50; i++)
		my_mlx_pixel_put(&img, 50 + i, 50 + i, img.cor);
	for (int i = 0; i < 50; i++)
		my_mlx_pixel_put(&img, 100 - i, 100, 0x0000FF00);
	for (int i = 0; i < 50; i++)
		my_mlx_pixel_put(&img, 50, 100 - i, 0x000000FF);
	mlx_put_image_to_window(date.mlx, date.win, img.img, 0, 0);
	// * create_square * //

	// * keys * //
	mlx_hook(date.win, 2, 1L<<0, keys, &date);
	// printf("box_x = %d\t", date.img->box.x);
	render_square(&date, date.img->box.x, date.img->box.y);
	// printf("box_y = %d\n", date.img->box.y);
	//mlx_loop_hook(date.mlx, render_square, &date);

	// loop mlx, not closed win
	mlx_loop(date.mlx);

}
