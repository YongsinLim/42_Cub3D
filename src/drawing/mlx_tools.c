/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@studekl.edu.my>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:13:08 by jenlee            #+#    #+#             */
/*   Updated: 2026/07/22 16:30:00 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

int	render_frame(t_game *game)
{
	handle_keys(game);
	draw_floor_and_ceiling(game);
	raycast_walls(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

void	init_render(t_game *game)
{
	ft_bzero(game->keys, sizeof(game->keys));
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("Failed to initialize MLX");
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "cub3D");
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_len, &game->endian);
	load_textures(game);
	mlx_loop_hook(game->mlx, render_frame, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop(game->mlx);
}
