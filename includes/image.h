/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 14:52:31 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/18 10:48:25 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H
# include <mlx.h>
# include <libft.h>

# define IMAGE		t_img

typedef struct		s_img
{
	void			*img;
	char			*data;
	int				endian;
	int				sizeline;
	int				bpp;
}					t_img;

IMAGE				*new_image(void *mlx, int width, int height);

#endif
