/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:37:36 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/06 15:23:06 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	pixel = cub->mlx->data;
	pixel += y * cub->mlx->size_line;
	pixel += x * (cub->mlx->bpp / 8);
	*(unsigned int *)pixel = color;
}

t_image	set_texture(t_cub *cub, int direction)
{
	t_image	texture;

	if (direction == NORTH)
		texture = cub->image[NORTH];
	else if (direction == SOUTH)
		texture = cub->image[SOUTH];
	else if (direction == EAST)
	{
		texture = cub->image[EAST];
	}
	else if (direction == WEST)
		texture = cub->image[WEST];
	else if (direction == DOOR)
		texture = cub->image[DOOR];
	return (texture);
}

int	map_pixel_from_texture(t_image texture, t_collision col, float v_offset)
{
	int	x;
	int	y;
	int	color;

	x = texture.width * col.offset;
	y = texture.height * v_offset;
	if (x < 0)
		x = 0;
	if (x >= texture.width)
		x = texture.width - 1;
	if (y < 0)
		y = 0;
	if (y >= texture.height)
		y = texture.height - 1;
	color = *(unsigned int *)(texture.data + y * texture.size_line + x
			* (texture.bpp / 8));
	return (color);
}

void	render_frame(t_cub *cub)
{
	float		ray_angle;
	float		fov_step;
	t_collision	col;
	float		fov_rad;
	int			x;

	x = 0;
	fov_rad = deg_to_rad(FOV);
	fov_step = fov_rad / WIDTH;
	while (x < WIDTH)
	{
		ray_angle = deg_to_rad(cub->player.angle) - (fov_rad / 2.0) + (fov_step
				* x);
		col = cast_ray(cub, ray_angle);
		col.dist *= cos(ray_angle - deg_to_rad(cub->player.angle));
		draw_vertical_section(cub, x, col);
		x++;
	}
	draw_minimap(cub);
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->mlx_win, cub->mlx->img, 0,
		0);
}
