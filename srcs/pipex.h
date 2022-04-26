/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:46:37 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/13 15:51:09 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_cmd{
	char	**path;
	char	*main1;
	char	*main2;
	char	**arg1;
	char	**arg2;
	int		input_file;
	int		output_file;
}	t_cmd;

typedef struct s_split_params
{
	char	**tab;
	size_t	nb_str;
	size_t	i;
	int		k;
	int		iq;
}	t_split_params;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strcpy(char *dst, char *src);
char	**ft_split(char *s, char c);
char	*ft_path(char **env);
char	*ft_strtrim(char *s1, char *set);
char	*ft_command(char **path, char *cmd);
void	ft_process_1(char **argv, char **env, int fd_tab[2], t_cmd cmd);
void	ft_process_2(char **argv, char **env, int fd_tab[2], t_cmd cmd);
void	ft_error_exit_arg(void);
void	ft_error_exit(t_cmd cmd);
void	ft_nb_arg_error(int argc);
void	ft_putstr_fd(char *s, int fd);
void	ft_free_all(t_cmd cmd);
void	ft_free_char_tab(char **tab);
t_cmd	ft_init_fd(char **argv, char **env);
size_t	ft_strlen(char *str);
#endif
