/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 13:10:54 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/26 15:30:13 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

OBJECT				*new_object(void *o_ptr, \
	int (*update)(void *o, CORE_ENGINE *c, double dt), \
	int (*render)(void *o, CORE_ENGINE *c, double dt))
{
	OBJECT	*o;

	if ((o = (OBJECT *)ft_memalloc(sizeof(OBJECT))) == NULL)
		return (NULL);
	o->o_ptr = o_ptr;
	o->update = update;
	o->render = render;
	return (o);
}
