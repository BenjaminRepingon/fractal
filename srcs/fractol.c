/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 10:31:25 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/27 17:01:49 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static OBJECT	*load_fractal(char *fractal)
{
	if (ft_strcmp(fractal, "mandelbrot") == 0)
		return (new_mandelbrot(-2.4f, 2.4f, -1.5f, 1.5f)->object);
	if (ft_strcmp(fractal, "julia") == 0)
		return (new_julia(-2.4f, 2.4f, -1.5f, 1.5f)->object);
	if (ft_strcmp(fractal, "burning_ship") == 0)
		return (new_burning_ship(-2.4f, 2.4f, -1.5f, 1.5f)->object);
	if (ft_strcmp(fractal, "julia3d") == 0)
		return (new_julia3d(-2.4f, 2.4f, -1.5f, 1.5f)->object);
	return (NULL);
}

static void		usage(void)
{
	ft_putendl("usage: ./fractol <fractal>");
	ft_putendl("Fractal:");
	ft_putendl("- mandelbrot");
	ft_putendl("- julia");
	ft_putendl("- burning_ship");
	ft_putendl("- julia3d");
}

int				main(int argc, char const *argv[])
{
	CORE_ENGINE		*core;
	OBJECT			*object;

	if (argc != 2)
	{
		usage();
		return (0);
	}
	else
	{
		if ((object = load_fractal((char *)argv[1])) == NULL)
		{
			usage();
			return (-1);
		}
		core = new_core_engine(30);
		add_object(core, object);
		create_window(core, 850, 550, "Fractol");
	}
	return (0);
}
