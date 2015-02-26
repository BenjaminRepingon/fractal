/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_engine_struct.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 15:33:42 by rbenjami          #+#    #+#             */
/*   Updated: 2015/02/26 15:37:38 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_ENGINE_STRUCT_H
# define CORE_ENGINE_STRUCT_H

# define CORE_ENGINE	t_core_engine

typedef struct		s_core_engine
{
	WINDOW			*window;
	t_list			*objects;
	int				fps;
	double			start_frame;
	double			end_frame;
	double			dt;
	BOOL			key[70000];
	BOOL			button_press[8];
	BOOL			button_release[8];
	VEC2			mouse;
}					t_core_engine;

#endif
