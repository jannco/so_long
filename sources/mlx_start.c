/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:47:07 by yadereve          #+#    #+#             */
/*   Updated: 2024/03/23 16:36:10 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	my_mlx_pixel_put(t_img *date, int x, int y, int color)
{
	char	*dst;

	dst = date->addr + (y * date->line_lenght + x * (date->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	initialization(t_map *map, t_mlx *date)
{
	date->map = map;
	date->mlx = mlx_init();
	date->win = mlx_new_window(date->mlx, date->width, date->height, "so_long");
}

void	mlx_start(t_map *map)
{
	t_mlx	date;
	t_img	img;

	date.height = 760;
	date.width = 1080;
	date.map = map;
	// initialization(map, &date);
	date.mlx = mlx_init();
	date.win = mlx_new_window(date.mlx, date.width, date.height, "so_long");
	img.img = mlx_new_image(date.mlx, date.width, date.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_lenght,
			&img.endian);
	for (int i = 0; i < 50; i++)
		my_mlx_pixel_put(&img, 50 + i, 50 + i, 0x00FF0000);
	for (int i = 0; i < 50; i++)
		my_mlx_pixel_put(&img, 100 - i, 100, 0x0000FF00);
	for (int i = 0; i < 50; i++)
		my_mlx_pixel_put(&img, 50, 100 - i, 0x000000FF);
	mlx_put_image_to_window(date.mlx, date.win, img.img, 0, 0);
	mlx_loop(date.mlx);

}
