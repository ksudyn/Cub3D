/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_vert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:15:01 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/06 15:25:37 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cast_column_ray_right(t_cub *cub, float angle, t_collision *hit)
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;
	float	dist;

	x = floor(cub->player.x / C_SIZE) * C_SIZE + C_SIZE;
	y = cub->player.y + (x - cub->player.x) * tan(angle);
	x_step = C_SIZE;
	y_step = C_SIZE * tan(angle);
	while (1)
	{
		if ((int)y / C_SIZE < 0 || (int)y / C_SIZE >= cub->height
			|| (int)x / C_SIZE < 0 || (int)x / C_SIZE >= cub->width)
			return ;
		dist = sqrt(sqr(x - cub->player.x) + sqr(y - cub->player.y));
		if (cub->map[(int)(y / C_SIZE)][(int)(x / C_SIZE)] == 'D'
			&& cub->door_progress < 1.0f)
			return (set_collision(hit, dist, fmod(y, C_SIZE) / C_SIZE, DOOR));
		if (check_collision(cub, x, y))
			return (set_collision(hit, dist, fmod(y, C_SIZE) / C_SIZE, EAST));
		x += x_step;
		y += y_step;
	}
}

void	cast_column_ray_left(t_cub *cub, float angle, t_collision *hit)
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;
	float	dist;

	x = floor(cub->player.x / C_SIZE) * C_SIZE - 0.0001f;
	y = cub->player.y + (x - cub->player.x) * tan(angle);
	x_step = -C_SIZE;
	y_step = -C_SIZE * tan(angle);
	while (1)
	{
		if ((int)y / C_SIZE < 0 || (int)y / C_SIZE >= cub->height
			|| (int)x / C_SIZE < 0 || (int)x / C_SIZE >= cub->width)
			return ;
		dist = sqrt(sqr(x - cub->player.x) + sqr(y - cub->player.y));
		if (cub->map[(int)(y / C_SIZE)][(int)(x / C_SIZE)] == 'D'
			&& cub->door_progress < 1.0f)
			return (set_collision(hit, dist, fmod(y, C_SIZE) / C_SIZE, DOOR));
		if (check_collision(cub, x - 1, y))
			return (set_collision(hit, dist, fmod(y, C_SIZE) / C_SIZE, WEST));
		x += x_step;
		y += y_step;
	}
}
