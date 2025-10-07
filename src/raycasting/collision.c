/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:01:12 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/06 15:35:53 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	get_map_cell(t_cub *cub, int grid_x, int grid_y)
{
	if (grid_y < 0 || grid_y >= cub->height)
		return (' ');
	if (grid_x < 0 || grid_x >= cub->width)
		return (' ');
	return (cub->map[grid_y][grid_x]);
}

int	is_walkable_char(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 'D');
}

int	check_collision(t_cub *cub, float world_x, float world_y)
{
	int		grid_x;
	int		grid_y;
	char	tile;

	grid_x = (int)(world_x / (float)C_SIZE);
	grid_y = (int)(world_y / (float)C_SIZE);
	tile = get_map_cell(cub, grid_x, grid_y);
	if (tile == '1')
		return (1);
	if (tile == 'D')
	{
		if (cub->door_progress < 1.0f)
			return (1);
		else
			return (0);
	}
	if (is_walkable_char(tile))
		return (0);
	if (is_walkable_char(tile))
		return (0);
	return (1);
}

int	check_collision_radius(t_cub *cub, float x, float y, float r)
{
	if (check_collision(cub, x - r, y - r))
		return (1);
	if (check_collision(cub, x + r, y - r))
		return (1);
	if (check_collision(cub, x - r, y + r))
		return (1);
	if (check_collision(cub, x + r, y + r))
		return (1);
	return (0);
}
