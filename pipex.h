/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:04:11 by mbousset          #+#    #+#             */
/*   Updated: 2025/03/01 17:45:51 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "utils_lib/get_next_line.h"
# include "utils_lib/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/* Structures */
typedef struct s_cmd
{
	char	*path;
	char	**args;
	pid_t	pid;
	int		exit_status;
}			t_cmd;

typedef struct s_data
{
	int		old_fd;
	int		out_fd;
	int		fd[2];
	t_cmd	*lst_cmd;
	int		cmd_nbr;
	char	**envp;
	int		ac;
}			t_data;

/* Error Handling */
void		print_err(char *err, char *str);
void		handle_error(void);
void		print_err1(char *err, char *str);
/* Process Management */
// void		child(t_cmd cmd, char **envp, int old_fd, int *fd);
// void		last_child(t_cmd cmd, char **envp, int rd_fd, int out_fd);
void		parent(int *old_fd, int *fd);
void		wait_for_prc(t_cmd *cmd_list, int cmd_nbr);

/* File Handling */
// void		in_file_open(char *path, int *old_fd);
// void		out_file_open(int in_her_doc, char *path, int *out_fd);
int			create_temp_file(int *old_fd);
void		read_from_herdoc(char *delemeter, int *old_fd);

/* Command Parsing */
bool		parse_cmd(t_cmd *cmd, char *av, char **envp);
t_cmd		*parse_cmd_list(int cmd_nbr, char **av, char **envp);
char		*get_cmd_path(char *cmd, char **envp);
bool		cmd_is_path(char *s);
void		process_input(int fd1, char *delemeter);

/* Path Utilities */
char		*get_path(char **paths);
char		*build_cmd_path(char *cmd, char *path);
int			is_dir(char *path);
char		*read_full_line(void);

/* String Utilities */
char		**split_tabs_spaces(char *str);
char		*stor_line(char *line, char *buf);
int			is_delemeter(char *line, char *delemeter);

/* Validation */
void		validate_arguments(int ac, char **av, int *in_her_doc);
// void		execute_cmd(t_cmd cmd, char **env);

/* FUNCTIONS */
void		free_garbeg(t_data *prg_data);
void		out_file_open(t_data *prg_data, int in_her_doc, char *path,
				int *out_fd);
void		last_child(t_cmd cmd, t_data *prg_data, int rd_fd, int out_fd);
void		execute_cmd(t_cmd cmd, t_data *prg_data);
void		child(t_data *prg_data, int index);
void		ft_exit(t_data *prg_data, int status);

void		in_file_open(t_data *prg_data, char *path, int *old_fd);

#endif
