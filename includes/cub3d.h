/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:35:22 by yolim             #+#    #+#             */
/*   Updated: 2026/05/20 13:44:20 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <fcntl.h>  // for open
#include <unistd.h> // for close, read, write
#include <stdio.h>  // for printf, perror
#include <stdlib.h> // for malloc, free, exit
#include <string.h> // for strerror
#include <sys/time.h>   // for gettimeofday
#include <math.h>   // for all functions of the math library
#include "../Libft/libft.h"


// pending for minilibx header file!


typedef struct s_texture {
    void    *img;   // ← this is ONE WALL TEXTURE image
    char    *addr;  // ← pixel memory of THAT TEXTURE
    int     bpp;    // ← texture's bits per pixel
    int     line_len;   // ← texture's line length
    int     endian; // ← texture's endian
    int     width;
    int     height;
}               t_texture;

typedef struct s_player {
    double  pos_x;
    double  pos_y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
}               t_player;

typedef struct s_game {
    void        *mlx;   // ← this is the SCREEN buffer
    void        *win;
    void        *img;
    char        *addr;  // ← pixel memory of the SCREEN
    int         bpp;    // ← screen's bits per pixel
    int         line_len;   // ← screen's line length
    int         endian; // ← screen's endian

    char        **map;  // not 2D array bcos compile time dont know the actual map size (map sometime not square), char **map can malloc exactly the right size after read the .cub file
    int         map_rows;
    int         map_cols;

    t_texture   tex[4]; // 0=NO 1=SO 2=WE 3=EA
    int         floor_colour;
    int         ceiling_colour;

    t_player    player;
}               t_game;













#endif
