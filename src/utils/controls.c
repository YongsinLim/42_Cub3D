/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@studekl.edu.my>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 16:10:39 by jenlee            #+#    #+#             */
/*   Updated: 2026/07/22 16:00:00 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>

static void	move_player(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	double	buf;

	new_x = game->player.pos_x + move_x;
	new_y = game->player.pos_y + move_y;
	buf = 0.1;
	if (move_x > 0 && game->map[(int)game->player.pos_y]
		[(int)(new_x + buf)] != '1')
		game->player.pos_x = new_x;
	else if (move_x < 0 && game->map[(int)game->player.pos_y]
		[(int)(new_x - buf)] != '1')
		game->player.pos_x = new_x;
	if (move_y > 0 && game->map[(int)(new_y + buf)]
		[(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
	else if (move_y < 0 && game->map[(int)(new_y - buf)]
		[(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

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

int	handle_keys(t_game *game)
{
	double	ms;
	double	rs;

	ms = 0.05;
	rs = 0.03;
	if (game->keys[KEY_W])
		move_player(game, game->player.dir_x * ms,
			game->player.dir_y * ms);
	if (game->keys[KEY_S])
		move_player(game, -game->player.dir_x * ms,
			-game->player.dir_y * ms);
	if (game->keys[KEY_A])
		move_player(game, game->player.dir_y * ms,
			-game->player.dir_x * ms);
	if (game->keys[KEY_D])
		move_player(game, -game->player.dir_y * ms,
			game->player.dir_x * ms);
	if (game->keys[KEY_RIGHT])
		rotate_player(game, rs);
	if (game->keys[KEY_LEFT])
		rotate_player(game, -rs);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 65536)
		game->keys[keycode] = 1;
	if (keycode == KEY_ESC)
		close_window(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 65536)
		game->keys[keycode] = 0;
	return (0);
}
