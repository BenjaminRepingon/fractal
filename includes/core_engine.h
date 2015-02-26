/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_engine.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 12:26:14 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/26 15:35:46 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_ENGINE_H
# define CORE_ENGINE_H
# include <sys/time.h>
# include "window.h"
# include "core_engine_struct.h"
# include "object.h"

struct s_object;

/*
**	core_engine.c
*/
CORE_ENGINE			*new_core_engine(int fps);
void				create_window(CORE_ENGINE *c, int w, int h, char *title);
void				add_object(CORE_ENGINE *c, struct s_object *o);

/*
**	core_engine_loop.c
*/
int					loop_hook(CORE_ENGINE *c);

/*
**	core_engine_hooks.c
*/
int					key_press(int keycode, CORE_ENGINE *c);
int					key_release(int keycode, CORE_ENGINE *c);
int					motion_notify(int x, int y, CORE_ENGINE *c);
int					button_press(int button, int x, int y, CORE_ENGINE *c);
int					button_release(int button, int x, int y, CORE_ENGINE *c);

#endif
