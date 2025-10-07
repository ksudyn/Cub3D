/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:33:05 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/07 16:21:30 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	remove_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static int	handle_color_line(char **line, t_cub *cub)
{
	if ((*line)[0] == 'F' || (*line)[0] == 'C')
	{
		if (parse_color_line(*line, cub) == 0)
			return (-1);
	}
	else
		return (1);
	return (0);
}

int	process_line(char **line, char ***map, int *height, t_cub *cub)
{
	remove_newline(*line);
	if ((*line)[0] == '\0')
	{
		if (cub->map_started)
			cub->map_finished = 1;
		return (1);
	}
	if (cub->map_finished)
		return (-1);
	if (is_texture_line(*line))
	{
		if (parse_texture_line(*line, cub) == -1)
			return (-1);
	}
	else if (handle_color_line(line, cub) == -1)
		return (-1);
	else if (!((*line)[0] == 'F' || (*line)[0] == 'C')
		&& cub->textures->ceiling_set == 1 && cub->textures->floor_set == 1)
	{
		cub->map_started = 1;
		if (!dimensions(*line, map, height, cub))
			return (free(*line), free_matrix(*map), 0);
	}
	return (1);
}

char	**read_map_lines(int fd, t_cub *cub)
{
	char	*line;
	char	**map;
	int		height;

	map = NULL;
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (process_line(&line, &map, &height, cub) == -1)
		{
			free(line);
			free_matrix(map);
			get_next_line(-1);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	cub->height = height;
	if (!cub->textures->floor_set)
		return (NULL);
	if (!cub->textures->ceiling_set)
		return (NULL);
	return (map);
}

char	**load_map(char *file, t_cub *cub)
{
	int		fd;
	char	**map;

	if (ft_check_file_extensions(file, ".cub") == 0)
		return (ft_error(2), NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_error(2);
		return (NULL);
	}
	cub->map_started = 0;
	cub->map_finished = 0;
	calculate_minimap_scale(cub);
	map = read_map_lines(fd, cub);
	close(fd);
	if (!map || !map[0])
	{
		ft_error(8);
		return (NULL);
	}
	return (map);
}
