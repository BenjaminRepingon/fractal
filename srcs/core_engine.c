/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 12:26:02 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/23 17:23:23 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include </usr/X11/include/X11/X.h>
#include "core_engine.h"

# include <stdio.h>

static double	get_time(void);

CORE_ENGINE		*new_core_engine(int fps)
{
	CORE_ENGINE	*c;

	if ((c = (CORE_ENGINE *)ft_memalloc(sizeof(CORE_ENGINE))) == NULL)
		return (NULL);
	c->window = NULL;
	c->objects = new_list();
	c->fps = fps;
	c->start_frame = get_time();
	c->dt = 1.0 / c->fps;
	return (c);
}

static void		update(CORE_ENGINE *c, double dt)
{
	OBJECT	*o;
	t_elem	*e;

	if (c->key[65307])
		exit(0);
	e = c->objects->first;
	while(e != NULL)
	{
		o = (OBJECT *)e->data;
		o->update(o->o_ptr, c, dt);
		e = e->next;
	}
}

static void		render(CORE_ENGINE *c, double dt)
{
	OBJECT	*o;
	t_elem	*e;

	e = c->objects->first;
	while(e != NULL)
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

static int		loop_hook(CORE_ENGINE *c)
{
	int	sleep;
	int	i;

	c->start_frame = get_time();
	clear_window(c->window);
	update( c, c->dt );
	render( c, c->dt );
	i = 0;
	while(i < 8)
		c->button_press[i++] = FALSE;
	i = 0;
	while(i < 8)
		c->button_release[i++] = FALSE;
	swap_buffer(c->window);
	c->end_frame = get_time();
	c->dt = (c->end_frame - c->start_frame);
	sleep = (SECOND / c->fps) - (c->dt * SECOND);
	if (sleep > 0)
		usleep(sleep);
	// printf("FPS: %f\n", 1.0 / (get_time() - c->start_frame));
	return (TRUE);
}

static int		expose_hook(CORE_ENGINE *c)
{
	c->window->have_changed = TRUE;
	return (TRUE);
}

static int		key_press(int keycode, CORE_ENGINE *c)
{
	c->key[keycode] = TRUE;
	return (TRUE);
}

static int		key_release(int keycode, CORE_ENGINE *c)
{
	c->key[keycode] = FALSE;
	return (TRUE);
}

static int		motion_notify(int x, int y, CORE_ENGINE *c)
{
	c->mouse.x = x;
	c->mouse.y = y;
	return (TRUE);
}

static int		button_press(int button, int x, int y, CORE_ENGINE *c)
{
	c->button_press[button] = TRUE;
	c->mouse.x = x;
	c->mouse.y = y;
	return (TRUE);
}

static int		button_release(int button, int x, int y, CORE_ENGINE *c)
{
	c->button_release[button] = TRUE;
	c->mouse.x = x;
	c->mouse.y = y;
	return (TRUE);
}

void			add_object(CORE_ENGINE *c, struct s_object *o)
{
	add_elem(c->objects, o);
}

void			create_window(CORE_ENGINE *c, int w, int h, char *title)
{
	c->window = new_window(w, h, title);
	mlx_do_key_autorepeaton(c->window->mlx);
	mlx_loop_hook(c->window->mlx, &loop_hook, c);
	mlx_expose_hook(c->window->win, &expose_hook, c);
	mlx_hook(c->window->win, KeyPress, KeyPressMask, &key_press, c);
	mlx_hook(c->window->win, KeyRelease, KeyReleaseMask, &key_release, c);
	mlx_hook(c->window->win, MotionNotify, PointerMotionMask, &motion_notify, c);
	mlx_hook(c->window->win, ButtonPress, ButtonPressMask, &button_press, c);
	mlx_hook(c->window->win, ButtonRelease, ButtonReleaseMask, &button_release, c);
	mlx_loop(c->window->mlx);
}
