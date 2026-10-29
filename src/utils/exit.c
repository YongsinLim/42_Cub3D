/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@studekl.edu.my>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 11:41:23 by yolim             #+#    #+#             */
/*   Updated: 2026/07/22 17:12:52 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	error_exit(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(1);
}

int	close_window(t_game *game)
{
	return (close_game(game));
}
