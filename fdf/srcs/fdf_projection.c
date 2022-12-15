/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 21:35:57 by wxuerui           #+#    #+#             */
/*   Updated: 2022/10/16 14:21:13 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Project a 2D object into 3D with a 30 degree oblique */
static void	isometric_projection(t_point *p)
{
	int	x;
	int	y;

	x = p->x;
	y = p->y;
	p->x = (x - y) * cos(M_PI / 6);
	p->y = (x + y) * sin(M_PI / 6) - p->z;
}

/* Make a new point */
t_point	new_point(int x, int y, t_fdf *fdf)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = fdf->map->coords[y * fdf->map->width + x];
	point.color = get_point_color(point, fdf->map, fdf->view);
	return (point);
}

/* Show(project) the map according to its current state.
 * E.g. the rotate angles, visual mode
 */
t_point	project(t_point p, t_fdf *fdf)
{
	p.x *= fdf->view->zoom;
	p.y *= fdf->view->zoom;
	p.z *= fdf->view->zoom / 2;
	p.x -= (fdf->map->width * fdf->view->zoom) / 2;
	p.y -= (fdf->map->height * fdf->view->zoom) / 2;
	if (fdf->view->mode == THREE_D)
	{
		rotate_x(&p.y, &p.z, fdf->view->angle_x);
		rotate_y(&p.x, &p.z, fdf->view->angle_y);
		rotate_z(&p.x, &p.y, fdf->view->angle_z);
		isometric_projection(&p);
	}
	p.x += (WIDTH - MENU_SIZE) / 2;
	p.y += (HEIGHT + fdf->map->height * fdf->view->zoom) / 2;
	p.x += fdf->view->move_x;
	p.y += fdf->view->move_y;
	return (p);
}
