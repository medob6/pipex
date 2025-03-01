/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:02:42 by mbousset          #+#    #+#             */
/*   Updated: 2025/03/01 18:08:15 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(t_data *prg_data, int index)
{
	close(prg_data->fd[0]);
	if (prg_data->old_fd != -1)
	{
		dup2(prg_data->old_fd, STDIN_FILENO);
		close(prg_data->old_fd);
	}
	dup2(prg_data->fd[1], STDOUT_FILENO);
	close(prg_data->fd[1]);
	execute_cmd(prg_data->lst_cmd[index], prg_data);
	ft_exit(prg_data, 1);
}

void	last_child(t_cmd cmd, t_data *prg_data, int rd_fd, int out_fd)
{
	if (rd_fd != -1)
	{
		dup2(rd_fd, STDIN_FILENO);
		close(rd_fd);
	}
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	execute_cmd(cmd, prg_data);
	ft_exit(prg_data, 1);
}

void	parent(int *old_fd, int *fd)
{
	close(fd[1]);
	if (*old_fd >= 0)
		close(*old_fd);
	*old_fd = fd[0];
}

void	wait_for_prc(t_cmd *cmd_list, int cmd_nbr)
{
	int	i;
	int	status;

	i = 0;
	while (i < cmd_nbr)
	{
		waitpid(cmd_list[i].pid, &status, 0);
		cmd_list[i].exit_status = 0;
		if (WIFEXITED(status))
			cmd_list[i].exit_status = WEXITSTATUS(status);
		else if (WIFSTOPPED(status))
			cmd_list[i].exit_status = WSTOPSIG(status);
		else if (WIFSIGNALED(status))
			cmd_list[i].exit_status = WTERMSIG(status);
		i++;
	}
}

int	is_delemeter(char *line, char *delemeter)
{
	size_t	d_len;

	d_len = ft_strlen(delemeter);
	if ((ft_strncmp(line, delemeter, d_len) == 0) && line[d_len] == '\n'
		&& line[d_len + 1] == '\0')
		return (1);
	return (0);
}
