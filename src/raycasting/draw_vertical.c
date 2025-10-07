/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:33:49 by pablalva          #+#    #+#             */
/*   Updated: 2025/10/06 15:36:25 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_ceiling_or_floor(t_cub *cub, int x, int i, int ceiling)
{
	if (ceiling)
		put_pixel(cub, x, i, rgb_to_int(cub->textures->ceiling_rgb));
	else
		put_pixel(cub, x, i, rgb_to_int(cub->textures->floor_rgb));
}

static void	draw_texture_pixel(t_cub *cub, int x, int i, t_draw_ctx *ctx)
{
	float	tex_y;

	tex_y = (float)(i - ctx->start_height) / ctx->section_size;
	put_pixel(cub, x, i, map_pixel_from_texture(ctx->texture, ctx->coll,
			tex_y));
}

static void	draw_door_pixel(t_cub *cub, int x, int i, t_draw_ctx *ctx)
{
	int	door_h;

	door_h = (int)(ctx->section_size * (1.0f - cub->door_progress));
	if (i >= ctx->start_height + door_h)
		draw_ceiling_or_floor(cub, x, i, i < HEIGHT / 2);
	else
		draw_texture_pixel(cub, x, i, ctx);
}

static void	draw_wall_or_door(t_cub *cub, int x, int i, t_draw_ctx *ctx)
{
	if (ctx->coll.direction == DOOR)
		draw_door_pixel(cub, x, i, ctx);
	else
		draw_texture_pixel(cub, x, i, ctx);
}

void	draw_vertical_section(t_cub *cub, int x, t_collision coll)
{
	t_image		texture;
	t_draw_ctx	ctx;
	int			i;
	int			section_size;
	int			start_height;

	if (coll.direction == SOUTH)
		coll.offset = 1 - coll.offset;
	if (coll.dist == 0)
		coll.dist = 0.1;
	texture = set_texture(cub, coll.direction);
	section_size = (HEIGHT * C_SIZE) / coll.dist;
	start_height = (HEIGHT - section_size) / 2;
	ctx = (t_draw_ctx){texture, coll, section_size, start_height};
	i = -1;
	while (++i < HEIGHT)
	{
		if (i < start_height)
			draw_ceiling_or_floor(cub, x, i, 1);
		else if (i < start_height + section_size)
			draw_wall_or_door(cub, x, i, &ctx);
		else
			draw_ceiling_or_floor(cub, x, i, 0);
	}
}
