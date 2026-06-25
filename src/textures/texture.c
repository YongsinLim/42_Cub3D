/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 18:31:59 by yolim             #+#    #+#             */
/*   Updated: 2026/06/24 18:47:28 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->tex[i].img = mlx_xpm_file_to_image(game->mlx,
				game->tex[i].path, &game->tex[i].width,
				&game->tex[i].height);
		if (!game->tex[i].img)
			error_exit("Failed to load texture");
		game->tex[i].addr = mlx_get_data_addr(game->tex[i].img,
				&game->tex[i].bpp, &game->tex[i].line_len,
				&game->tex[i].endian);
		i++;
	}
}
