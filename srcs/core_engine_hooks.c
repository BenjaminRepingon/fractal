/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_engine_hooks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 11:32:36 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/27 13:22:39 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_engine.h"
# include <stdio.h>
int		key_press(int keycode, CORE_ENGINE *c)
{
	printf("%d\n", keycode);
	c->key[keycode] = TRUE;
	return (TRUE);
}

int		key_release(int keycode, CORE_ENGINE *c)
{
	c->key[keycode] = FALSE;
	return (TRUE);
}

int		motion_notify(int x, int y, CORE_ENGINE *c)
{
	c->mouse.x = x;
	c->mouse.y = y;
	return (TRUE);
}

int		button_press(int button, int x, int y, CORE_ENGINE *c)
{
	c->button_press[button] = TRUE;
	c->mouse.x = x;
	c->mouse.y = y;
	return (TRUE);
}

int		button_release(int button, int x, int y, CORE_ENGINE *c)
{
	c->button_release[button] = TRUE;
	c->mouse.x = x;
	c->mouse.y = y;
	return (TRUE);
}
