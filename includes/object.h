/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 13:11:02 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/26 15:36:40 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H
# include "core_engine.h"

# define OBJECT			t_object

typedef struct		s_object
{
	void			*o_ptr;
	int				(*update)(void *o, CORE_ENGINE *c, double dt);
	int				(*render)(void *o, CORE_ENGINE *c, double dt);
}					t_object;

OBJECT				*new_object(void *o_ptr, \
	int (*update)(void *o, CORE_ENGINE *c, double dt), \
	int (*render)(void *o, CORE_ENGINE *c, double dt));

#endif
