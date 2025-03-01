/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:04:21 by mbousset          #+#    #+#             */
/*   Updated: 2025/03/01 18:11:10 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_input(int fd1, char *delemeter)
{
	char	*line;

	line = NULL;
	while (1)
	{
		if (line && is_delemeter(line, delemeter))
			break ;
		ft_putstr_fd("pipe heredoc> ", 1);
		if (line)
		{
			write(fd1, line, ft_strlen(line));
			free(line);
		}
		line = read_full_line();
		if (!line)
			break ;
	}
	if (!line)
		print_err1("warning: here-document delimited by end-of-file (wanted `",
			delemeter);
	free(line);
}

void	execute_cmd(t_cmd cmd, t_data *prg_data)
{
	char	*new_path;
	int		status;

	if (!cmd.path)
	{
		if (!cmd.args)
			ft_putstr_fd("Mysh: Command not found: \n", 2);
		else
			print_err("command not found", cmd.args[0]);
		ft_exit(prg_data, 127);
	}
	new_path = ft_strjoin(cmd.path, "/");
	if (access(new_path, F_OK) != 0)
	{
		execve(cmd.path, cmd.args, prg_data->envp);
		print_err(strerror(errno), cmd.path);
		status = 127;
	}
	else
	{
		print_err(strerror(21), cmd.path);
		status = 126;
	}
	free(new_path);
	ft_exit(prg_data, status);
}

void	excute_child(t_data *prg_data, char **av, int in_her_doc, int index)
{
	if (index == 0)
	{
		if (in_her_doc)
		{
			if (prg_data->old_fd == -1)
				ft_exit(prg_data, 1);
		}
		else
			in_file_open(prg_data, av[1], &(prg_data->old_fd));
	}
	if (index == prg_data->cmd_nbr - 1)
	{
		out_file_open(prg_data, in_her_doc, av[prg_data->ac - 1],
			&prg_data->out_fd);
		last_child(prg_data->lst_cmd[index], prg_data, prg_data->old_fd,
			prg_data->out_fd);
	}
	else
		child(prg_data, index);
}

void	pipex(t_data *prg_data, int in_her_doc, char **av)
{
	int	i;

	i = 0;
	while (i < prg_data->cmd_nbr)
	{
		if (i != prg_data->cmd_nbr - 1)
			pipe(prg_data->fd);
		prg_data->lst_cmd[i].pid = fork();
		if (prg_data->lst_cmd[i].pid == 0)
		{
			excute_child(prg_data, av, in_her_doc, i);
		}
		else
			parent(&prg_data->old_fd, prg_data->fd);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	prg_data;
	int		in_her_doc;
	int		status;

	prg_data.old_fd = -1;
	validate_arguments(ac, av, &in_her_doc);
	if (in_her_doc)
		read_from_herdoc(av[2], &prg_data.old_fd);
	prg_data.cmd_nbr = ac - 3 - in_her_doc;
	prg_data.lst_cmd = parse_cmd_list(prg_data.cmd_nbr, av + 2 + in_her_doc,
			envp);
	prg_data.envp = envp;
	prg_data.ac = ac;
	pipex(&prg_data, in_her_doc, av);
	wait_for_prc(prg_data.lst_cmd, prg_data.cmd_nbr);
	status = prg_data.lst_cmd[prg_data.cmd_nbr - 1].exit_status;
	free_garbeg(&prg_data);
	return (status);
}
// handel leaks