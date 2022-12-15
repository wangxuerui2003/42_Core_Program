/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:45:14 by wxuerui           #+#    #+#             */
/*   Updated: 2022/10/16 14:27:56 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Clean the memory and draw the background colors */
static void	draw_background(t_fdf *fdf)
{
	int	*image;
	int	i;

	ft_bzero(fdf->data_addr, WIDTH * HEIGHT * (fdf->bits_per_pixel / 8));
	image = (int *)(fdf->data_addr);
	i = -1;
	while (++i < HEIGHT * WIDTH)
	{
		if ((i / WIDTH < MENU_SIZE) && (i % WIDTH < MENU_SIZE))
			image[i] = MENU_BACKGROUND;
		else
			image[i] = BACKGROUND;
	}
}

/* Draw a single pixel on the window */
static void	draw_pixel(t_fdf *fdf, int x, int y, int color)
{
	int		i;

	if (x < 0 || y < 0)
		return ;
	if ((x >= MENU_SIZE || y >= MENU_SIZE) && x < WIDTH && y < HEIGHT)
	{
		i = (x * fdf->bits_per_pixel / 8) + (y * fdf->size_line);
		fdf->data_addr[i] = color;
		fdf->data_addr[++i] = color >> 8;
		fdf->data_addr[++i] = color >> 16;
	}
}

/* Formula for drawing a straight line on the window */
static void	adjust_errors(t_point *delta, t_point *temp,
	t_point *direction, int error[2])
{
	error[1] = error[0] * 2;
	if (error[1] > -abs(delta->y))
	{
		error[0] -= abs(delta->y);
		temp->x += direction->x;
	}
	if (error[1] < abs(delta->x))
	{
		error[0] += abs(delta->x);
		temp->y += direction->y;
	}	
}

/* Draw a straight line and change color according to their altitude changes */
static void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	t_point	delta;
	t_point	direction;
	t_point	temp;
	int		error[2];

	temp = p1;
	delta.x = p1.x - p2.x;
	delta.y = p1.y - p2.y;
	direction.x = -1 + (2 * (delta.x < 0));
	direction.y = -1 + (2 * (delta.y < 0));
	error[0] = abs(delta.x) - abs(delta.y);
	while ((p1.x > 0 && p2.x > 0) && (temp.x != p2.x || temp.y != p2.y))
	{
		draw_pixel(fdf, temp.x, temp.y, get_color(temp, p1, p2, delta));
		adjust_errors(&delta, &temp, &direction, error);
	}
}

/* Draw the whole map */
void	fdf_draw(t_fdf *fdf)
{
	int		x;
	int		y;

	draw_background(fdf);
	y = -1;
	while (++y < fdf->map->height)
	{
		x = -1;
		while (++x < fdf->map->width)
		{
			if (x != fdf->map->width - 1)
				draw_line(fdf, project(new_point(x, y, fdf), fdf),
					project(new_point(x + 1, y, fdf), fdf));
			if (y != fdf->map->height - 1)
				draw_line(fdf, project(new_point(x, y, fdf), fdf),
					project(new_point(x, y + 1, fdf), fdf));
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	fdf_print_manual(fdf);
}
