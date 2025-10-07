/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:47:05 by ksudyn            #+#    #+#             */
/*   Updated: 2025/10/06 19:44:23 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define FOV 60
# define WIDTH 800
# define HEIGHT 600
# define C_SIZE 64
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define DOOR 4

# define NUM_TEXTURES 5

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define KEY_ESC 65307

# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_DESTROY 17

# define NO_EVENT_MASK 0
# define KEY_PRESS_MASK 1L
# define KEY_RELEASE_MASK 2L

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_image
{
	void		*img;
	char		*data;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}				t_image;

typedef struct s_player
{
	float		x;
	float		y;
	float		angle;
	float		delta_x;
	float		delta_y;

	int			key_up;
	int			key_down;
	int			key_left;
	int			key_right;
	int			key_space;
	int			left_rotate;
	int			right_rotate;
}				t_player;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_mlx;

typedef struct s_textures
{
	void		*north;
	void		*south;
	void		*east;
	void		*west;
	void		*door;

	int			ceiling_rgb[3];
	int			floor_rgb[3];
	int			ceiling_set;
	int			floor_set;
}				t_textures;

typedef struct s_cub
{
	char		**map;
	char		**old_map;
	int			width;
	int			height;
	float		player_x;
	float		player_y;
	char		player_dir;
	int			map_started;
	int			map_finished;
	int			minimap_scale;
	int			minimap_offset_x;
	int			minimap_offset_y;
	int			door_open;
	float		door_progress;
	int			block_mouse;
	int			textures_counter;

	t_textures	*textures;
	t_mlx		*mlx;
	t_player	player;
	char		*textures_path[NUM_TEXTURES];
	t_image		image[NUM_TEXTURES];
}				t_cub;

typedef struct s_collision
{
	float		dist;
	float		offset;
	int			direction;
}				t_collision;
typedef struct s_draw_ctx
{
	t_image		texture;
	t_collision	coll;
	int			section_size;
	int			start_height;
}				t_draw_ctx;

/*....check_map.c....*/
int				check_valid_chars(t_cub *game);
int				check_player_count(t_cub *game);
int				check_top_bottom_walls(t_cub *game);
int				check_side_walls(t_cub *game);
/*....dimensions.c....*/
int				dimensions(char *line, char ***map, int *height, t_cub *cub);
/*....flood_fill.c....*/
void			flood_fill(t_cub *game, int x, int y, char **map_copy);
char			**copy_map(char **map, int height);
void			free_matrix(char **matrix);
int				check_closed_map(t_cub *game);
/*....load_map.c....*/
char			**load_map(char *file, t_cub *cub);
/*....normalize_map.c....*/
int				normalize_map(t_cub *game);
/*....textures_color.c....*/
int				parse_color_line(char *line, t_cub *game);
int				parse_texture_line(char *line, t_cub *cub);
/*....utils_parse.c....*/
int				ft_check_file_extensions(char *map_file_name, char *extension);
int				is_valid_map_char(char c);
int				is_player(char c);
/*....validate_map.c....*/
int				validate_map(t_cub *game);
/*....collision.c....*/
char			get_map_cell(t_cub *cub, int grid_x, int grid_y);
int				is_walkable_char(char c);
int				check_collision(t_cub *cub, float world_x, float world_y);
int				check_collision_radius(t_cub *cub, float x, float y, float r);
/*....math_utils.c....*/
float			deg_to_rad(float deg);
float			sqr(float n);
int				safe_exit(t_cub *cub);
int				rgb_to_int(int rgb[3]);
/*....player_move.c....*/
void			move_forward(t_cub *cub, float speed);
void			move_backward(t_cub *cub, float speed);
void			move_left(t_cub *cub, float speed);
void			move_right(t_cub *cub, float speed);
void			rotate_player(t_player *p, float angle);
int				mouse_move(int x, int y, t_cub *cub);
/*....doors.c....*/
void			close_doors(t_cub *cub);
void			open_doors(t_cub *cub);
void			try_close_doors(t_cub *cub);
/*....ray_player.c....*/
void			init_hooks(t_cub *cub);
/*....raycasting_cast.c....*/
void			init_collision(t_collision *col);
t_collision		cast_ray(t_cub *cub, float ray_angle);
/*....raycasting_horiz.c....*/
void			set_collision(t_collision *col, float dist, float offset,
					int dir);
void			cast_row_ray_down(t_cub *cub, float ray_angle,
					t_collision *hit);
void			cast_row_ray_up(t_cub *cub, float ray_angle, t_collision *hit);
/*....raycasting_vert.c....*/
void			cast_column_ray_right(t_cub *cub, float ray_angle,
					t_collision *hit);
void			cast_column_ray_left(t_cub *cub, float ray_angle,
					t_collision *hit);
/*....render_frame.c...*/
void			put_pixel(t_cub *cub, int x, int y, int color);
void			render_frame(t_cub *cub);
t_image			set_texture(t_cub *cub, int direction);
void			draw_vertical_section(t_cub *cub, int x, t_collision coll);
int				map_pixel_from_texture(t_image texture, t_collision col,
					float v_offset);
/*....cub3d.c...*/
int				cub3d(t_cub *cub);
int				key_release_hook(int keycode, t_cub *cub);
int				key_press_hook(int keycode, t_cub *cub);
int				main_loop(t_cub *cub);
/*....error.c...*/
int				ft_error(int i);
int				ft_error_mlx(int i);
/*....init.c...*/
void			init_player(t_cub *cub);
void			init_texture_paths(t_cub *cub);
void			init_struct(t_cub *cub);
/*....load_textures.c...*/
int				load_textures(t_cub *cub);
int				is_texture_line(char *line);
/*....mini_map.c...*/
void			draw_minimap(t_cub *cub);
void			calculate_minimap_scale(t_cub *cub);

void			cleanup(t_cub *cub);

#endif