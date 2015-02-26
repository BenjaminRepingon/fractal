/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia3d_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 15:06:48 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/26 15:52:45 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "julia3d.h"
#include "utils.h"

static int	render_depth_julia3d(JULIA3D *j, QUAT *qz, QUAT *qc)
{
	float	r;
	float	tr;

	j->c = 0;
	r = qz->x + qz->x + qz->y * qz->y + qz->z * qz->z + qz->w * qz->w;
	while (r < 16 && j->c < j->c_max)
	{
		tr = qz->x;
		qz->x = qz->x * qz->x - qz->y * qz->y - qz->z * qz->z - qz->w * qz->w;
		qz->x -= qc->x;
		qz->y = 2 * tr * qz->y - qc->y;
		qz->z = 2 * tr * qz->z - qc->y;
		qz->w = 2 * tr * qz->w - qc->w;
		j->c++;
		r = qz->x + qz->x + qz->y * qz->y + qz->z * qz->z + qz->w * qz->w;
	}
	if (j->c > j->cc)
	{
		j->cc = j->c;
		j->zc = j->z;
	}
	j->z -= 0.04;
	return (TRUE);
}

static int	render_color_julia3d(CORE_ENGINE *core, JULIA3D *j)
{
	if (j->cc == j->c_max)
	{
		if (j->zc < 0)
			j->vertex.color = color3((j->zc + 1) * 200, 0, 0);
		else if (j->zc <= 1)
			j->vertex.color = color3(200 + (j->zc) * 50, j->zc * 200, 0);
		else
			j->vertex.color = color3(255, 255, (j->zc - 1) * 255);
	}
	else
		j->vertex.color = color3(0, 0, 0);
	put_vertex(core->window, &j->vertex);
	return (TRUE);
}

int			render_julia3d(CORE_ENGINE *core, JULIA3D *j)
{
	QUAT	qz;
	QUAT	qc;

	j->x = j->vertex.pos.x / j->zoom;
	j->y = j->vertex.pos.y / j->zoom;
	j->x = j->min_x + (j->max_x - j->min_x) / core->window->width * j->x;
	j->y = j->min_y + (j->max_y - j->min_y) / core->window->height * j->y;
	qc.x = j->old_pos.x / core->window->width;
	qc.y = j->old_pos.y / core->window->height;
	qc.z = -0.113;
	qc.w = -0.05;
	j->cc = 0;
	j->z = 1.6;
	while (j->z >= -1.6)
	{
		qz.x = j->x * cos(j->rot) + j->z * sin(j->rot);
		qz.y = -j->x * sin(j->rot) + j->z * cos(j->rot);
		qz.z = j->y;
		qz.w = 0;
		render_depth_julia3d(j, &qz, &qc);
	}
	render_color_julia3d(core, j);
	return (TRUE);
}
