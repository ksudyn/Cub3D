/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_cast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:30:36 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/06 15:47:53 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_collision(t_collision *col)
{
	col->dist = 1e30;
	col->offset = 0;
	col->direction = -1;
}

t_collision	cast_ray(t_cub *cub, float ray_angle)
{
	t_collision	hit_h;
	t_collision	hit_v;
	t_collision	final;

	init_collision(&hit_h);
	init_collision(&hit_v);
	init_collision(&final);
	ray_angle = fmod(ray_angle, 2 * M_PI);
	if (ray_angle < 0)
		ray_angle += 2 * M_PI;
	if (ray_angle > 0 && ray_angle < M_PI)
		cast_row_ray_down(cub, ray_angle, &hit_h);
	else
		cast_row_ray_up(cub, ray_angle, &hit_h);
	if (ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2)
		cast_column_ray_right(cub, ray_angle, &hit_v);
	else
		cast_column_ray_left(cub, ray_angle, &hit_v);
	if (fabs(hit_h.dist * cos(ray_angle - cub->player.angle)) < fabs(hit_v.dist
			* cos(ray_angle - cub->player.angle)))
		final = hit_h;
	else
		final = hit_v;
	return (final);
}
