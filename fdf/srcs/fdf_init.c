/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:45:26 by wxuerui           #+#    #+#             */
/*   Updated: 2022/10/16 14:24:31 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Get the size(dimensions) of the map */
static void	get_map_size(t_map *map, int fd)
{
	char	*line;
	char	**row;
	int		width;

	map->height = 0;
	map->width = 0;
	line = get_next_line(fd);
	while (line != NULL && ++map->height)
	{
		if ((ft_strlen(line)) == 1 && (ft_strncmp(line, "\n", 1) == 0))
		{
			free(line);
			break ;
		}
		row = ft_split(line, ' ');
		free(line);
		width = ft_2darrlen((void **)row);
		if (map->width == 0)
			map->width = width;
		ft_free2darr((void **)row);
		line = get_next_line(fd);
	}
	close(fd);
}

/* Read the x, y, z(altitude) values from the map */
static void	read_map(t_map *map, int fd)
{
	char	*line;
	char	**row;
	int		i;
	int		j;

	line = get_next_line(fd);
	i = 0;
	map->coords = malloc((map->height * map->width) * sizeof(int));
	while (line != NULL)
	{
		row = ft_split(line, ' ');
		free(line);
		j = -1;
		while (row[++j] != NULL)
			map->coords[i++] = ft_atoi(row[j]);
		ft_free2darr((void **)row);
		line = get_next_line(fd);
		if ((ft_strlen(line)) == 1 && (ft_strncmp(line, "\n", 1) == 0))
		{
			free(line);
			break ;
		}
	}
	close(fd);
}

/* Initialize the view structure */
static t_view	*view_init(t_map *map)
{
	t_view	*view;

	view = malloc(sizeof(t_view));
	if (view == NULL)
		fdf_err_exit(ERR_FDF_INIT);
	view->mode = TWO_D;
	view->colorscheme = DEFAULT;
	view->zoom = fmin((WIDTH - MENU_SIZE) / map->width / 2,
			(HEIGHT - MENU_SIZE) / map->height / 2);
	view->angle_x = 0;
	view->angle_y = 0;
	view->angle_z = 0;
	view->move_x = 0;
	view->move_y = 0;
	return (view);
}

/* Initialize the map structure */
static t_map	*map_init(char *map_file)
{
	int		fd;
	t_map	*map;
	int		i;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		fdf_err_exit(ERR_MAP);
	map = malloc(sizeof(t_map));
	if (map == NULL)
		fdf_err_exit(ERR_MAP_INIT);
	get_map_size(map, fd);
	fd = open(map_file, O_RDONLY);
	read_map(map, fd);
	i = 0;
	map->min = map->coords[0];
	map->max = map->coords[0];
	while (++i < map->height * map->width)
	{
		if (map->coords[i] < map->min)
			map->min = map->coords[i];
		else if (map->coords[i] > map->max)
			map->max = map->coords[i];
	}
	return (map);
}

/* Initialize the fdf structure */
t_fdf	*fdf_init(char *map_file)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (fdf == NULL)
		fdf_err_exit(ERR_FDF_INIT);
	fdf->map = map_init(map_file);
	fdf->view = view_init(fdf->map);
	fdf->mlx = mlx_init();
	if (fdf->mlx == NULL)
		fdf_err_exit(ERR_FDF_INIT);
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "fdf");
	if (fdf->win == NULL)
		fdf_err_exit(ERR_FDF_INIT);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (fdf->img == NULL)
		fdf_err_exit(ERR_FDF_INIT);
	fdf->data_addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel,
			&fdf->size_line, &fdf->endian);
	return (fdf);
}
