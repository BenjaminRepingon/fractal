/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 14:52:10 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/26 15:28:40 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

IMAGE	*new_image(void *mlx, int width, int height)
{
	IMAGE	*i;

	if ((i = (IMAGE *)ft_memalloc(sizeof(IMAGE))) == NULL)
		return (NULL);
	if ((i->img = mlx_new_image(mlx, width, height)) == NULL)
	{
		error("mlx new image error: \n");
		return (NULL);
	}
	i->data = mlx_get_data_addr(i->img, &i->bpp, &i->sizeline, &i->endian);
	if (i->data == NULL)
	{
		error("mlx get data addr error: \n");
		return (NULL);
	}
	return (i);
}
