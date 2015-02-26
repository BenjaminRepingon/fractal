/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_engine_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 11:31:35 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/26 15:28:13 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_engine.h"

static void		update_all(CORE_ENGINE *c, double dt)
{
	OBJECT	*o;
	t_elem	*e;

	if (c->key[65307])
		exit(0);
	e = c->objects->first;
	while (e != NULL)
	{
		o = (OBJECT *)e->data;
		o->update(o->o_ptr, c, dt);
		e = e->next;
	}
}

static void		render_all(CORE_ENGINE *c, double dt)
{
	OBJECT	*o;
	t_elem	*e;

	e = c->objects->first;
	while (e != NULL)
	{
		o = (OBJECT *)e->data;
		o->render(o->o_ptr, c, dt);
		e = e->next;
	}
}

static double	get_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + (double)tv.tv_usec / SECOND);
}

int				loop_hook(CORE_ENGINE *c)
{
	int	sleep;
	int	i;

	c->start_frame = get_time();
	clear_window(c->window);
	update_all(c, c->dt);
	render_all(c, c->dt);
	i = 0;
	while (i < 8)
		c->button_press[i++] = FALSE;
	i = 0;
	while (i < 8)
		c->button_release[i++] = FALSE;
	swap_buffer(c->window);
	c->end_frame = get_time();
	c->dt = (c->end_frame - c->start_frame);
	sleep = (SECOND / c->fps) - (c->dt * SECOND);
	if (sleep > 0)
		usleep(sleep);
	return (TRUE);
}
