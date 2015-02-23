/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 10:53:11 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/23 17:18:32 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelbrot.h"
# include <stdio.h>
static int	update(void *o, CORE_ENGINE *c, double dt)
{
	MANDELBROT	*m;
	BOOL		zoom;
	float		delta_x;
	float		delta_y;

	(void)dt;
	zoom = FALSE;
	delta_x = ((c->window->width / 2) - c->mouse.x) / (c->window->width) / 2;
	delta_y = (c->mouse.y - (c->window->height / 2)) / (c->window->height / 2);
	m = (MANDELBROT *)o;
	if (c->button_press[5] || c->key[65362])
	{
		m->zoom *= 1.05f;
		zoom = TRUE;
	}
	if (c->button_press[4] || c->key[65364])
	{
		m->zoom *= 0.05f;
		zoom = TRUE;
	}
	if (zoom)
	{
		m->min_x = m->min_x - (delta_x / m->zoom);
		m->max_x = m->max_x - (delta_x / m->zoom);
		m->min_y = m->min_y - (delta_y / m->zoom);
		m->max_y = m->max_y - (delta_y / m->zoom);
		m->changed = TRUE;
	}
	return (TRUE);
}

static void		color(VEC3 *v, float lerp)
{
	static int		color_a = 0xFFDD00;
	static int		color_b = 0x00CC88;
	VEC3			a;
	VEC3			b;

	a.x = color_a & 0xFF0000;
	a.y = color_a & 0x00FF00;
	a.z = color_a & 0x0000FF;
	b.x = color_b & 0xFF0000;
	b.y = color_b & 0x00FF00;
	b.z = color_b & 0x0000FF;
	v->x = ((int)(a.x + ((b.x - a.x) * lerp)) & 0xFF0000) >> 16;
	v->y = ((int)(a.y + ((b.y - a.y) * lerp)) & 0x00FF00) >> 8;
	v->z = ((int)(a.z + ((b.z - a.z) * lerp)) & 0x0000FF);
}

static int	render_mandelbrot(CORE_ENGINE *c, MANDELBROT *m)
{
	int			it;
	double		r;
	double		i;
	double		tmp;

	it = 0;
	m->rc = m->min_x + (m->max_x - m->min_x) / c->window->width * (m->vertex.pos.x / m->zoom);
	m->ic = m->min_y + (m->max_y - m->min_y) / c->window->height * (m->vertex.pos.y / m->zoom);
	m->rz = 0;
	m->iz = 0;
	r = 0;

	//TODO: fixed point
	while (it < 100)
	{
		r = m->rz;
		i = m->iz;
		m->rz = r * r - i * i + m->rc;
		tmp = r * i;
		m->iz = tmp + tmp + m->ic;
		if (m->rz * m->rz + m->iz * m->iz >= 4)
			break ;
		it++;
	}
	color(&(m->vertex.color), (float)it / 100.0f);
	put_vertex(c->window, &m->vertex);
	return (TRUE);
}

static int	render(void *o, CORE_ENGINE *c, double dt)
{
	MANDELBROT	*m;

	(void)dt;
	m = (MANDELBROT *)o;
	m->vertex.pos.x = 0;
	if (!m->changed)
		return (TRUE);
	while (m->vertex.pos.x < c->window->width)
	{
		m->vertex.pos.y = 0;
		while (m->vertex.pos.y < c->window->height)
		{
			m->vertex.pos.z = 0;
			m->vertex.color.x = 0;
			m->vertex.color.y = 0;
			m->vertex.color.z = 0;
			render_mandelbrot(c, m);
			m->vertex.pos.y++;
		}
		m->vertex.pos.x++;
	}
	m->changed = FALSE;
	return (TRUE);
}

MANDELBROT	*new_mandelbrot(float min_x, float max_x, float min_y, float max_y)
{
	MANDELBROT	*m;

	if ((m = (MANDELBROT *)ft_memalloc(sizeof(MANDELBROT))) == NULL)
		return (NULL);
	m->object = new_object(m, &update, &render);
	m->min_x = min_x;
	m->max_x = max_x;
	m->min_y = min_y;
	m->max_y = max_y;
	m->changed = TRUE;
	m->level = 0;
	m->zoom = 1;
	return (m);
}
