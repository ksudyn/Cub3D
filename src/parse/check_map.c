/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:16:53 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/06 20:45:09 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_valid_chars(t_cub *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!is_valid_map_char(game->map[i][j]))
				return (ft_error(6));
			if (game->map[i][j] == 'D' && game->textures_path[DOOR] == NULL)
				return (ft_error(6));
			j++;
		}
		i++;
	}
	return (1);
}

int	check_player_count(t_cub *game)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < game->height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (is_player(game->map[i][j]))
			{
				game->player_dir = game->map[i][j];
				game->player_x = j;
				game->player_y = i;
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		return (ft_error(4));
	return (1);
}

int	check_top_bottom_walls(t_cub *game)
{
	int	i;

	i = 0;
	while (game->map[0][i])
	{
		if (game->map[0][i] != '1' && game->map[0][i] != ' ')
			return (ft_error(1));
		i++;
	}
	i = 0;
	while (game->map[game->height - 1][i])
	{
		if (game->map[game->height - 1][i] != '1' && game->map[game->height
			- 1][i] != ' ')
			return (ft_error(1));
		i++;
	}
	return (1);
}

int	check_side_walls(t_cub *game)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	while (i < game->height)
	{
		start = 0;
		while (game->map[i][start] == ' ')
			start++;
		end = ft_strlen(game->map[i]) - 1;
		while (end >= 0 && game->map[i][end] == ' ')
			end--;
		if (end >= start)
		{
			if (game->map[i][start] != '1' && game->map[i][start] != ' ')
				return (ft_error(1));
			if (game->map[i][end] != '1' && game->map[i][end] != ' ')
				return (ft_error(1));
		}
		i++;
	}
	return (1);
}
