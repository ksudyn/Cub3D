/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:28:11 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/06 15:22:55 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define MAX_MINIMAP_SIZE 200
#define PLAYER_COLOR 0xFF0000
#define WALL_COLOR 0x444444
#define FLOOR_COLOR 0xFFFFFF
#define DOOR_COLOR 0xFF0000

void	calculate_minimap_scale(t_cub *cub)
{
	int	scale_x;
	int	scale_y;

	if (cub->width <= 0 || cub->height <= 0)
	{
		cub->minimap_scale = 1;
		cub->minimap_offset_x = 0;
		cub->minimap_offset_y = 0;
		return ;
	}
	scale_x = MAX_MINIMAP_SIZE / cub->width;
	scale_y = MAX_MINIMAP_SIZE / cub->height;
	cub->minimap_scale = scale_x;
	if (scale_y < scale_x)
		cub->minimap_scale = scale_y;
	if (cub->minimap_scale < 1)
		cub->minimap_scale = 1;
	cub->minimap_offset_x = 10;
	cub->minimap_offset_y = 10;
}

void	draw_square(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;
	int	scale;
	int	offset_x;
	int	offset_y;

	i = 0;
	scale = cub->minimap_scale;
	offset_x = cub->minimap_offset_x;
	offset_y = cub->minimap_offset_y;
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			put_pixel(cub, offset_x + x * scale + j, offset_y + y * scale + i,
				color);
			j++;
		}
		i++;
	}
}

void	draw_player_minimap(t_cub *cub)
{
	int	px;
	int	py;
	int	radius;
	int	dx;
	int	dy;

	px = cub->minimap_offset_x + (cub->player.x / C_SIZE)
		* cub->minimap_scale;
	py = cub->minimap_offset_y + (cub->player.y / C_SIZE)
		* cub->minimap_scale;
	radius = 3;
	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			if (dx * dx + dy * dy <= radius * radius)
				put_pixel(cub, px + dx, py + dy, PLAYER_COLOR);
			dx++;
		}
		dy++;
	}
}

void	draw_player_direction(t_cub *cub)
{
	int	px;
	int	py;
	int	i;
	int	dx;
	int	dy;

	px = cub->minimap_offset_x + (cub->player.x / C_SIZE)
		* cub->minimap_scale;
	py = cub->minimap_offset_y + (cub->player.y / C_SIZE)
		* cub->minimap_scale;
	i = 0;
	while (i < 7)
	{
		dx = (int)(cub->player.delta_x * i);
		dy = (int)(cub->player.delta_y * i);
		put_pixel(cub, px + dx, py + dy, 0x00FF00);
		i++;
	}
}

void	draw_minimap(t_cub *cub)
{
	int		y;
	int		x;
	char	cell;

	y = 0;
	calculate_minimap_scale(cub);
	while (y < cub->height)
	{
		x = 0;
		while (x < cub->width)
		{
			cell = cub->map[y][x];
			if (cell == '1')
				draw_square(cub, x, y, WALL_COLOR);
			else if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E'
				|| cell == 'W')
				draw_square(cub, x, y, FLOOR_COLOR);
			else if (cell == 'D')
				draw_square(cub, x, y, DOOR_COLOR);
			x++;
		}
		y++;
	}
	draw_player_minimap(cub);
	draw_player_direction(cub);
}
