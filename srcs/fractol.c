/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 10:31:25 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/25 17:49:12 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		main(int argc, char const *argv[])
{
	CORE_ENGINE		*core;
	JULIA3D	*j;
	(void)argc;
	(void)argv;

	core = new_core_engine(30);

	j = new_julia3d(-2.4f, 2.4f, -1.5f, 1.5f);
	// m = new_julia(-2.4f, 2.4f, -1.5f, 1.5f);
	add_object(core, j->object);

	create_window(core, 850, 550, "Fractol");
	return (0);
}
