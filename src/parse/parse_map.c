/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:36:24 by yolim             #+#    #+#             */
/*   Updated: 2026/05/21 23:01:11 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int count_file_lines(char *path) {
    int     fd;
    int     count;
    char    *line;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        error_exit("Cannot open file");
    count = 0;
    while ((line = get_next_line(fd)) != NULL) {
        free(line);
        count++;
    }
    close(fd);
    return (count);
}

// read every line into a char** array
char    **read_file(char *path) {
    int     fd;
    char    **lines_array;
    char    *line;
    int     i;

    lines_array = malloc(sizeof(char *) * (count_file_lines(path) + 1));
    if (!lines_array)
        return (NULL);
    fd = open(path, O_RDONLY);
    if (fd < 0)
        error_exit("Cannot open file");
    i = 0;
    while ((line = get_next_line(fd)) != NULL) {
        lines_array[i] = line;
        i++;
    }
    lines_array[i] = NULL;
    close(fd);
    return (lines_array);
}

// identify which lines are direction elements vs map's line character
int is_map_line(char *line) {
    int i;

    i = 0;
    while (line[i] == ' ')
        i++;
    return (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S'
        || line[i] == 'E' || line[i] == 'W');
}
