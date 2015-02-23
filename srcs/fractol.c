/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 10:31:25 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/23 16:53:57 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		main(int argc, char const *argv[])
{
	CORE_ENGINE		*core;
	MANDELBROT		*m;
	(void)argc;
	(void)argv;

	core = new_core_engine(30);

	m = new_mandelbrot(-2.4f, 2.4f, -1.5f, 1.5f);
	add_object(core, m->object);

	create_window(core, 850, 550, "Fractol");
	return (0);
}
