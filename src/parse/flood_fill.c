/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:08:09 by ksudyn            #+#    #+#             */
/*   Updated: 2025/09/29 11:26:14 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	flood_fill(t_cub *game, int x, int y, char **map_copy)
{
	if (x < 0 || x >= game->width || y < 0 || y >= game->height)
	{
		ft_error(1);
		free_matrix(map_copy);
		safe_exit(game);
	}
	if (map_copy[y][x] == ' ')
	{
		ft_error(1);
		free_matrix(map_copy);
		safe_exit(game);
	}
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'V' || map_copy[y][x] == ' ')
		return ;
	map_copy[y][x] = 'V';
	flood_fill(game, x + 1, y, map_copy);
	flood_fill(game, x - 1, y, map_copy);
	flood_fill(game, x, y + 1, map_copy);
	flood_fill(game, x, y - 1, map_copy);
}

char	**copy_map(char **map, int height)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (i--)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix)
	{
		while (matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
}

int	check_closed_map(t_cub *game)
{
	char	**map_copy;

	map_copy = copy_map(game->map, game->height);
	if (!map_copy)
	{
		ft_error(7);
		exit(1);
	}
	flood_fill(game, game->player_x, game->player_y, map_copy);
	free_matrix(map_copy);
	game->old_map = copy_map(game->map, game->height);
	if (!game->old_map)
	{
		ft_error(7);
		exit(1);
	}
	return (1);
}
