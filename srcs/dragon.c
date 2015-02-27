/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/27 10:35:55 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/27 14:06:18 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelbrot.h"
#include "utils.h"

static int	update(void *o, CORE_ENGINE *c, double dt)
{
	MANDELBROT	*m;
	BOOL		zoom;
	VEC2		delta;

	(void)dt;
	zoom = FALSE;
	delta.x = ((c->window->width / 2) - c->mouse.x) / (c->window->width / 2);
	delta.x -= 0.1;
	delta.y = (c->mouse.y - (c->window->height / 2)) / (c->window->height / 2);
	m = (MANDELBROT *)o;
	if ((c->button_press[5] || c->key[65362]) && (zoom = TRUE))
		m->zoom *= 1.05f;
	if ((c->button_press[4] || c->key[65364]) && (zoom = TRUE))
		m->zoom *= 0.9525f;
	if (zoom)
	{
		m->min_x = m->min_x - (delta.x / m->zoom);
		m->max_x = m->max_x - (delta.x / m->zoom);
		m->min_y = m->min_y - (delta.y / m->zoom);
		m->max_y = m->max_y - (delta.y / m->zoom);
		m->changed = TRUE;
	}
	return (TRUE);
}

static int	render_dragon(CORE_ENGINE *c, MANDELBROT *m)
{
	int			it;
	double		r;
	double		i;
	double		tmp;

	m->rc = m->min_x + m->rc / c->window->width * (m->vertex.pos.x / m->zoom);
	m->ic = m->min_y + m->ic / c->window->height * (m->vertex.pos.y / m->zoom);
	m->rz = 0;
	m->iz = 0;
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
			m->rc = m->max_x - m->min_x;
			m->ic = m->max_y - m->min_y;
			render_dragon(c, m);
			m->vertex.pos.y++;
		}
		m->vertex.pos.x++;
	}
	m->changed = FALSE;
	return (TRUE);
}

MANDELBROT	*new_dragon(float min_x, float max_x, float min_y, float max_y)
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
	return (m);
}
