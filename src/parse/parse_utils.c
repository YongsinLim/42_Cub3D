/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:37:44 by yolim             #+#    #+#             */
/*   Updated: 2026/07/08 15:21:05 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// check last 4 chars of filename are ".cub"
void	check_file_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
		error_exit("File must have .cub extension");
}

int	count_file_lines(char *path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open file");
	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

// read every line into a char** array
char	**read_file(char *path)
{
	int		fd;
	char	**lines_array;
	char	*line;
	int		i;

	lines_array = malloc(sizeof(char *) * (count_file_lines(path) + 1));
	if (!lines_array)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open file");
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines_array[i] = line;
		i++;
		line = get_next_line(fd);
	}
	lines_array[i] = NULL;
	close(fd);
	return (lines_array);
}

// identify which lines are direction elements vs map's line character
int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S'
		|| line[i] == 'E' || line[i] == 'W');
}
