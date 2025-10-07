/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:48:58 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/06 15:38:39 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	player_on_door(t_cub *cub)
{
	int	px;
	int	py;

	px = (int)(cub->player.x / C_SIZE);
	py = (int)(cub->player.y / C_SIZE);
	return (cub->old_map[py][px] == 'D');
}

int	key_press_hook(int keycode, t_cub *cub)
{
	if (keycode == KEY_LEFT)
		cub->player.left_rotate = 1;
	else if (keycode == KEY_RIGHT)
		cub->player.right_rotate = 1;
	else if (keycode == KEY_W)
		cub->player.key_up = 1;
	else if (keycode == KEY_A)
		cub->player.key_left = 1;
	else if (keycode == KEY_S)
		cub->player.key_down = 1;
	else if (keycode == KEY_D)
		cub->player.key_right = 1;
	else if (keycode == XK_space && !player_on_door(cub))
		cub->door_open = !cub->door_open;
	else if (keycode == XK_t)
		cub->block_mouse = !cub->block_mouse;
	else if (keycode == KEY_ESC)
		safe_exit(cub);
	return (0);
}

int	key_release_hook(int keycode, t_cub *cub)
{
	if (keycode == KEY_LEFT)
		cub->player.left_rotate = 0;
	else if (keycode == KEY_RIGHT)
		cub->player.right_rotate = 0;
	else if (keycode == KEY_W)
		cub->player.key_up = 0;
	else if (keycode == KEY_A)
		cub->player.key_left = 0;
	else if (keycode == KEY_S)
		cub->player.key_down = 0;
	else if (keycode == KEY_D)
		cub->player.key_right = 0;
	return (0);
}

static void	aux_main_loop(t_cub *cub)
{
	if (cub->door_open)
	{
		if (cub->door_progress < 1.0f)
			cub->door_progress += 0.05f;
	}
	else
	{
		if (cub->door_progress > 0.0f)
		{
			if (!player_on_door(cub))
				cub->door_progress -= 0.05f;
		}
	}
}

int	main_loop(t_cub *cub)
{
	float	speed;
	float	rot_speed;

	speed = 2.0f;
	rot_speed = 2.0f;
	if (cub->player.left_rotate)
		rotate_player(&cub->player, -rot_speed);
	if (cub->player.right_rotate)
		rotate_player(&cub->player, rot_speed);
	if (cub->player.key_up)
		move_forward(cub, speed);
	if (cub->player.key_down)
		move_backward(cub, speed);
	if (cub->player.key_left)
		move_left(cub, speed);
	if (cub->player.key_right)
		move_right(cub, speed);
	aux_main_loop(cub);
	render_frame(cub);
	return (0);
}
