/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 10:53:23 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/27 13:21:06 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDELBROT_H
# define MANDELBROT_H
# include "object.h"

# define MANDELBROT	t_mandelbrot

typedef struct	s_mandelbrot
{
	OBJECT		*object;
	VERT		vertex;
	double		min_x;
	double		max_x;
	double		min_y;
	double		max_y;
	double		rc;
	double		ic;
	double		rz;
	double		iz;
	double		zoom;
	int			mode;
	int			anti_alias;
	VEC2		old_pos;
	BOOL		changed;
}				t_mandelbrot;

MANDELBROT		*new_mandelbrot(float minx, float maxx, float miny, float maxy);
MANDELBROT		*new_julia(float min_x, float max_x, float min_y, float max_y);
MANDELBROT		*new_burning_ship(float inx, float axx, float iny, float axy);
MANDELBROT		*new_dragon(float min_x, float max_x, float min_y, float max_y);

#endif
