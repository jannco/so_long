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

void	hero(t_mlx *date)
{
	int		w;
	int		h;

	date->hero->x = 32;
	date->hero->y = 32;
	date->hero->next = NULL;

	date->hero->img = mlx_xpm_file_to_image(date->mlx, "./sprites/player.xpm", &w, &h);
}

void	barrier(t_mlx *date)
{
	int	w;
	int	h;

	date->bar->x = 0;
	date->bar->y = 0;
	date->bar->next = NULL;

	date->bar->img = mlx_xpm_file_to_image(date->mlx, "./sprites/wall.xpm", &w, &h);
}
void	initialization(t_map *map, t_mlx *date)
{
	date->map = map;
	date->width = 32 * date->map->size.x;
	date->height = 32 * date->map->size.y;
	date->mlx = mlx_init();
	date->win = mlx_new_window(date->mlx, date->width, date->height, "so_long");
	hero(date);
	barrier(date);
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
	int box_x = date->width;
	int box_y = date->height;
	// printf("box_x = %d\t", x + date->img->width);
	// printf("box_y = %d\n", y + date->box_y);
	while(x < box_x)
	{
		while (y < box_y)
		{
			mlx_pixel_put(date->mlx, date->win, x, y, 0xCADC9F);
			y++;
		}
		y = 0;
		x++;
	}
	return (1);
}

int	render_image(t_mlx *date)
{
	mlx_clear_window(date->mlx, date->win);
	// render_square(date);
	mlx_put_image_to_window(date->mlx, date->win, date->bar->img, date->bar->x, date->bar->y);
	mlx_put_image_to_window(date->mlx, date->win, date->hero->img, date->hero->x, date->hero->y);
	mlx_do_sync(date->mlx);
	return (1);
}

int	keys(int keycode, t_mlx *date)
{

	// printf("key = %d\n", keycode);
	if (keycode == A_KEY || keycode == LEFT)
		date->hero->x -= 32;
	if (keycode == D_KEY || keycode == RIGHT)
		date->hero->x += 32;
	if (keycode == W_KEY || keycode == UP)
		date->hero->y -= 32;
	if (keycode == S_KEY || keycode == DOWN)
		date->hero->y += 32;

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

	initialization(map, &date);

	// * image * //
	mlx_loop_hook(date.mlx, render_image, &date);

	// * keys * //
	mlx_hook(date.win, 2, 1L<<0, keys, &date);

	// * loop mlx, not closed win * //
	mlx_loop(date.mlx);

}
