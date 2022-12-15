/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transformations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangping <wangping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:45:31 by wxuerui           #+#    #+#             */
/*   Updated: 2022/09/20 15:10:02 by wangping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*rotate about x-axis anticlockwise about angle_x*/
void	rotate_x(int *y, int *z, double angle_x)
{
	int	previous_y;

	previous_y = *y;
	*y = previous_y * cos(angle_x) - *z * sin(angle_x);
	*z = previous_y * sin(angle_x) + *z * cos(angle_x);
}

/*rotate about y-axis anticlockwise about angle_y*/
void	rotate_y(int *x, int *z, double angle_y)
{
	int	previous_x;

	previous_x = *x;
	*x = previous_x * cos(angle_y) + *z * sin(angle_y);
	*z = -previous_x * sin(angle_y) + *z * cos(angle_y);
}

/*rotate about z-axis anticlockwise about angle_z*/
void	rotate_z(int *x, int *y, double angle_z)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(angle_z) - previous_y * sin(angle_z);
	*y = previous_x * sin(angle_z) + previous_y * cos(angle_z);
}
