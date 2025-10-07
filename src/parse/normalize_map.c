/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:14:29 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/06 18:56:10 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_max_width(t_cub *game)
{
	int	i;
	int	len;

	i = 0;
	game->width = 0;
	while (i < game->height)
	{
		len = ft_strlen(game->map[i]);
		if (len > game->width)
			game->width = len;
		i++;
	}
}

static int	fill_short_lines(t_cub *game)
{
	int		i;
	int		len;
	char	*new_line;

	i = 0;
	while (i < game->height)
	{
		len = ft_strlen(game->map[i]);
		if (len < game->width)
		{
			new_line = malloc(game->width + 1);
			if (!new_line)
				return (ft_error(9));
			ft_memset(new_line, ' ', game->width);
			ft_memcpy(new_line, game->map[i], len);
			new_line[game->width] = '\0';
			free(game->map[i]);
			game->map[i] = new_line;
		}
		i++;
	}
	return (1);
}

int	normalize_map(t_cub *game)
{
	get_max_width(game);
	if (!fill_short_lines(game))
		return (0);
	return (1);
}
