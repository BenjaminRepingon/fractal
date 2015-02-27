/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 12:36:41 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/27 17:57:47 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <libft.h>
# include "mandelbrot.h"

VEC3	color3f(float r, float g, float b);
VEC3	color3(int r, int g, int b);
void	check_num(CORE_ENGINE *c, MANDELBROT *m);

#endif
