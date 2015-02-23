/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 13:10:54 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/19 14:32:38 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

OBJECT				*new_object(void *o_ptr, int UPDATE_FUNC, int RENDER_FUNC)
{
	OBJECT	*o;

	if ((o = (OBJECT *)ft_memalloc(sizeof(OBJECT))) == NULL)
		return (NULL);
	o->o_ptr = o_ptr;
	o->update = update;
	o->render = render;
	return (o);
}
