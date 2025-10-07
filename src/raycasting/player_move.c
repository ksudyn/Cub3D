/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:08:16 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/06 15:37:45 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_cub *cub, float speed)
{
	float	new_x;
	float	new_y;
	float	r;

	r = 6.0f;
	new_x = cub->player.x + cub->player.delta_x * speed;
	new_y = cub->player.y + cub->player.delta_y * speed;
	if (!check_collision_radius(cub, new_x, new_y, r))
	{
		cub->player.x = new_x;
		cub->player.y = new_y;
	}
}

void	move_backward(t_cub *cub, float speed)
{
	float	new_x;
	float	new_y;
	float	r;

	r = 6.0f;
	new_x = cub->player.x - cub->player.delta_x * speed;
	new_y = cub->player.y - cub->player.delta_y * speed;
	if (!check_collision_radius(cub, new_x, new_y, r))
	{
		cub->player.x = new_x;
		cub->player.y = new_y;
	}
}

void	move_left(t_cub *cub, float speed)
{
	float	new_x;
	float	new_y;
	float	r;

	r = 6.0f;
	new_x = cub->player.x + cub->player.delta_y * speed;
	new_y = cub->player.y - cub->player.delta_x * speed;
	if (!check_collision_radius(cub, new_x, new_y, r))
	{
		cub->player.x = new_x;
		cub->player.y = new_y;
	}
}

void	move_right(t_cub *cub, float speed)
{
	float	new_x;
	float	new_y;
	float	r;

	r = 6.0f;
	new_x = cub->player.x - cub->player.delta_y * speed;
	new_y = cub->player.y + cub->player.delta_x * speed;
	if (!check_collision_radius(cub, new_x, new_y, r))
	{
		cub->player.x = new_x;
		cub->player.y = new_y;
	}
}
