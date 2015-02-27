/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 15:54:37 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/27 17:50:16 by rbenjami         ###   ########.fr       */
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
	check_num(c, m);
	return (TRUE);
}

static int	render_burningship2(CORE_ENGINE *c, MANDELBROT *m, float x, float y)
{
	double		r;
	double		i;
	int			it;

	m->rc = m->min_x + (m->max_x - m->min_x) / c->window->width * \
	((m->vertex.pos.x + x) / m->zoom);
	m->ic = m->min_y + (m->max_y - m->min_y) / c->window->height * \
	((m->vertex.pos.y + y) / m->zoom);
	m->rz = m->rc;
	m->iz = m->ic;
	r = m->rz * m->rz;
	i = m->iz * m->iz;
	it = 0;
	while (it < 100)
	{
		m->iz = fabs(m->rz * m->iz);
		m->iz = m->iz + m->iz - m->ic;
		m->rz = r - i + m->rc;
		r = m->rz * m->rz;
		i = m->iz * m->iz;
		if (r + i >= 4)
			break ;
		it++;
	}
	return (it);
}

static int	render_burning_ship(CORE_ENGINE *c, MANDELBROT *m)
{
	int			alias_x;
	int			alias_y;
	float		total;

	alias_y = 0;
	total = 0;
	while (alias_y < m->anti_alias)
	{
		alias_x = 0;
		while (alias_x < m->anti_alias)
		{
			total += render_burningship2(c, m, \
				(float)(-(m->anti_alias / 2) + alias_x) / (float)m->anti_alias,\
				(float)(-(m->anti_alias / 2) + alias_y) / (float)m->anti_alias);
			alias_x++;
		}
		alias_y++;
	}
	total /= m->anti_alias * m->anti_alias;
	if (total == 100)
		m->vertex.color = color3(230, 200, 50);
	else
		m->vertex.color = color3f(sin(total / 50), 0, 0);
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
			render_burning_ship(c, m);
			m->vertex.pos.y++;
		}
		m->vertex.pos.x++;
	}
	m->changed = FALSE;
	return (TRUE);
}

MANDELBROT	*new_burning_ship(float minx, float maxx, float miny, float maxy)
{
	MANDELBROT	*m;

	if ((m = (MANDELBROT *)ft_memalloc(sizeof(MANDELBROT))) == NULL)
		return (NULL);
	m->object = new_object(m, &update, &render);
	m->min_x = minx;
	m->max_x = maxx;
	m->min_y = miny;
	m->max_y = maxy;
	m->changed = TRUE;
	m->zoom = 1;
	m->anti_alias = 1;
	return (m);
}
