/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@studekl.edu.my>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 16:12:54 by jenlee            #+#    #+#             */
/*   Updated: 2026/06/30 15:36:13 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned int	get_tex_color(t_texture *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

int	get_tex_idx(t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.ray_dir_x > 0)
			return (3);
		return (2);
	}
	if (game->ray.ray_dir_y > 0)
		return (1);
	return (0);
}

static int	calculate_tex_x(t_game *game, t_texture *tex)
{
	double	wall_x;
	int		tex_x;

	if (game->ray.side == 0)
		wall_x = game->player.pos_y + game->ray.perp_wall_dist
			* game->ray.ray_dir_y;
	else
		wall_x = game->player.pos_x + game->ray.perp_wall_dist
			* game->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if ((game->ray.side == 0 && game->ray.ray_dir_x < 0)
		|| (game->ray.side == 1 && game->ray.ray_dir_y > 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

void	draw_wall_column(t_game *game, int x, int y)
{
	t_texture	*tex;
	int			tex_x;
	double		step;
	double		tex_pos;

	tex = &game->tex[get_tex_idx(game)];
	tex_x = calculate_tex_x(game, tex);
	step = 1.0 * tex->height / game->ray.line_height;
	tex_pos = (game->ray.draw_start - SCREEN_HEIGHT / 2
			+ game->ray.line_height / 2) * step;
	y = game->ray.draw_start;
	while (y <= game->ray.draw_end)
	{
		my_mlx_pixel_put(game, x, y, get_tex_color(tex, tex_x, (int)tex_pos));
		tex_pos += step;
		y++;
	}
}
