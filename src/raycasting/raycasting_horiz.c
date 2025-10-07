/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_horiz.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:11:22 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/06 15:39:48 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_collision(t_collision *col, float dist, float offset, int dir)
{
	col->dist = dist;
	col->offset = offset;
	col->direction = dir;
}

void	cast_row_ray_down(t_cub *cub, float angle, t_collision *hit)
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;
	float	dist;

	y = floor(cub->player.y / C_SIZE) * C_SIZE + C_SIZE;
	x = cub->player.x + (y - cub->player.y) / tan(angle);
	y_step = C_SIZE;
	x_step = C_SIZE / tan(angle);
	while (1)
	{
		if ((int)y / C_SIZE < 0 || (int)y / C_SIZE >= cub->height || (int)x
			/ C_SIZE < 0 || (int)x / C_SIZE >= cub->width)
			return ;
		dist = sqrt(sqr(x - cub->player.x) + sqr(y - cub->player.y));
		if (cub->map[(int)(y / C_SIZE)][(int)(x / C_SIZE)] == 'D'
			&& cub->door_progress < 1.0f)
			return (set_collision(hit, dist, fmod(x, C_SIZE) / C_SIZE, DOOR));
		if (check_collision(cub, x, y))
			return (set_collision(hit, dist, fmod(x, C_SIZE) / C_SIZE, SOUTH));
		x += x_step;
		y += y_step;
	}
}

void	cast_row_ray_up(t_cub *cub, float angle, t_collision *hit)
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;
	float	dist;

	y = floor(cub->player.y / C_SIZE) * C_SIZE - 0.0001f;
	x = cub->player.x + (y - cub->player.y) / tan(angle);
	y_step = -C_SIZE;
	x_step = -C_SIZE / tan(angle);
	while (1)
	{
		if ((int)y / C_SIZE < 0 || (int)y / C_SIZE >= cub->height
			|| (int)x / C_SIZE < 0 || (int)x / C_SIZE >= cub->width)
			return ;
		dist = sqrt(sqr(x - cub->player.x) + sqr(y - cub->player.y));
		if (cub->map[(int)(y / C_SIZE)][(int)(x / C_SIZE)] == 'D'
			&& cub->door_progress < 1.0f)
			return (set_collision(hit, dist, fmod(x, C_SIZE) / C_SIZE, DOOR));
		if (check_collision(cub, x, y - 1))
			return (set_collision(hit, dist, fmod(x, C_SIZE) / C_SIZE, NORTH));
		x += x_step;
		y += y_step;
	}
}
