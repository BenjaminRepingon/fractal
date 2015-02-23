/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 13:41:26 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/23 17:05:18 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

WINDOW			*new_window(int width, int height, char *title)
{
	WINDOW	*w;

	if ((w = (WINDOW *)ft_memalloc(sizeof(WINDOW))) == NULL)
		return (NULL);
	if ((w->mlx = mlx_init()) == NULL)
	{
		error("mlx init error: \n");
		return (NULL);
	}
	if ((w->win = mlx_new_window(w->mlx, width, height, title)) == NULL)
	{
		error("window error: \n");
		return (NULL);
	}
	if ((w->color_buf = new_image(w->mlx, width, height)) == NULL)
	{
		error("bit buffer error: \n");
		return (NULL);
	}
	w->depth_buf = (float *)ft_memalloc(sizeof(float) * width * height);
	w->width = width;
	w->height = height;
	w->title = title;
	return (w);
}

void			swap_buffer(WINDOW *w)
{
	if (w->have_changed)
	{
		mlx_put_image_to_window(w->mlx, w->win, w->color_buf->img, 0, 0);
		w->have_changed = FALSE;
	}
}

void			clear_window(WINDOW *w)
{
	(void)w;
	// mlx_clear_window(w->mlx, w->win);
}

void			put_vertex(WINDOW *w, VERT *v)
{
	int		index;
	char	*tmp;
	int		x;
	int		y;

	x = v->pos.x;
	y = w->height - v->pos.y;
	if (x < 0 || x >= w->width)
		return ;
	if (y < 0 || y >= w->height)
		return ;
	if (v->pos.z >= 0)
	{
		index = (y * w->color_buf->sizeline + x * (w->color_buf->bpp / 8));
		tmp = &w->color_buf->data[index];
		tmp[0] = (char)(v->color.z);
		tmp[1] = (char)(v->color.y);
		tmp[2] = (char)(v->color.x);
	}
	w->depth_buf[y * w->width + x] = v->pos.z;
	w->have_changed = TRUE;
}
