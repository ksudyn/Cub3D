/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:00:06 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/06 15:37:12 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_cub(t_cub *cub)
{
	int	i;

	i = 0;
	if (cub->map)
	{
		while (cub->map[i])
		{
			free(cub->map[i]);
			i++;
		}
		free(cub->map);
		i = 0;
	}
	while (i < NUM_TEXTURES)
	{
		if (cub->textures_path[i])
			free(cub->textures_path[i]);
		i++;
	}
	if (cub->textures)
		free(cub->textures);
	if (cub->mlx)
		free(cub->mlx);
}

float	deg_to_rad(float deg)
{
	return (deg * M_PI / 180);
}

float	sqr(float n)
{
	return (n * n);
}

int	safe_exit(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		if (cub->image[i].img)
			mlx_destroy_image(cub->mlx->mlx, cub->image[i].img);
		i++;
	}
	if (cub->mlx->mlx_win)
		mlx_destroy_window(cub->mlx->mlx, cub->mlx->mlx_win);
	if (cub->mlx->img)
		mlx_destroy_image(cub->mlx->mlx, cub->mlx->img);
	if (cub->mlx->mlx)
	{
		mlx_destroy_display(cub->mlx->mlx);
		free(cub->mlx->mlx);
	}
	if (cub->old_map)
		free_matrix(cub->old_map);
	free_cub(cub);
	exit(0);
}

int	rgb_to_int(int rgb[3])
{
	int	color;

	color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (color);
}
