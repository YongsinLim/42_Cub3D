/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:36:24 by yolim             #+#    #+#             */
/*   Updated: 2026/05/30 13:27:15 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_element_line(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0);
}

/*
Find where the map starts in the lines array, map is always after all elements
Map starts after elements + empty lines
*/
int	find_map_start(char **lines)
{
	int	i;
	int	map_start;

	i = 0;
	map_start = -1;
	while (lines[i])
	{
		if (map_start == -1 && is_map_line(lines[i])
			&& !is_element_line(lines[i]))
			map_start = i;
		else if (map_start != -1 && is_element_line(lines[i]))
			error_exit("Map must be the last element in the file");
		i++;
	}
	if (map_start == -1)
		error_exit("No map found in file");
	return (map_start);
}

// Read map rows into game->map (char**)
void	parse_map(t_game *game, char **lines, int start)
{
	int	i;
	int	row;

	i = start;
	row = 0;
	while (lines[i] && is_map_line(lines[i]))
	{
		i++;
		row++;
	}
	game->map_rows = row;
	game->map = malloc(sizeof(char *) * (row + 1));
	if (!game->map)
		error_exit("Malloc failed");
	i = 0;
	while (i < row)
	{
		game->map[i] = ft_strtrim(lines[start + i], "\n");
		i++;
	}
	game->map[i] = NULL;
}

// Find map_cols — widest row
void	find_map_cols(t_game *game)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	game->map_cols = 0;
	while (game->map[i])
	{
		length = ft_strlen(game->map[i]);
		if (length > game->map_cols)
			game->map_cols = length;
		i++;
	}
}
