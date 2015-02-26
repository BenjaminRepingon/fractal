/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/25 16:31:52 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/26 15:39:34 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JULIA3D_H
# define JULIA3D_H
# include "object.h"

# define JULIA3D	t_julia3d

typedef struct	s_julia3d
{
	OBJECT		*object;
	VERT		vertex;
	float		min_x;
	float		max_x;
	float		min_y;
	float		max_y;
	float		zoom;
	float		rot;
	float		x;
	float		y;
	int			c;
	int			cc;
	float		z;
	float		zc;
	int			mode;
	int			c_max;
	VEC2		old_pos;
	BOOL		changed;
}				t_julia3d;

JULIA3D			*new_julia3d(float minx, float maxx, float miny, float maxy);
int				render_julia3d(CORE_ENGINE *core, JULIA3D *j);

#endif
