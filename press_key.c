/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:09:06 by yadereve          #+#    #+#             */
/*   Updated: 2024/02/22 14:53:21 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

void	*win;
void	*mlx;

int key_press(int keycode, void *param)
{
	printf("Key %d\n", keycode);
	if (keycode == ESC)
	{
		mlx_destroy_window(param, win);
		exit(0);
	}
	return 0;
}

int main(void)
{
	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "press_key");

	mlx_hook(win, 2, 1L << 0, key_press, mlx);

	mlx_loop(mlx);

	return 0;
}
