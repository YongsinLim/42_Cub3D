/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@studekl.edu.my>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 17:00:00 by jenlee            #+#    #+#             */
/*   Updated: 2026/08/18 18:50:32 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Forward declaration for Linux MLX display cleanup
#ifdef __linux__

int	mlx_destroy_display(void *mlx_ptr);
#endif

void	free_2d_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex[i].path)
			free(game->tex[i].path);
		if (game->tex[i].img)
			mlx_destroy_image(game->mlx, game->tex[i].img);
		i++;
	}
}

#ifdef __linux__

static void	destroy_mlx(t_game *game)
{
	if (!game->mlx)
		return ;
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}
#else

static void	destroy_mlx(t_game *game)
{
	if (!game->mlx)
		return ;
	free(game->mlx);
}
#endif

int	close_game(t_game *game)
{
	if (!game)
		exit(0);
	if (game->map)
		free_2d_array(game->map);
	free_textures(game);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	destroy_mlx(game);
	exit(0);
	return (0);
}
