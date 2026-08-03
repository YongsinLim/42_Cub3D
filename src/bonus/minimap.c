/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@studekl.edu.my>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 17:30:00 by jenlee            #+#    #+#             */
/*   Updated: 2026/07/22 17:45:00 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define MM_SCALE 10
#define MM_RAD 6
#define MM_OFF 15

static int	is_valid_row(char **map, int row)
{
	int	i;

	if (!map || row < 0)
		return (0);
	i = 0;
	while (map[i])
	{
		if (i == row)
			return (1);
		i++;
	}
	return (0);
}

static void	draw_mm_square(t_game *game, int sx, int sy, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MM_SCALE)
	{
		j = 0;
		while (j < MM_SCALE)
		{
			my_mlx_pixel_put(game, sx + i, sy + j, color);
			j++;
		}
		i++;
	}
}

static void	draw_mm_tile(t_game *game, int dx, int dy)
{
	int	mx;
	int	my;
	int	sx;
	int	sy;

	mx = (int)game->player.pos_x + dx;
	my = (int)game->player.pos_y + dy;
	sx = MM_OFF + (dx + MM_RAD) * MM_SCALE;
	sy = MM_OFF + (dy + MM_RAD) * MM_SCALE;
	if (!is_valid_row(game->map, my) || mx < 0
		|| mx >= (int)ft_strlen(game->map[my]))
		draw_mm_square(game, sx, sy, 0x000000);
	else if (game->map[my][mx] == '1')
		draw_mm_square(game, sx, sy, 0x333333);
	else if (game->map[my][mx] == '0')
		draw_mm_square(game, sx, sy, 0xCCCCCC);
	else
		draw_mm_square(game, sx, sy, 0x000000);
}

void	draw_minimap(t_game *game)
{
	int	dx;
	int	dy;
	int	cx;
	int	cy;

	dy = -MM_RAD;
	while (dy <= MM_RAD)
	{
		dx = -MM_RAD;
		while (dx <= MM_RAD)
		{
			draw_mm_tile(game, dx, dy);
			dx++;
		}
		dy++;
	}
	cx = MM_OFF + MM_RAD * MM_SCALE + (MM_SCALE / 2);
	cy = MM_OFF + MM_RAD * MM_SCALE + (MM_SCALE / 2);
	my_mlx_pixel_put(game, cx, cy, 0xFF0000);
	my_mlx_pixel_put(game, cx + 1, cy, 0xFF0000);
	my_mlx_pixel_put(game, cx, cy + 1, 0xFF0000);
	my_mlx_pixel_put(game, cx + 1, cy + 1, 0xFF0000);
}