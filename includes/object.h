/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 13:11:02 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/19 14:28:18 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H
# include "core_engine.h"

# define OBJECT			t_object
# define UPDATE_FUNC	(*update)(void *o, CORE_ENGINE *c, double dt)
# define RENDER_FUNC	(*render)(void *o, CORE_ENGINE *c, double dt)

typedef struct		s_object
{
	void			*o_ptr;
	int				UPDATE_FUNC;
	int				RENDER_FUNC;
}					t_object;

OBJECT				*new_object(void *o, int UPDATE_FUNC, int RENDER_FUNC);

#endif
