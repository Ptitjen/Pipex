/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:12:22 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/12 14:17:31 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error_exit(int choice)
{
	if (choice == 1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit (EXIT_FAILURE);
	}
	if (choice == 2)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit (EXIT_FAILURE);
	}
}

void	ft_nb_arg_error(int argc)
{
	if (argc != 5)
	{
		write(2, "\n### Error ###\n\nPlease use format : \
		./pipex inputfile cmd1 cmd2 outputfile\n\n", 76);
		exit (EXIT_FAILURE);
	}
}
