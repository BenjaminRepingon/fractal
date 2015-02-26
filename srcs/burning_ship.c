/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 15:54:37 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/26 18:17:02 by rbenjami         ###   ########.fr       */
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

static void	color(VEC3 *v, float lerp)
{
	static int		color_a = 0x000000;
	static int		color_b = 0xFF0000;
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
#define MAX_ANTI_ALIAS 5
#define MAX_IT 100
// #  include <stdio.h>
static int	render_burning_ship(CORE_ENGINE *c, MANDELBROT *m)
{
	int			it[MAX_ANTI_ALIAS * MAX_ANTI_ALIAS];
	float		anti_alias;
	double		r;
	double		i;
	int			alias_x;
	int			alias_y;
	int			total;

	alias_y = 0;
	total = 0;
	while (alias_y < MAX_ANTI_ALIAS)
	{
		alias_x = 0;
		while (alias_x < MAX_ANTI_ALIAS)
		{
			anti_alias = (float)(-(MAX_ANTI_ALIAS / 2) + alias_x) / (float)MAX_ANTI_ALIAS;
			m->rc = m->min_x + (m->max_x - m->min_x) / c->window->width * ((m->vertex.pos.x + anti_alias) / m->zoom);
			anti_alias = (float)(-(MAX_ANTI_ALIAS / 2) + alias_y) / (float)MAX_ANTI_ALIAS;
			m->ic = m->min_y + (m->max_y - m->min_y) / c->window->height * ((m->vertex.pos.y + anti_alias) / m->zoom);
			m->rz = m->rc;
			m->iz = m->ic;
			r = m->rz * m->rz;
			i = m->iz * m->iz;
			it[alias_y * MAX_ANTI_ALIAS + alias_x] = 0;
			while (it[alias_y * MAX_ANTI_ALIAS + alias_x] < MAX_IT)
			{
				m->iz = fabs(m->rz * m->iz);
				m->iz = m->iz + m->iz - m->ic;
				m->rz = r - i + m->rc;
				r = m->rz * m->rz;
				i = m->iz * m->iz;
				if (r + i >= 4)
					break ;
				it[alias_y * MAX_ANTI_ALIAS + alias_x]++;
			}
			total += it[alias_y * MAX_ANTI_ALIAS + alias_x];
			alias_x++;
		}
		alias_y++;
	}
	total /= MAX_ANTI_ALIAS * MAX_ANTI_ALIAS;
	if (total == MAX_IT)
		m->vertex.color = color3(230, 200, 50);
	else
		color(&m->vertex.color, (float)total / MAX_IT);
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
			// m->rc = ;
			// m->ic = ;
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
	return (m);
}
