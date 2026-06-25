/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:35:51 by yolim             #+#    #+#             */
/*   Updated: 2026/06/19 22:30:29 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_if_empty(char *prefix, int position, t_game *game, char *path)
{
	char	msg[64];

	if (game->tex[position].path)
	{
		ft_strlcpy(msg, "Duplicate ", sizeof(msg));
		ft_strlcat(msg, prefix, sizeof(msg));
		error_exit(msg);
	}
	game->tex[position].path = path;
}

// Save each element type's path
void	parse_element(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		set_if_empty("NO texture", 0, game, ft_strtrim(line + 3, " \n"));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		set_if_empty("SO texture", 1, game, ft_strtrim(line + 3, " \n"));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		set_if_empty("WE texture", 2, game, ft_strtrim(line + 3, " \n"));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		set_if_empty("EA texture", 3, game, ft_strtrim(line + 3, " \n"));
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (game->floor_colour != -1)
			error_exit("Duplicate Floor colour");
		game->floor_colour = parse_rgb(line + 2);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (game->ceiling_colour != -1)
			error_exit("Duplicate Ceiling colour");
		game->ceiling_colour = parse_rgb(line + 2);
	}
}

// Check none of 6 elements are missing
void	validate_elements(t_game *game)
{
	if (!game->tex[0].path)
		error_exit("Missing NO texture");
	if (!game->tex[1].path)
		error_exit("Missing SO texture");
	if (!game->tex[2].path)
		error_exit("Missing WE texture");
	if (!game->tex[3].path)
		error_exit("Missing EA texture");
	if (game->floor_colour == -1)
		error_exit("Missing Floor colour");
	if (game->ceiling_colour == -1)
		error_exit("Missing Ceiling colour");
}

// Parse RGB color — "220,100,0" → int
int	parse_rgb(char *str)
{
	char	**colour_array;
	int		r;
	int		g;
	int		b;

	colour_array = ft_split(str, ',');
	if (!colour_array || !colour_array[0] || !colour_array[1]
		|| !colour_array[2] || colour_array[3])
		error_exit("Invalid RGB format");
	r = ft_atoi(colour_array[0]);
	g = ft_atoi(colour_array[1]);
	b = ft_atoi(colour_array[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_exit("Colour value out of range [0, 255]");
	free(colour_array[0]);
	free(colour_array[1]);
	free(colour_array[2]);
	free(colour_array);
	return (r << 16 | g << 8 | b);
}
