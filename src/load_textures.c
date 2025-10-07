/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:10:59 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/01 21:18:59 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_texture_line(char *line)
{
	return (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0
		|| ft_strncmp(line, "DO", 2) == 0);
}

static int	aux_load_textures(t_cub *cub)
{
	cub->textures->north = cub->image[0].img;
	cub->textures->south = cub->image[1].img;
	cub->textures->east = cub->image[2].img;
	cub->textures->west = cub->image[3].img;
	if (cub->textures_path[DOOR])
	{
		cub->textures->door = cub->image[DOOR].img;
	}
	else
	{
		cub->textures->door = NULL;
	}
	if (!cub->textures->north || !cub->textures->east || !cub->textures->south
		|| !cub->textures->west)
		return (1);
	if (cub->textures_path[DOOR] && !cub->textures->door)
		return (1);
	return (0);
}

int	load_textures(t_cub *cub)
{
	int	i;

	if (cub->textures == NULL)
		return (printf("Error: cub->textures no está inicializado.\n"), 1);
	i = -1;
	while (++i < NUM_TEXTURES)
	{
		if (i < 4 && !cub->textures_path[i])
			return (ft_error_mlx(2), 1);
		if (cub->textures_path[i])
		{
			cub->image[i].img = mlx_xpm_file_to_image(cub->mlx->mlx,
					cub->textures_path[i], &cub->image[i].width,
					&cub->image[i].height);
		}
		if (cub->image[i].img)
		{
			cub->image[i].data = mlx_get_data_addr(cub->image[i].img,
					&cub->image[i].bpp, &cub->image[i].size_line,
					&cub->image[i].endian);
		}
	}
	if (aux_load_textures(cub) != 0)
		return (ft_error_mlx(2), 1);
	return (0);
}
