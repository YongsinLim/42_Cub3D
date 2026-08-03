/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 18:08:54 by yolim             #+#    #+#             */
/*   Updated: 2026/07/07 18:00:36 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// to solve invalid map that space exist outer and inner with unenclosed wall
void	bfs_mark_outer_space(char **map, int row, int max_cols, t_point start)
{
	t_queue	*q;
	t_point	cur;

	q = create_queue(row * max_cols * 4);
	enqueue(q, start.r, start.c);
	while (!is_empty(q))
	{
		cur = dequeue(q);
		if (cur.r < 0 || cur.c < 0 || cur.r >= row
			|| cur.c >= (int)ft_strlen(map[cur.r]) || map[cur.r][cur.c] != ' ')
			continue ;
		map[cur.r][cur.c] = 'X';
		enqueue(q, cur.r - 1, cur.c);
		enqueue(q, cur.r + 1, cur.c);
		enqueue(q, cur.r, cur.c - 1);
		enqueue(q, cur.r, cur.c + 1);
	}
	free(q->cells);
	free(q);
}

void	mark_outer_spaces(char **map, int rows, int max_cols)
{
	int		r;
	int		c;
	int		len;
	t_point	start;

	r = 0;
	while (r < rows)
	{
		len = (int)ft_strlen(map[r]);
		c = 0;
		while (c < len)
		{
			if ((r == 0 || r == rows - 1 || c == 0 || c == len - 1)
				&& map[r][c] == ' ')
			{
				start.r = r;
				start.c = c;
				bfs_mark_outer_space(map, rows, max_cols, start);
			}
			c++;
		}
		r++;
	}
}
