/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:44:37 by wxuerui           #+#    #+#             */
/*   Updated: 2022/10/16 14:19:09 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Check if the mapfile format is valid */
static void	fdf_check_map_file(char *map_file)
{
	char	**map_name;

	map_name = ft_split(map_file, '.');
	if (ft_2darrlen((void **)map_name) != 2)
		fdf_err_exit(ERR_MAP_FORMAT);
	if (ft_strlen(map_name[1]) == 3 && ft_strncmp(map_name[1], "fdf", 3) == 0)
		ft_free2darr((void **)map_name);
	else
	{
		ft_free2darr((void **)map_name);
		fdf_err_exit(ERR_MAP_FORMAT);
	}
}

/* End program when error happened */
void	fdf_err_exit(char *err_msg)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd(RESET, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}

/* End program Normally */
int	close_win(t_fdf *fdf)
{
	free(fdf->view);
	free(fdf->map->coords);
	free(fdf->map);
	free(fdf);
	ft_printf(MAGENTA"Exited ./fdf\n"RESET);
	exit(0);
}

/* Print the manual on the top left corner of the window */
void	fdf_print_manual(t_fdf *fdf)
{
	void	*mlx;
	void	*win;

	mlx = fdf->mlx;
	win = fdf->win;
	mlx_string_put(mlx, win, 65, 20, TEXT_COLOR, "RTFM");
	mlx_string_put(mlx, win, 15, 40, TEXT_COLOR, "Zoom: +/-");
	mlx_string_put(mlx, win, 15, 60, TEXT_COLOR, "Move: Arrows");
	mlx_string_put(mlx, win, 15, 80, TEXT_COLOR, "Switch mode: M");
	mlx_string_put(mlx, win, 15, 100, TEXT_COLOR, "Rotate:");
	mlx_string_put(mlx, win, 37, 120, TEXT_COLOR, "X-Axis - 2/8");
	mlx_string_put(mlx, win, 37, 140, TEXT_COLOR, "Y-Axis - 4/6");
	mlx_string_put(mlx, win, 37, 160, TEXT_COLOR, "Z-Axis - 3/7");
	mlx_string_put(mlx, win, 15, 180, TEXT_COLOR, "Change Colorscheme: C");
}

/* Program starts */
int	main(int ac, char **av)
{
	t_fdf	*fdf;

	if (ac != 2)
		fdf_err_exit(ERR_USAGE);
	fdf_check_map_file(av[1]);
	fdf = fdf_init(av[1]);
	fdf_draw(fdf);
	fdf_hooks(fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
