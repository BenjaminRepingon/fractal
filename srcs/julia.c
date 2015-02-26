/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 15:25:35 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/26 14:36:49 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelbrot.h"
#include "utils.h"

static int	update2(MANDELBROT *m, CORE_ENGINE *c, double dt)
{
	(void)dt;
	if (c->key[109])
		m->mode = !m->mode;
	if (c->key[119])
	{
		m->min_y += (1 / m->zoom) / 5.0;
		m->max_y += (1 / m->zoom) / 5.0;
	}
	if (c->key[97])
	{
		m->min_x -= (1 / m->zoom) / 5.0;
		m->max_x -= (1 / m->zoom) / 5.0;
	}
	if (c->key[115])
	{
		m->min_y -= (1 / m->zoom) / 5.0;
		m->max_y -= (1 / m->zoom) / 5.0;
	}
	if (c->key[100])
	{
		m->min_x += (1 / m->zoom) / 5.0;
		m->max_x += (1 / m->zoom) / 5.0;
	}
	return (TRUE);
}

static int	update(void *o, CORE_ENGINE *c, double dt)
{
	MANDELBROT	*m;
	BOOL		zoom;
	VEC2		delta;

	m = (MANDELBROT *)o;
	update2(m, c, dt);
	zoom = FALSE;
	delta.x = ((c->window->width / 2) - c->mouse.x) / (c->window->width / 2);
	delta.x -= 0.1;
	delta.y = (c->mouse.y - (c->window->height / 2)) / (c->window->height / 2);
	if (m->mode == 0 && (c->button_press[5] || c->key[65362]) && (zoom = TRUE))
		m->zoom *= 1.05f;
	if (m->mode == 0 && (c->button_press[4] || c->key[65364]) && (zoom = TRUE))
		m->zoom *= 0.9525f;
	if (m->mode == 1)
		m->old_pos = c->mouse;
	if (zoom)
	{
		m->min_x = m->min_x - (delta.x / m->zoom);
		m->max_x = m->max_x - (delta.x / m->zoom);
		m->min_y = m->min_y - (delta.y / m->zoom);
		m->max_y = m->max_y - (delta.y / m->zoom);
	}
	return (TRUE);
}

static int	render_julia(CORE_ENGINE *c, MANDELBROT *m)
{
	float		it;
	double		r;
	double		i;
	double		tmp;

	m->rc = (double)m->old_pos.x / (double)c->window->width;
	m->ic = (double)m->old_pos.y / (double)c->window->height;
	m->rz = m->min_x + m->rz / c->window->width * (m->vertex.pos.x / m->zoom);
	m->iz = m->min_y + m->iz / c->window->height * (m->vertex.pos.y / m->zoom);
	it = 0;
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
	m->vertex.color = (it == 100) ? color3(0, 0, 0) : color3f(sin(it / 7.0), \
		sin(it / 5.0), sin(it / 4.0));
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
			m->rz = m->max_x - m->min_x;
			m->iz = m->max_y - m->min_y;
			render_julia(c, m);
			m->vertex.pos.y++;
		}
		m->vertex.pos.x++;
	}
	return (TRUE);
}

MANDELBROT	*new_julia(float min_x, float max_x, float min_y, float max_y)
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
	m->zoom = 1;
	m->mode = 1;
	m->old_pos.x = 0;
	m->old_pos.y = 0;
	return (m);
}
