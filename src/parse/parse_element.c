/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:35:51 by yolim             #+#    #+#             */
/*   Updated: 2026/10/29 23:10:00 by jenlee           ###   ########.fr       */
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
		set_if_empty("NO texture", 0, game, ft_strtrim(line + 3, " \t\n"));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		set_if_empty("SO texture", 1, game, ft_strtrim(line + 3, " \t\n"));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		set_if_empty("WE texture", 2, game, ft_strtrim(line + 3, " \t\n"));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		set_if_empty("EA texture", 3, game, ft_strtrim(line + 3, " \t\n"));
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

static int	is_valid_num(char *str)
{
	int	i;
	int	digits;

	i = 0;
	digits = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digits++;
		i++;
	}
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	return (digits > 0 && digits <= 3 && str[i] == '\0');
}

// Parse RGB color — "220,100,0" → int
int	parse_rgb(char *str)
{
	char	**colour_array;
	int		rgb[3];
	int		i;
	int		commas;

	commas = 0;
	i = 0;
	while (str[i])
		if (str[i++] == ',')
			commas++;
	if (commas != 2)
		error_exit("Invalid RGB format");
	colour_array = ft_split(str, ',');
	if (!colour_array || !colour_array[0] || !colour_array[1]
		|| !colour_array[2] || colour_array[3] || !is_valid_num(colour_array[0])
		|| !is_valid_num(colour_array[1]) || !is_valid_num(colour_array[2]))
		(free_lines(colour_array), error_exit("Invalid RGB format"));
	rgb[0] = ft_atoi(colour_array[0]);
	rgb[1] = ft_atoi(colour_array[1]);
	rgb[2] = ft_atoi(colour_array[2]);
	free_lines(colour_array);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
		error_exit("Colour value out of range [0, 255]");
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
