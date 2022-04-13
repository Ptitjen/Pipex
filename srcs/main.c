/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:46:17 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/13 17:15:31 by jeulliot         ###   ########.fr       */
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
	char *buffer;

	buffer = malloc(sizeof(char) * 1000);
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

	father = fork();


		
	if (father == 0)
	{
		close (tab[1]);
		char **tabc1;
		char **commande2;
		char **argcom2;
//	wait (NULL);
		tabc1 = malloc(sizeof(char*) * 2);		
		read (tab[0], buffer, 1000);
		tabc1[0] = ft_strcpy(tabc1[0], buffer);
		tabc1[1] = "\n";
		printf("apres pipe : %s", tabc1[0]);
		printf("\n");
		printf("commande 2 full : %s\n", argv[3]);
		commande2 = ft_split(argv[3], ' ');
		argcom2 = ft_split(argv[1], ' ');
		printf("commande 2 : %s\n", commande2[0]);		
		
		execve(ft_strjoin("/bin/", commande2[0]), argcom2, NULL); 
		close (tab[0]);
	}	
	if (father > 0)
	{
		close (tab[0]);
		char **tabc;
		char **commande;
		char **bli;
		bli = malloc(sizeof(char*) * 2);
		bli[0] = "";
		bli[1] = 0;
		tabc = malloc(sizeof(char*) * 2);
		
		buffer = ft_strcpy(buffer, "file1");		
		printf("commande 1 full : %s\n", argv[2]);
		commande = ft_split(argv[2], ' ');
		printf("commande 1 : %s\n", commande[0]);
		//printf("buffer : %s\n", buffer);
		write (tab[1], buffer, 1000);
		execve(ft_strjoin("/bin/", commande[0]), bli, NULL); // voir comment recup le resultat pour pouvoir le mettre dans buffer
		close(tab[1]);
	}


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
