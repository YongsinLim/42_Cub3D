/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:35:21 by yolim             #+#    #+#             */
/*   Updated: 2026/06/18 17:53:46 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	parse(t_game *game, char *path)
{
	char	**lines;
	int		i;
	int		map_start;

	check_file_extension(path);
	lines = read_file(path);
	if (!lines)
		error_exit("Failed to read file");
	i = 0;
	while (lines[i])
	{
		if (is_element_line(lines[i]))
			parse_element(game, lines[i]);
		i++;
	}
	validate_elements(game);
	map_start = find_map_start(lines);
	parse_map(game, lines, map_start);
	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
	find_map_cols(game);
	validate_map_chars(game);
	find_player(game);
	validate_map_enclosed(game);
}
