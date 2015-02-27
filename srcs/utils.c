/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 12:35:46 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/27 17:57:35 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

VEC3	color3f(float r, float g, float b)
{
	VEC3	c;

	c.x = r * 255.0;
	c.y = g * 255.0;
	c.z = b * 255.0;
	return (c);
}

VEC3	color3(int r, int g, int b)
{
	VEC3	c;

	c.x = r;
	c.y = g;
	c.z = b;
	return (c);
}

void	check_num(CORE_ENGINE *c, MANDELBROT *m)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		if (c->key[65457 + i] && (m->changed = TRUE))
			m->anti_alias = i + 1;
		i++;
	}
}
