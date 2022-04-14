/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:46:17 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/14 16:12:47 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_nb_arg_error (int argc)
{
	if (argc != 5)
	{
		write(2, "\n### Error ###\n\nPlease use format : ./pipex inputfile cmd1 cmd2 outputfile\n\n", 76);
		exit (-1);
	}
}

void	ft_process_1 (char **argv, char **env, int fd_tab[2]) //fils : avec argv[2]
{
	(void) env;
	int	input_file;
	input_file = open(argv[1], O_RDONLY, 0777);

	if (input_file == -1)
	{
		ft_putstr_fd("### Input file error ###", 2);
		exit (-1);
	}			
	
	char **commande;
	commande = ft_split(argv[2], ' ');

	//write(fd_tab[1], "zombicorn", 9); test pipe : marche

	dup2(input_file, STDIN_FILENO); //entree standard = 0 => le input file devient entree	
	dup2(fd_tab[1], STDOUT_FILENO); // sortie standard = 1 => la case 1 de la pipe devient sortie
	execve(ft_strjoin("/bin/", commande[0]), commande, env);
	close(fd_tab[0]);
	close(input_file);	
}

void	ft_process_2 (char **argv, char **env, int fd_tab[2])//parent : avec argv[3]
{
	int		output_file;
	char	**commande;	
	
	output_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (output_file == -1)
	{
		ft_putstr_fd("### Output file error ###", 2);
		exit (-1);
	}	
	commande = ft_split(argv[3], ' ');	
	
	/* test pipe : marche */
	/*char *buffer = malloc(sizeof(char)*1000);
	read(fd_tab[0], buffer, 1000 );
	write(output_file, buffer, 1000); */
	
	dup2(fd_tab[0], STDIN_FILENO); 
	dup2(output_file, STDOUT_FILENO); 	
	execve(ft_strjoin("/bin/", commande[0]), commande, env); //options - ok
	close(fd_tab[1]);
	close(output_file);
}

//pipe marche
//commands marchent avec options
//arrive pas a executer sur le contenu de file1?
int	main(int argc, char **argv, char **env)
{
	pid_t	process;
	int		p;
	int		fd_tab[2];

	ft_nb_arg_error (argc);
	p = pipe(fd_tab);
	if (p == -1)
	{
		write(2, "\n### Error while creating pipe ###\n\n", 36);
		exit (-1);
	}
	process = fork();
	if (process == -1)
	{
		write(2, "\n### Error while executing fork ###\n\n", 37);
		exit (-1);
	}	
	if (process == 0)
		ft_process_1(argv, env, fd_tab);	
	waitpid(process, NULL, 0);
	ft_process_2(argv, env, fd_tab);
	close(fd_tab[0]);
	close(fd_tab[1]);
	return (0);
}

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
