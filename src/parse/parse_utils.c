/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:37:44 by yolim             #+#    #+#             */
/*   Updated: 2026/05/21 15:03:09 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// check last 4 chars of filename are ".cub"
void    check_file_extension(char *path) {
    int len;

    len = ft_strlen(path);
    if (len < 5 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
        error_exit("File must have .cub extension");
}

