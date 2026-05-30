/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:36:56 by yolim             #+#    #+#             */
/*   Updated: 2026/05/30 13:22:09 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Find player position + set initial direction
void	find_player(t_game *game)
{
	int	r;
	int	c;
	int	found;

	found = 0;
	r = 0;
	while (r < game->map_rows)
	{
		c = find_player_start_col_in_row(game->map[r]);
		if (c != -1)
		{
			if (found > 0)
				error_exit("Multiple player starting positions");
			found++;
			game->player.pos_x = c + 0.5;
			game->player.pos_y = r + 0.5;
			set_player_direction(&game->player, game->map[r][c]);
			game->map[r][c] = '0';
		}
		r++;
	}
	if (!found)
		error_exit("No player starting position found");
}

int	find_player_start_col_in_row(char *row)
{
	int	c;

	c = 0;
	while (row[c])
	{
		if (ft_strchr("NSEW", row[c]))
			return (c);
		c++;
	}
	return (-1);
}

void	set_player_direction(t_player *player, char dir)
{
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	if (dir == 'N')
	{
		player->dir_y = -1;
		player->plane_x = 0.66;
	}
	else if (dir == 'S')
	{
		player->dir_y = 1;
		player->plane_x = -0.66;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->plane_y = -0.66;
	}
}
