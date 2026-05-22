/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 11:41:23 by yolim             #+#    #+#             */
/*   Updated: 2026/05/21 23:07:26 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    error_exit(char *msg) {
    ft_putstr_fd("Error\n", 2);
    if (msg) {
        ft_putstr_fd(msg, 2);
        ft_putstr_fd("\n", 2);
    }

    // free everything here

    exit(1);
}