/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:38:11 by pablalva          #+#    #+#             */
/*   Updated: 2025/10/06 15:38:08 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_move(int x, int y, t_cub *cub)
{
	int		center_x;
	int		center_y;
	int		delta_x;
	float	sens;

	(void)y;
	if (!cub->block_mouse)
		return (0);
	center_x = WIDTH / 2;
	center_y = HEIGHT / 2;
	delta_x = x - center_x;
	if (delta_x == 0)
		return (0);
	sens = 0.2f;
	rotate_player(&cub->player, delta_x * sens);
	mlx_mouse_move(cub->mlx->mlx, cub->mlx->mlx_win, center_x, center_y);
	return (0);
}

void	rotate_player(t_player *player, float angle)
{
	player->angle += angle;
	player->delta_x = cos(deg_to_rad(player->angle));
	player->delta_y = sin(deg_to_rad(player->angle));
}
