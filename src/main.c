/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@studekl.edu.my>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:38:32 by yolim             #+#    #+#             */
/*   Updated: 2026/06/11 16:07:26 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit("Usage: ./cub3D map.cub");
	ft_memset(&game, 0, sizeof(t_game)); //zero everything
	game.floor_colour = 0x00228B22;   // Forest Green
	game.ceiling_colour = 0x0087CEEB; // Sky Blue
	//parse(&game, argv[1]);


	//Temporary
	// Example starting values (facing North)
	(void)argv;
	game.player.pos_x = 5.0; // Assume we start in an empty space on the map
	game.player.pos_y = 5.0;
	game.player.dir_x = 0.0;
	game.player.dir_y = -1.0;
	game.player.plane_x = 0.66; // The standard FOV is created by a 0.66 plane
	game.player.plane_y = 0.0;


	init_render(&game); // JJ functions
	return (0);
}
