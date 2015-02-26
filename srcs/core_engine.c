/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 12:26:02 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/26 15:27:28 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include </usr/X11/include/X11/X.h>
#include "core_engine.h"

CORE_ENGINE		*new_core_engine(int fps)
{
	CORE_ENGINE	*c;

	if ((c = (CORE_ENGINE *)ft_memalloc(sizeof(CORE_ENGINE))) == NULL)
		return (NULL);
	c->window = NULL;
	c->objects = new_list();
	c->fps = fps;
	c->dt = 1.0 / c->fps;
	return (c);
}

static int		expose_hook(CORE_ENGINE *c)
{
	c->window->have_changed = TRUE;
	return (TRUE);
}

void			add_object(CORE_ENGINE *c, OBJECT *o)
{
	add_elem(c->objects, o);
}

void			create_window(CORE_ENGINE *c, int w, int h, char *title)
{
	void	*win;

	c->window = new_window(w, h, title);
	win = c->window->win;
	mlx_do_key_autorepeaton(c->window->mlx);
	mlx_loop_hook(c->window->mlx, &loop_hook, c);
	mlx_expose_hook(c->window->win, &expose_hook, c);
	mlx_hook(win, KeyPress, KeyPressMask, &key_press, c);
	mlx_hook(win, KeyRelease, KeyReleaseMask, &key_release, c);
	mlx_hook(win, MotionNotify, PointerMotionMask, &motion_notify, c);
	mlx_hook(win, ButtonPress, ButtonPressMask, &button_press, c);
	mlx_hook(win, ButtonRelease, ButtonReleaseMask, &button_release, c);
	mlx_loop(c->window->mlx);
}
