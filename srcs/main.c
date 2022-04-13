/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:46:17 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/12 16:56:35 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	main(int argc, char **argv)
{
	pid_t	father;
	int	p;
	int fd1;
	int fd2;
	int	tab[2];
	char buffer[1000];

	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1)
	{
		ft_putstr_fd("Erreur fichier 1", 2);
		exit (-1);
	}
	fd2 = open(argv[argc - 1], O_RDWR);
	if (fd2 == -1)
	{
		ft_putstr_fd("Erreur fichier 2", 2);
		exit (-1);
	}
	tab[0] = fd2;
	tab[1] = fd1;
/*	printf("%s\n", argv[2]);
	printf("%s\n", argv[3]);*/

	p = pipe(tab);

	father = fork();

	if (father == 0)
	{
		close (tab[1]);
		read (tab[0], buffer, 1000);
		printf("pipe : %s", buffer);
		execve(ft_strjoin("/bin/",argv[2]), 0, NULL);
		close (tab[0]);
	}	
	if (father > 0)
	{
		close (tab[0]);
		strcpy(buffer, "Zombicorn\n");
		//wait(NULL);
		write (tab[1], buffer, 10);
		close(tab[1]);
	}

	if (p == -1) //echec creation pipe
		ft_putstr_fd(strerror(errno), 2); // ecrit directement dans sortie erreur

	close (fd1);
	close (fd2);
	return (0);
}


/*
int	main(int argc, char **argv)
{
	//pid_t	father;
	int	p;
	int fd1;
	int fd2;
	int	tab[2];
	char buffer[1000];

	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1)
	{
		ft_putstr_fd("Erreur fichier 1", 2);
		exit (-1);
	}
	fd2 = open(argv[argc - 1], O_RDWR);
	if (fd2 == -1)
	{
		ft_putstr_fd("Erreur fichier 2", 2);
		exit (-1);
	}
	tab[0] = fd2;
	tab[1] = fd1;
	p = pipe(tab);
	if (p == -1) //echec creation pipe
		ft_putstr_fd(strerror(errno), 2); // ecrit directement dans sortie erreur
	write (tab[1], "Zombicorns", 10);
	read (tab[0], buffer, 1000);
	printf("%s", buffer);
	close (fd1);
	close (fd2);
	return (0);
}*/

//executer commandes du shell : /bin/commande  ex /bin/ls
/*
int	main(int argc, char **argv)
{
	pid_t	father;
	father = fork();
	if (father > 0)
	{
		wait(NULL);
		printf("Unicorn\n");
	}
	if (father == 0)
	{
		sleep (3);
		execve("/bin/ls", argv, NULL);
	}	

	return (0);
}
*/
