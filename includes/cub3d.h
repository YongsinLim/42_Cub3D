/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:35:22 by yolim             #+#    #+#             */
/*   Updated: 2026/08/18 18:40:29 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>	// for open
# include <unistd.h>	// for close, read, write
# include <stdio.h>	// for printf, perror
# include <stdlib.h>	// for malloc, free, exit
# include <string.h>	// for strerror
# include <sys/time.h>	// for gettimeofday
# include <math.h>	// for all functions of the math library
# include "../Libft/libft.h"
# include "keycodes.h"

# include "mlx.h"

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600

typedef struct s_texture
{
	char	*path;
	void	*img;	// ← this is ONE WALL TEXTURE image
	char	*addr;	// ← pixel memory of THAT TEXTURE
	int		bpp;	// ← texture's bits per pixel
	int		line_len;	// ← texture's line length
	int		endian;	// ← texture's endian
	int		width;
	int		height;
}			t_texture;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;	// 0 for NS, 1 for EW
	int		line_height;
	int		draw_start;
	int		draw_end;
}				t_ray;

// Store a grid coordinate (row, column) as one unit.
typedef struct s_point
{
	int	r;
	int	c;
}				t_point;

/*
The queue is just an array with two pointers — head chases tail.

  cells: [ (1,1) | (0,1) | (2,1) | (1,0) | (1,2) | ... ]
		   ↑ head                                    ↑ tail
		   next to process                           next empty slot
*/
typedef struct s_queue
{
	t_point	*cells;	// array of coordinates waiting to be checked
	int		head_idx;	// index of next cell to process (front)
	int		tail_idx;	// index of next empty slot (back)
	int		capacity;	// max cells the array can hold
}			t_queue;

/* char		**map:
not 2D array bcos compile time dont know the actual map size
(map sometime not square), char **map can malloc exactly the right size
after read the .cub file
*/

typedef struct s_game
{
	void		*mlx;	// ← this is the SCREEN buffer
	void		*win;
	void		*img;
	char		*addr;	// ← pixel memory of the SCREEN
	int			bpp;	// ← screen's bits per pixel
	int			line_len;	// ← screen's line length
	int			endian;	// ← screen's endian
	char		**map;
	int			map_rows;
	int			map_cols;
	t_texture	tex[4]; // 0=NO 1=SO 2=WE 3=EA
	int			floor_colour;
	int			ceiling_colour;
	t_player	player;
	t_ray		ray;
	int			keys[65536];
}				t_game;

// ----- Parse Map -----
int				is_element_line(char *line);
int				find_map_start(char **lines);
void			parse_map(t_game *game, char **lines, int start);
void			find_map_cols(t_game *game);

// ----- Parse Utils -----
void			check_file_extension(char *path);
int				count_file_lines(char *path);
char			**read_file(char *path);
int				is_map_line(char *line);

// ----- Parse Element -----
void			set_if_empty(char *prefix, int position, t_game *game,
					char *path);
void			parse_element(t_game *game, char *line);
void			validate_elements(t_game *game);
int				parse_rgb(char *str);

// ----- Player Setting -----
void			find_player(t_game *game);
int				find_player_start_col_in_row(char *row);
void			set_player_direction(t_player *player, char dir);

// ----- Map Validation Utils -----
t_queue			*create_queue(int capacity);
void			enqueue(t_queue *q, int r, int c);
t_point			dequeue(t_queue *q);
int				is_empty(t_queue *q);

// ----- Map Validation -----
void			validate_map_chars(t_game *game);
char			**copy_map(t_game *game);
int				flood_fill_bfs(char **map, int rows, int max_cols,
					t_point start);
int				check_cell(char **map, int rows, t_point cur);
void			validate_map_enclosed(t_game *game);

// ----- Space Handling -----
void			bfs_mark_outer_space(char **map, int row, int max_cols,
					t_point start);
void			mark_outer_spaces(char **map, int rows, int max_cols);

// ----- Parse -----
void			parse(t_game *game, char *path);
void			free_lines(char **lines);

// ----- Texture -----
void			load_textures(t_game *game);

// ----- Report Error Functions -----
void			error_exit(char *msg);

// ------Initialising rendering------- //
void			draw_floor_and_ceiling(t_game *game);
int				render_frame(t_game *game);
void			init_render(t_game *game);
void			my_mlx_pixel_put(t_game *game, int x, int y, int color);

// --------Raycasting```````````````````//
void			raycast_walls(t_game *game);
unsigned int	get_tex_color(t_texture *tex, int x, int y);
int				get_tex_idx(t_game *game);
void			draw_wall_column(t_game *game, int x, int y);

// --------Mlx Hooks-------------//
int				key_press(int keycode, t_game *game);
int				close_window(t_game *game);
int				handle_keys(t_game *game);
int				key_release(int keycode, t_game *game);
int				close_game(t_game *game);
# ifdef BONUS
void			draw_minimap(t_game *game);
# endif

#endif
