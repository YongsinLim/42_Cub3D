/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:38:32 by yolim             #+#    #+#             */
/*   Updated: 2026/05/30 13:38:45 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit("Usage: ./cub3D map.cub");
	ft_memset(&game, 0, sizeof(t_game)); //zero everything
	game.floor_colour = -1; // set explicitly, bcos 0 is valid colour
	game.ceiling_colour = -1;
	parse(&game, argv[1]);
	init_render(&game); // JJ functions
	return (0);
}
