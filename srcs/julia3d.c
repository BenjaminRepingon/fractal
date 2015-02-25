/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/25 15:17:31 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/25 17:54:29 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "julia3d.h"
#include <stdio.h>

static int	update(void *o, CORE_ENGINE *c, double dt)
{
	JULIA3D	*j;
	BOOL		zoom;
	float		delta_x;
	float		delta_y;

	(void)dt;
	(void)c;
	j = (JULIA3D *)o;
	zoom = FALSE;
	delta_x = ((c->window->width / 2) - c->mouse.x) / (c->window->width) / 2;
	delta_y = (c->mouse.y - (c->window->height / 2)) / (c->window->height / 2);
	if (c->key[109])
	{
		j->mode = !j->mode;
		printf("MODE: %d\n", j->mode);
	}
	if (j->mode == 0 && (c->button_press[5] || c->key[65362]))
	{
		j->zoom *= 1.05f;
		zoom = TRUE;
	}
	if (j->mode == 0 && (c->button_press[4] || c->key[65364]))
	{
		j->zoom *= 0.95f;
		zoom = TRUE;
	}
	if (c->key[97])
	{
		j->changed = TRUE;
		j->rot += 0.30;
	}
	if (c->key[100])
	{
		j->changed = TRUE;
		j->rot -= 0.30;
	}
	if (zoom)
	{
		j->min_x = j->min_x - (delta_x / j->zoom);
		j->max_x = j->max_x - (delta_x / j->zoom);
		j->min_y = j->min_y - (delta_y / j->zoom);
		j->max_y = j->max_y - (delta_y / j->zoom);
		j->changed = TRUE;
	}
	if (j->mode == 1 && (j->old_pos.x != c->mouse.x || j->old_pos.y != c->mouse.y))
	{
		j->changed = TRUE;
		j->old_pos.x = c->mouse.x;
		j->old_pos.y = c->mouse.y;
	}
	return (TRUE);
}

static VEC3	color3(int r, int g, int b)
{
	VEC3	c;

	c.x = r;
	c.y = g;
	c.z = b;
	return (c);
}

static int	render_julia3d(CORE_ENGINE *core, JULIA3D *j)
{
	int		c;
	int		cc;
	float	z;
	float	zc;
	float	r;
	float	x;
	float	y;
	QUAT	qz;
	QUAT	qc;
	float	tr;

	x = j->min_x + (j->max_x - j->min_x) / core->window->width * (j->vertex.pos.x / j->zoom);
	y = j->min_y + (j->max_y - j->min_y) / core->window->height * (j->vertex.pos.y / j->zoom);
	qc.x = j->old_pos.x / core->window->width;
	qc.y = j->old_pos.y / core->window->height;
	qc.z = -0.6113;
	qc.w = -0.05;
	cc = 0;
	z = 1.6;
	while (z >= -1.6)
	{
		qz.x = x * cos(j->rot) + z * sin(j->rot);
		qz.y = -x * sin(j->rot) + z * cos(j->rot);
		qz.z = y;
		qz.w = 0;
		c = 0;
		r = qz.x + qz.x + qz.y * qz.y + qz.z * qz.z + qz.w * qz.w;
		while (r < 16 && c < j->c_max)
		{
			tr = qz.x;
			qz.x = qz.x * qz.x - qz.y * qz.y - qz.z * qz.z - qz.w * qz.w - qc.x;
			qz.y = 2 * tr * qz.y - qc.y;
			qz.z = 2 * tr * qz.z - qc.y;
			qz.w = 2 * tr * qz.w - qc.w;
			c++;
			r = qz.x + qz.x + qz.y * qz.y + qz.z * qz.z + qz.w * qz.w;
		}
		if (c > cc)
		{
			cc = c;
			zc = z;
		}
		z -= 0.04;
	}
	if (cc == j->c_max)
	{
		if (zc < 0)
			j->vertex.color = color3((zc + 1) * 200, 0, 0);
		else if (zc <= 1)
			j->vertex.color = color3(200 + (zc) * 50, zc * 200, 0);
		else
			j->vertex.color = color3(255, 255, (zc - 1) * 400);
	}
	else
		j->vertex.color = color3(0, 0, 0);
	put_vertex(core->window, &j->vertex);
	return (TRUE);
}

static int	render(void *o, CORE_ENGINE *c, double dt)
{
	JULIA3D	*j;

	(void)dt;
	j = (JULIA3D *)o;
	j->vertex.pos.x = 0;
	if (!j->changed)
		return (TRUE);
	while (j->vertex.pos.x < c->window->width)
	{
		j->vertex.pos.y = 0;
		while (j->vertex.pos.y < c->window->height)
		{
			j->vertex.pos.z = 0;
			j->vertex.color.x = 0;
			j->vertex.color.y = 0;
			j->vertex.color.z = 0;
			render_julia3d(c, j);
			j->vertex.pos.y++;
		}
		j->vertex.pos.x++;
	}
	j->changed = FALSE;
	return (TRUE);
}

JULIA3D	*new_julia3d(float min_x, float max_x, float min_y, float max_y)
{
	JULIA3D	*j;

	if ((j = (JULIA3D *)ft_memalloc(sizeof(JULIA3D))) == NULL)
		return (NULL);
	j->object = new_object(j, &update, &render);
	j->min_x = min_x;
	j->max_x = max_x;
	j->min_y = min_y;
	j->max_y = max_y;
	j->changed = TRUE;
	j->zoom = 1;
	j->rot = 0;
	j->mode = 1;
	j->old_pos.x = 0;
	j->old_pos.y = 0;
	j->c_max = 10;
	return (j);
}
