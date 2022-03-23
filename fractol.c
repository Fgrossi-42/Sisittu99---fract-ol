/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcerchi <mcerchi@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:27:28 by mcerchi           #+#    #+#             */
/*   Updated: 2022/03/23 19:24:59 by mcerchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


void	which_colour(int it, t_env *e)
{
	if (e->col.palette == 0)
	{
		e->col.r = (it % 255) * 3;
		e->col.g = (it % 255) * 3;
		e->col.b = (it % 255) * 3;
	}
	else if (e->col.palette == 1)
	{
		e->col.r = (it * 7 % 255);
		e->col.g = (it % 255);
		e->col.b = (it % 255);
	}
	else if (e->col.palette == 2)
	{
		e->col.r = (it % 255);
		e->col.g = (it * 7 % 255);
		e->col.b = (it % 255);
	}
	else if (e->col.palette == 3)
	{
		e->col.r = (it % 255);
		e->col.g = (it % 255);
		e->col.b = (it * 7 % 255);
	}
	return ;
}

unsigned int	ft_colour(t_pxl x)
{
	unsigned int	colour;

	colour = 0;
	colour |= (unsigned int)(x.b);
	colour |= (unsigned int)(x.g) * (unsigned int)pow(16, 2);
	colour |= (unsigned int)(x.r) * (unsigned int)pow(16, 4);
	return (colour);
}

//**************************************************************************************

void	print_pxl(t_env *e)
{
	int	i;
	int	j;
	int	iterations;

	i = -1;
	j = -1;
	int ciao = 0;
	mlx_clear_window(e->mlx.mlx, e->mlx.win);
	printf("min_x:\t%Lf\t\t\tmax_x:\t%Lf\n", e->mlx.virt_min.x, e->mlx.virt_max.x);
	printf("min_y:\t%Lf\t\t\tmax_y:\t%Lf\n", e->mlx.virt_min.y, e->mlx.virt_max.y);
	t_cpx res;
	while (++i < HEIGHT)
	{
		while (++j < WIDTH)
		{
			res = virtual_to_real(e->mlx, j, i);
			if ((res.x > -0.001 && res.x < 0.001) || (res.y > -0.001 && res.y < 0.001))
			{
				if (ciao == 0)
				{
					ft_putstr_fd("case zero done!\n", 1);
					ciao = 1;
				}
				e->col.r = 255;
				e->col.g = 0;
				e->col.b = 0;
				my_mlx_pixel_put(&e->img, j, i, ft_colour(e->col));
			}
			else
			{
				iterations = e->function(e->mlx, e->var, j, i);
				which_colour(iterations, e);
				my_mlx_pixel_put(&e->img, j, i, ft_colour(e->col));
			}
		}
		j = -1;
	}
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img, 0, 0);
}

// char	**ft_copy_argv(int argc, char **argv)
// {
// 	char	**res;
// 	int		i;

// 	i = 0;
// 	res = (char **)malloc (sizeof(char *) * argc);
// 	if (!res)
// 		return (NULL);
// 	while (i < argc)
// 	{
// 		res[i] = ft_substr(argv[i], 0, ft_strlen(argv[i]));
// 		i++;
// 	}
// 	res[i] = NULL;
// 	return (res);
// }

// void	free_matrix(void **matrix)
// {
// 	int	i;

// 	i = 0;
// 	while (matrix[i])
// 		free(matrix[i++]);
// 	if (matrix)
// 		free(matrix);
// }

//*************************************************************************************

int	main(int argc, char **argv)
{
	t_env	e;

	e.argc = argc;
	e.argv = argv;
	which_function(&e);
	ft_init_e(&e);
	print_pxl(&e);
	mlx_hook(e.mlx.win, 2, 0, ft_command, &e);
	mlx_hook(e.mlx.win, 17, 1L<<0, destroy_win, &e);
	mlx_mouse_hook(e.mlx.win, ft_mouse_manage, &e);
	mlx_loop(e.mlx.mlx);
	// free_matrix((void **)e.argv);
}
