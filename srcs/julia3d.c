/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/25 15:17:31 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/26 15:47:52 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "julia3d.h"

static int	update2(JULIA3D *j, CORE_ENGINE *c, BOOL zoom, VEC2 delta)
{
	if (c->key[97] && (j->changed = TRUE))
		j->rot += 0.30;
	if (c->key[100] && (j->changed = TRUE))
		j->rot -= 0.30;
	if (zoom)
	{
		j->min_x = j->min_x - (delta.x / j->zoom);
		j->max_x = j->max_x - (delta.x / j->zoom);
		j->min_y = j->min_y - (delta.y / j->zoom);
		j->max_y = j->max_y - (delta.y / j->zoom);
		j->changed = TRUE;
	}
	if (j->mode == 1 && \
		(j->old_pos.x != c->mouse.x || j->old_pos.y != c->mouse.y))
	{
		j->old_pos = c->mouse;
		j->changed = TRUE;
	}
	return (TRUE);
}

static int	update(void *o, CORE_ENGINE *c, double dt)
{
	JULIA3D		*j;
	BOOL		zoom;
	VEC2		delta;

	(void)dt;
	j = (JULIA3D *)o;
	zoom = FALSE;
	delta.x = ((c->window->width / 2) - c->mouse.x) / (c->window->width / 2);
	delta.x -= 0.1;
	delta.y = (c->mouse.y - (c->window->height / 2)) / (c->window->height / 2);
	if (c->key[109])
	{
		j->mode = !j->mode;
		ft_putstr("Mode: ");
		ft_putnbr_base(j->mode, 2);
		ft_putchar('\n');
	}
	if (j->mode == 0 && (c->button_press[5] || c->key[65362]) && (zoom = TRUE))
		j->zoom *= 1.05f;
	if (j->mode == 0 && (c->button_press[4] || c->key[65364]) && (zoom = TRUE))
		j->zoom *= 0.95f;
	update2(j, c, zoom, delta);
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

JULIA3D		*new_julia3d(float min_x, float max_x, float min_y, float max_y)
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
