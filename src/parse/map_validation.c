/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 12:10:54 by yolim             #+#    #+#             */
/*   Updated: 2026/07/08 15:35:26 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Validate char in map (must be one of '0', '1', ' ', 'N', 'S', 'E', 'W')
void	validate_map_chars(t_game *game)
{
	int		r;
	int		c;
	char	ch;

	r = 0;
	while (r < game->map_rows)
	{
		c = 0;
		while (game->map[r][c])
		{
			ch = game->map[r][c];
			if (ch != '0' && ch != '1' && ch != ' ' && ch != 'N' && ch != 'S'
				&& ch != 'E' && ch != 'W')
				error_exit("Invalid character in map");
			c++;
		}
		r++;
	}
}

char	**copy_map(t_game *game)
{
	char	**copy;
	int		r;

	copy = malloc(sizeof(char *) * (game->map_rows + 1));
	if (!copy)
		error_exit("Malloc failed");
	r = 0;
	while (r < game->map_rows)
	{
		copy[r] = ft_strdup(game->map[r]);
		if (!copy[r])
			error_exit("Malloc failed");
		r++;
	}
	copy[r] = NULL;
	return (copy);
}

// BFS = Breadth-First Search 广度优先搜索
int	flood_fill_bfs(char **map, int rows, int max_cols, t_point start)
{
	t_queue	*q;
	t_point	cur;
	int		leaked;

	q = create_queue(rows * max_cols * 4);
	leaked = 0;
	enqueue(q, start.r, start.c);
	while (!is_empty(q))
	{
		cur = dequeue(q);
		leaked = check_cell(map, rows, cur);
		if (leaked)
			break ;
		if (map[cur.r][cur.c] == 'V' || map[cur.r][cur.c] == '1')
			continue ;
		map[cur.r][cur.c] = 'V';
		enqueue(q, cur.r - 1, cur.c);
		enqueue(q, cur.r + 1, cur.c);
		enqueue(q, cur.r, cur.c - 1);
		enqueue(q, cur.r, cur.c + 1);
	}
	free(q->cells);
	free(q);
	return (leaked);
}

// leaked: 0 = ok, 1 = outer space (X) or out of bounds, 2 = hole (' ')
int	check_cell(char **map, int rows, t_point cur)
{
	if (cur.r < 0 || cur.c < 0 || cur.r >= rows
		|| cur.c >= (int)ft_strlen(map[cur.r]))
		return (1);
	if (map[cur.r][cur.c] == 'X')
		return (1);
	if (map[cur.r][cur.c] == ' ')
		return (2);
	return (0);
}

void	validate_map_enclosed(t_game *game)
{
	char	**copy;
	int		result;
	t_point	start;
	int		i;

	copy = copy_map(game);
	mark_outer_spaces(copy, game->map_rows, game->map_cols);
	start.r = (int)game->player.pos_y;
	start.c = (int)game->player.pos_x;
	result = flood_fill_bfs(copy, game->map_rows, game->map_cols, start);
	i = 0;
	while (copy[i])
	{
		free(copy[i]);
		i++;
	}
	free(copy);
	if (result == 1)
		error_exit("Map is not enclosed by walls");
	else if (result == 2)
		error_exit("Map contains hole (space inside map)");
}
