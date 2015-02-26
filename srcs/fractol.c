/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 10:31:25 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/26 18:41:37 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		main(int argc, char const *argv[])
{
	CORE_ENGINE		*core;
	// JULIA3D			*j;
	MANDELBROT		*m;
	(void)argc;
	(void)argv;

	core = new_core_engine(30);

	// j = new_julia3d(-2.4f, 2.4f, -1.5f, 1.5f);
	m = new_mandelbrot(-2.4f, 2.4f, -1.5f, 1.5f);
	// m = new_julia(-2.4f, 2.4f, -1.5f, 1.5f);
	// m = new_burning_ship(-2.4f, 2.4f, -1.5f, 1.5f);
	add_object(core, m->object);
	// add_object(core, j->object);

	create_window(core, 850*2, 550*2, "Fractol");
	return (0);
}
