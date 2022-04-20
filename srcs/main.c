/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:46:17 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/18 12:24:11 by jeulliot         ###   ########.fr       */
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

char	*ft_path(char **env)
{
	while(ft_strncmp("PATH", *env, 4))
		env ++;
	return(*env + 5);
}

char	*ft_command(char **path, char *cmd)
{
	char *str;
	char *cmd_out;

	while(*path)
	{
		str=ft_strjoin(*path, "/");
		cmd_out = ft_strjoin(str, cmd);
		free(str);
		if (access(cmd_out, 0) == 0)
			return(cmd_out);
		free(cmd_out);
		path++;
	}
	return(NULL);
}

void	ft_process_1 (char **argv, char **env, int fd_tab[2], t_cmd cmd)
{
	int	input_file;
	input_file = open(argv[1], O_RDONLY);

	if (input_file == -1)
	{
		ft_putstr_fd("### Input file error ###", 2);
		exit (-1);
	}			
	cmd.arg1 = ft_split(argv[2], ' ');	
	cmd.main1= ft_command(cmd.path, cmd.arg1[0]);
	dup2(input_file, STDIN_FILENO);		
	dup2(fd_tab[1], STDOUT_FILENO);
	close(fd_tab[0]);
	execve(cmd.main1, cmd.arg1, env);
	close(input_file);		
}

void	ft_process_2 (char **argv, char **env, int fd_tab[2], t_cmd cmd)
{
	int		output_file;
	
	output_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (output_file == -1)
	{
		ft_putstr_fd("### Output file error ###", 2);
		exit (-1);
	}	
	cmd.arg2 = ft_split(argv[3], ' ');	
	cmd.main2= ft_command(cmd.path, cmd.arg2[0]);
	dup2(fd_tab[0], STDIN_FILENO); 
	close(fd_tab[1]);
	dup2(output_file, STDOUT_FILENO);	
	execve(cmd.main2, cmd.arg2, env);	
	close(output_file);
}

void	ft_error_exit(int choice) //ajouter les trucs a free
{
	if (choice == 1)
	{
		write(2, "\n### Error while creating pipe ###\n\n", 36);
		exit (-1);
	}
	if (choice == 2)
	{
		write(2, "\n### Error while executing fork 1###\n\n", 38);
		exit (-1);
	}	
	if (choice == 3)
	{
		write(2, "\n### Error while executing fork 2###\n\n", 38);
		exit (-1);
	}
}

int	main(int argc, char **argv, char **env)
{
	pid_t	process1;
	pid_t 	process2;
	int		p;
	int		fd_tab[2];
	t_cmd 	cmd;

	ft_nb_arg_error (argc);
	p = pipe(fd_tab);
	if (p == -1)
		ft_error_exit(1);
	cmd.path = ft_split(ft_path(env), ':');
	process1 = fork();
	if (process1 == -1)
		ft_error_exit(2);
	if (process1 == 0)
		ft_process_1(argv, env, fd_tab, cmd);
	waitpid(process1, NULL, 0);
	process2 = fork();
	if (process2 == -1)
		ft_error_exit(3);
	if (process2 == 0)
		ft_process_2(argv, env, fd_tab, cmd);
	return (0);
}

