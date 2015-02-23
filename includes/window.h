/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 13:41:38 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/23 17:05:38 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H
# include <mlx.h>
# include <libft.h>
# include "image.h"

# define SECOND		(1000000.0)
# define WINDOW		t_window

typedef struct s_window		t_window;
struct				s_window
{
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	char			*title;
	IMAGE			*color_buf;
	float			*depth_buf;
	BOOL			have_changed;
};

WINDOW				*new_window(int width, int height, char *title);
void				swap_buffer(WINDOW *w);
void				clear_window(WINDOW *w);
void				put_vertex(WINDOW *w, VERT *v);

#endif
