/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:01:22 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/02 14:58:00 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_hooks(t_cub *cub)
{
	mlx_hook(cub->mlx->mlx_win, ON_DESTROY, NO_EVENT_MASK, safe_exit, cub);
	mlx_hook(cub->mlx->mlx_win, ON_KEYDOWN, KEY_PRESS_MASK, key_press_hook,
		cub);
	mlx_hook(cub->mlx->mlx_win, ON_KEYUP, KEY_RELEASE_MASK, key_release_hook,
		cub);
	mlx_hook(cub->mlx->mlx_win, 6, 1L << 6, mouse_move, cub);
	mlx_loop_hook(cub->mlx->mlx, main_loop, cub);
}

int	cub3d(t_cub *cub)
{
	cub->mlx->mlx = mlx_init();
	if (!cub->mlx->mlx)
		return (ft_error_mlx(1));
	cub->mlx->img = mlx_new_image(cub->mlx->mlx, WIDTH, HEIGHT);
	if (!cub->mlx->img)
		return (ft_error_mlx(1));
	cub->mlx->data = mlx_get_data_addr(cub->mlx->img, &cub->mlx->bpp,
			&cub->mlx->size_line, &cub->mlx->endian);
	if (!cub->mlx->data)
		return (ft_error_mlx(1));
	if (load_textures(cub) == 1)
		return (1);
	cub->mlx->mlx_win = mlx_new_window(cub->mlx->mlx, WIDTH, HEIGHT, "CUB3D");
	if (!cub->mlx->mlx_win)
		return (free(cub->mlx->mlx), ft_error_mlx(1));
	init_hooks(cub);
	return (0);
}
