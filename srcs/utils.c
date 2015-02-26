/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 12:35:46 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/26 12:37:34 by rbenjami         ###   ########.fr       */
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
