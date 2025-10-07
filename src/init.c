/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:09:17 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/06 15:22:47 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_player(t_cub *cub)
{
	cub->player.x = cub->player_x * C_SIZE + C_SIZE / 2;
	cub->player.y = cub->player_y * C_SIZE + C_SIZE / 2;
	if (cub->player_dir == 'N')
		cub->player.angle = 270;
	else if (cub->player_dir == 'S')
		cub->player.angle = 90;
	else if (cub->player_dir == 'E')
		cub->player.angle = 0;
	else if (cub->player_dir == 'W')
		cub->player.angle = 180;
	cub->player.key_up = 0;
	cub->player.key_down = 0;
	cub->player.key_left = 0;
	cub->player.key_right = 0;
	cub->player.left_rotate = 0;
	cub->player.right_rotate = 0;
	cub->player.delta_x = cos(deg_to_rad(cub->player.angle));
	cub->player.delta_y = sin(deg_to_rad(cub->player.angle));
}

void	init_texture_paths(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		cub->textures_path[i] = NULL;
		i++;
	}
}

void	init_struct(t_cub *cub)
{
	ft_bzero(cub, sizeof(t_cub));
	cub->textures = ft_calloc(1, sizeof(t_textures));
	cub->mlx = ft_calloc(1, sizeof(t_mlx));
	cub->door_open = 0;
	if (!cub->textures || !cub->mlx)
		exit(ft_error(9));
}
