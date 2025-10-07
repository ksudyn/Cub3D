/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:20:13 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/02 16:42:46 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_texture_format(char **split)
{
	if (!split || !split[0] || !split[1] || split[2])
	{
		free_matrix(split);
		return (0);
	}
	return (1);
}

static int	assign_texture(char *id, int dir, char **split, t_cub *cub)
{
	if (!ft_strncmp(split[0], id, 3))
	{
		if (cub->textures_path[dir])
		{
			return (-1);
		}
		cub->textures_path[dir] = ft_strdup(split[1]);
		cub->textures_counter++;
		return (0);
	}
	return (1);
}

int	set_texture_path(char **split, t_cub *cub)
{
	if (!assign_texture("NO", NORTH, split, cub))
		return (0);
	if (!assign_texture("SO", SOUTH, split, cub))
		return (0);
	if (!assign_texture("WE", WEST, split, cub))
		return (0);
	if (!assign_texture("EA", EAST, split, cub))
	{
		return (0);
	}
	if (!assign_texture("DO", DOOR, split, cub))
		return (0);
	return (-1);
}

int	parse_texture_line(char *line, t_cub *cub)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!check_texture_format(split))
		return (-1);
	if (set_texture_path(split, cub))
	{
		free_matrix(split);
		return (-1);
	}
	free_matrix(split);
	return (0);
}
