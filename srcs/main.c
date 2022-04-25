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

char	*ft_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env ++;
	return (*env + 5);
}

char	*ft_command(char **path, char *cmd)
{
	char	*str;
	char	*cmd_out;

	if (cmd[0] == '/')
		if (access(cmd, 0) == 0)
			return (cmd);
	while (*path)
	{
		str = ft_strjoin(*path, "/");
		cmd_out = ft_strjoin(str, cmd);
		free(str);
		if (access(cmd_out, 0) == 0)
			return (cmd_out);
		free(cmd_out);
		path++;
	}
	return (NULL);
}

void	ft_process_1(char **argv, char **env, int fd_tab[2], t_cmd cmd)
{
	
	cmd.arg1 = ft_split(argv[2], ' ');
	cmd.main1 = ft_command(cmd.path, cmd.arg1[0]);
	if (cmd.main1 == NULL)
	{
		ft_putstr_fd("Command not found\n", 2);
		exit(127);
	}
	if (cmd.input_file != -1)
	{
		dup2(cmd.input_file, STDIN_FILENO);
		dup2(fd_tab[1], STDOUT_FILENO);
		close(fd_tab[0]);
		if (execve(cmd.main1, cmd.arg1, env) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			free(cmd.main1);
			ft_free_char_tab(cmd.arg1);
			ft_free_char_tab(cmd.path);
			exit (1);
		}
		close(cmd.input_file);
	}		
	free(cmd.main1);
	ft_free_char_tab(cmd.arg1);	
}

void	ft_process_2(char **argv, char **env, int fd_tab[2], t_cmd cmd)
{

	cmd.arg2 = ft_split(argv[3], ' ');
	cmd.main2 = ft_command(cmd.path, cmd.arg2[0]);
	if (cmd.main2 == NULL)
	{
		ft_putstr_fd("Command not found\n", 2);
		exit(127);
	}
	dup2(fd_tab[0], STDIN_FILENO);
	close(fd_tab[1]);
	dup2(cmd.output_file, STDOUT_FILENO);
	if (execve(cmd.main2, cmd.arg2, env) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit (1);
	}
	close(cmd.output_file);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	process;
	int		p;
	int		fd_tab[2];
	t_cmd	cmd;

	ft_nb_arg_error(argc);
	p = pipe(fd_tab);
	if (p == -1)
		ft_error_exit_arg();
	cmd.path = ft_split(ft_path(env), ':');
	cmd.input_file = open(argv[1], O_RDONLY);
	if (cmd.input_file == -1)
		ft_putstr_fd(strerror(errno), 2);
	cmd.output_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (cmd.output_file == -1)
	{
		ft_putstr_fd(strerror(errno), 2);		
		exit (1);
	}
	process = fork();
	if (process == -1)
		ft_error_exit(cmd);
	if (process == 0)
		ft_process_1(argv, env, fd_tab, cmd);
	else 
	{	
		waitpid(process, NULL, WNOHANG);		
		ft_process_2(argv, env, fd_tab, cmd);			
	}
	ft_free_all(cmd);
	return (0);
}
