/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@studekl.edu.my>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:37:21 by jenlee            #+#    #+#             */
/*   Updated: 2026/06/11 15:37:21 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_ray_vars(t_game *game, int x);
void	calc_step_and_side_dist(t_game *game);
void	draw_untextured_line(t_game *game, int x);
void	perform_dda(t_game *game);

void	raycast_walls(t_game *game)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray_vars(game, x);
		calc_step_and_side_dist(game);
		perform_dda(game);
		// For now, will draw untextured lines to test the math
		// draw_wall_column(game, x); 
		draw_untextured_line(game, x);
		x++;
	}
}

void	init_ray_vars(t_game *game, int x)
{
	game->ray.camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1.0;
	game->ray.ray_dir_x = game->player.dir_x + game->player.plane_x
		* game->ray.camera_x;
	game->ray.ray_dir_y = game->player.dir_y + game->player.plane_y
		* game->ray.camera_x;
	game->ray.map_x = (int)game->player.pos_x;
	game->ray.map_y = (int)game->player.pos_y;
	if (game->ray.ray_dir_x == 0)
		game->ray.delta_dist_x = 1e30;
	else
		game->ray.delta_dist_x = fabs(1.0 / game->ray.ray_dir_x);
	if (game->ray.ray_dir_y == 0)
		game->ray.delta_dist_y = 1e30;
	else
		game->ray.delta_dist_y = fabs(1.0 / game->ray.ray_dir_y);
	game->ray.hit = 0;
}

void	calc_step_and_side_dist(t_game *game)
{
	if (game->ray.ray_dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist_x = (game->player.pos_x - game->ray.map_x)
			* game->ray.delta_dist_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist_x = (game->ray.map_x + 1.0 - game->player.pos_x)
			* game->ray.delta_dist_x;
	}
	if (game->ray.ray_dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist_y = (game->player.pos_y - game->ray.map_y)
			* game->ray.delta_dist_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist_y = (game->ray.map_y + 1.0 - game->player.pos_y)
			* game->ray.delta_dist_y;
	}
}

void	perform_dda(t_game *game)
{
	while (game->ray.hit == 0)
	{
		// Jump to next map square, either in x-direction, or in y-direction
		if (game->ray.side_dist_x < game->ray.side_dist_y)
		{
			game->ray.side_dist_x += game->ray.delta_dist_x;
			game->ray.map_x += game->ray.step_x;
			game->ray.side = 0; // 0 means we hit an East/West wall
		}
		else
		{
			game->ray.side_dist_y += game->ray.delta_dist_y;
			game->ray.map_y += game->ray.step_y;
			game->ray.side = 1; // 1 means we hit a North/South wall
		}
		// Temporary Fake Map Boundary for Testing
		// Pretend there are solid walls at coordinates 0 and 9
		if (game->ray.map_x <= 0 || game->ray.map_x >= 9
			|| game->ray.map_y <= 0 || game->ray.map_y >= 9)
		{
			game->ray.hit = 1;
		}
		// FUTURE IMPLEMENTATION (Once parsing is done):
		// if (game->map[game->ray.map_y][game->ray.map_x] == '1')
		// 	game->ray.hit = 1;
	}
}

void	draw_untextured_line(t_game *game, int x)
{
	int	color;
	int	y;

	// 1. Calculate distance projected on camera direction
	if (game->ray.side == 0)
		game->ray.perp_wall_dist = (game->ray.side_dist_x - game->ray.delta_dist_x);
	else
		game->ray.perp_wall_dist = (game->ray.side_dist_y - game->ray.delta_dist_y);
	// Prevent divide by zero if player is literally inside a wall
	if (game->ray.perp_wall_dist == 0)
		game->ray.perp_wall_dist = 0.01;
	// 2. Calculate height of line to draw on screen
	game->ray.line_height = (int)(SCREEN_HEIGHT / game->ray.perp_wall_dist);
	// 3. Calculate lowest and highest pixel to fill in current stripe
	game->ray.draw_start = -game->ray.line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	game->ray.draw_end = game->ray.line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->ray.draw_end >= SCREEN_HEIGHT)
		game->ray.draw_end = SCREEN_HEIGHT - 1;
	// 4. Choose a solid color depending on orientation (N, S, E, W)
	if (game->ray.side == 0)
	{
		if (game->ray.ray_dir_x > 0)
			color = 0x00FF0000; // Red (West face)
		else
			color = 0x0000FF00; // Green (East face)
	}
	else
	{
		if (game->ray.ray_dir_y > 0)
			color = 0x000000FF; // Blue (North face)
		else
			color = 0x00FFFF00; // Yellow (South face)
	}
	// 5. Draw the vertical line column
	y = game->ray.draw_start;
	while (y <= game->ray.draw_end)
	{
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
}
