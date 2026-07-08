/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@studekl.edu.my>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 16:10:39 by jenlee            #+#    #+#             */
/*   Updated: 2026/07/08 15:43:49 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>

#ifdef __linux__
# define KEY_ESC	65307
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
#else
# define KEY_ESC	53
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_LEFT	123
# define KEY_RIGHT	124
#endif

static void	move_player(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	double	buffer;

	new_x = game->player.pos_x + move_x;
	new_y = game->player.pos_y + move_y;
	buffer = 0.1;
	if (move_x > 0 && game->map[(int)game->player.pos_y][(int)(new_x + buffer)] != '1')
		game->player.pos_x = new_x;
	else if (move_x < 0 && game->map[(int)game->player.pos_y][(int)(new_x - buffer)] != '1')
		game->player.pos_x = new_x;
	if (move_y > 0 && game->map[(int)(new_y + buffer)][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
	else if (move_y < 0 && game->map[(int)(new_y - buffer)][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

// Applies the 2D rotation matrix to the player's vectors
static void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed)
		+ game->player.dir_y * cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed)
		+ game->player.plane_y * cos(rot_speed);
}

int	key_press(int keycode, t_game *game)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.5;
	rot_speed = 0.1;
	if (keycode == KEY_ESC)
		close_window(game);
	if (keycode == KEY_W)
		move_player(game, game->player.dir_x * move_speed,
			game->player.dir_y * move_speed);
	if (keycode == KEY_S)
		move_player(game, -game->player.dir_x * move_speed,
			-game->player.dir_y * move_speed);
	if (keycode == KEY_A)
		move_player(game, game->player.dir_y * move_speed,
			-game->player.dir_x * move_speed);
	if (keycode == KEY_D)
		move_player(game, -game->player.dir_y * move_speed,
			game->player.dir_x * move_speed);
	if (keycode == KEY_RIGHT)
		rotate_player(game, rot_speed);
	if (keycode == KEY_LEFT)
		rotate_player(game, -rot_speed);
	return (0);
}

int	close_window(t_game *game)
{
	(void)game;
	printf("Window closed");
	exit(0);
}
