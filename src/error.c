/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:44:30 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/06 16:21:53 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_error(int i)
{
	if (i == 1)
		printf("Error: map don't closed.\n");
	if (i == 2)
		printf("Failed to open map file\n");
	if (i == 3)
		printf("Invalid floor color format\n");
	if (i == 4)
		printf("Error in number of players\n");
	if (i == 5)
		printf("Map not rectangular\n");
	if (i == 6)
		printf("Character invalid\n");
	if (i == 7)
		printf("Not copy map\n");
	if (i == 8)
		printf("Invalid map\n");
	if (i == 9)
		printf("Error: Memory\n");
	if (i == 10)
		printf("Error: Number of argument\n");
	return (0);
}

int	ft_error_mlx(int i)
{
	if (i == 1)
		printf("Problem with the MLX\n");
	if (i == 2)
		printf("Problem loading the textures\n");
	return (0);
}
