/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 11:49:40 by yolim             #+#    #+#             */
/*   Updated: 2026/06/18 12:34:30 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_queue	*create_queue(int capacity)
{
	t_queue	*q;

	q = malloc(sizeof(t_queue));
	if (!q)
		error_exit("Malloc failed");
	q->cells = malloc(sizeof(t_point) * capacity);
	if (!q->cells)
		error_exit("Malloc failed");
	q->head_idx = 0;
	q->tail_idx = 0;
	q->capacity = capacity;
	return (q);
}

/*
before:  [ (1,1) | (0,1) | _empty_ ]
                              ↑ tail
  after:   [ (1,1) | (0,1) | (2,1) ]
                                      ↑ tail
 */
void	enqueue(t_queue *q, int r, int c)
{
	q->cells[q->tail_idx].r = r;
	q->cells[q->tail_idx].c = c;
	q->tail_idx++;
}

/* return cell at head, then move head forward
before:  [ (1,1) | (0,1) | (2,1) ]
↑ head
after:   [ (1,1) | (0,1) | (2,1) ]
↑ head
returned: (1,1)
*/
t_point	dequeue(t_queue *q)
{
	return (q->cells[q->head_idx++]);
}

// no cells between head_idx and tail_idx = empty
int	is_empty(t_queue *q)
{
	return (q->head_idx == q->tail_idx);
}
