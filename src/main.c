/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@studekl.edu.my>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:38:32 by yolim             #+#    #+#             */
/*   Updated: 2026/06/19 18:41:53 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit("Usage: ./cub3D map.cub");
	ft_memset(&game, 0, sizeof(t_game)); //zero everything
	game.floor_colour = -1;
	game.ceiling_colour = -1;
	parse(&game, argv[1]);
	init_render(&game); // JJ functions
	return (0);
}
