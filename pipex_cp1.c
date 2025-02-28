#include "pipex.h"

char	*get_path(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (!ft_strncmp("PATH=", paths[i], 5))
		{
			return (paths[i]);
		}
		i++;
	}
	return (NULL);
}

char	*build_cmd_path(char *cmd, char *path)
{
	char	*cmd_path;
	char	*tmp;

	cmd_path = NULL;
	tmp = ft_strjoin(path, "/");
	cmd_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (cmd_path);
}

// i do paths[5] becaus PATH= have 5 caracters so i want to skip it and start spliting by ':'

int	is_dir(char *path)
{
	char	*new_path;
	int		ans;

	ans = 0;
	new_path = ft_strjoin(path, "/");
	if (access(new_path, F_OK) == 0)
		ans = 1;
	free(new_path);
	return (ans);
}
char	*get_cmd_path(char *cmd, char **envp)
{
	char	*paths;
	char	**args;
	char	*cmd_path;
	int		i;

	i = 0;
	cmd_path = NULL;
	paths = get_path(envp);
	if (paths == NULL)
		return (NULL);
	args = ft_split(&paths[5], ':');
	while (args[i])
	{
		cmd_path = build_cmd_path(cmd, args[i]);
		if (access(cmd_path, F_OK) == 0 && !is_dir(cmd_path))
			break ;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	free_all(args);
	return (cmd_path);
}

bool	cmd_is_path(char *s)
{
	if (ft_strchr(s, '/'))
		return (true);
	return (false);
}

bool	parse_cmd(t_cmd *cmd, char *av, char **envp)
{
	char	**cmd_args;

	cmd_args = split_tabs_spaces(av);
	if (!cmd_args || cmd_args[0] == NULL)
	{
		cmd->args = NULL;
		cmd->path = NULL;
		return (false);
	}
	cmd->args = cmd_args;
	if (cmd_is_path(cmd_args[0]))
		cmd->path = cmd_args[0];
	else
		cmd->path = get_cmd_path(cmd_args[0], envp);
	return (true);
}

t_cmd	*parse_cmd_list(int cmd_nbr, char **av, char **envp)
{
	t_cmd	*cmd_lst;
	int		i;

	cmd_lst = ft_calloc(cmd_nbr, sizeof(t_cmd));
	i = 0;
	while (i < cmd_nbr)
	{
		parse_cmd(&cmd_lst[i], av[i], envp);
		i++;
	}
	return (cmd_lst);
}

void	print_cmd_list(t_cmd *list_cmd, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		printf("commande [%d] : path = %s ", i, list_cmd[i].path);
		while (list_cmd[i].args[j])
		{
			printf(" %s ", list_cmd[i].args[j]);
			j++;
		}
		i++;
	}
}

void	execute_cmd(t_cmd cmd, char **env)
{
	char	*new_path;

	if (!cmd.path)
	{
		dup2(2, 1);
		if (!cmd.args)
			printf("Mysh: Command not found: \n");
		else
			printf("Mysh: Command not found: %s\n", cmd.args[0]);
		exit(127);
	}
	new_path = ft_strjoin(cmd.path, "/");
	
	if (access(new_path, F_OK) != 0)
	{
		execve(cmd.path, cmd.args, env);
		dup2(2, 1);
		printf("Mysh: %s: %s\n", strerror(errno), cmd.path);
	}
	else
	{
		dup2(2, 1);
		printf("Mysh: %s: %s\n", strerror(21), cmd.path);
	}
	exit(1);
}
void	child(t_cmd cmd, char **envp, int old_fd, int *fd)
{
	close(fd[0]);
	if (old_fd != -1)
	{
		dup2(old_fd, STDIN_FILENO);
		close(old_fd);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execute_cmd(cmd, envp);
	exit(1);
}

void	last_child(t_cmd cmd, char **envp, int rd_fd, int out_fd)
{
	if (rd_fd != -1)
	{
		dup2(rd_fd, STDIN_FILENO);
		close(rd_fd);
	}
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	execute_cmd(cmd, envp);
	exit(1);
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
		if (WIFEXITED(status))
			cmd_list[i].exit_status = WEXITSTATUS(status);
		i++;
	}
}
void	print_error(char *s)
{
	ft_putchar_fd(ft_tolower(s[0]), 2);
	ft_putstr_fd(&s[1], 2);
}

char	*stor_line(char *line, char *buf)
{
	char	*new_buf;

	new_buf = ft_strjoin(buf, line);
	free(buf);
	return (new_buf);
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
char	*read_from_herdoc(char *delemeter, char *buf)
{
	char	*line;
	char	*tmp;

	line = NULL;
	while (1)
	{
		if (line && is_delemeter(line, delemeter))
			break ;
		ft_putstr_fd("pipe heredoc> ", 1);
		if (line != NULL)
		{
			buf = stor_line(line, buf);
			free(line);
		}
		line = get_next_line(0);
		if (line)
		{
			while (line[ft_strlen(line) - 1] != '\n')
			{
				tmp = NULL;
				while (!tmp)
					tmp = get_next_line(0);
				line = stor_line(tmp, line);
				free(tmp);
			}
		}
		else
			break ;
	}
	if (!line)
	{
		dup2(2, 1);
		printf("\nMysh: warning: here-document delimited by end-of-file (wanted `%s')\n",
			delemeter);
	}
	free(line);
	return (buf);
}

void	creat_temp_file(int *old_fd, char *buf)
{
	*old_fd = open("/tmp/temp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*old_fd == -1)
	{
		dup2(2, 1);
		printf("Mysh: %s: /tmp/temp_file\n", strerror(errno));
		exit(1);
	}
	write(*old_fd, buf, ft_strlen(buf));
	free(buf);
	close(*old_fd);
	*old_fd = open("/tmp/temp_file", O_RDONLY);
	unlink("/tmp/temp_file");
}

void	in_file_open(char *path, int *old_fd)
{
	*old_fd = open(path, O_RDONLY);
	if (*old_fd == -1)
	{
		dup2(2, 1);
		printf("Mysh: %s: %s\n", strerror(errno), path);
		exit(1);
	}
}

void	out_file_open(int in_her_doc, char *path, int *out_fd)
{
	if (!in_her_doc)
		*out_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		*out_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*out_fd == -1)
	{
		dup2(2, 1);
		printf("Mysh: %s: %s\n", strerror(errno), path);
		exit(1);
	}
}

int	main(int ac, char **av, char **envp)
{
	int		old_fd;
	int		out_fd;
	t_cmd	*lst_cmd;
	int		i;
	int		cmd_nbr;
	char	*buf;
	int		in_her_doc;
	int		fd[2];

	in_her_doc = (ft_strncmp(av[1], "here_doc", 9) == 0);
	buf = NULL;
	if (ac < 5 + in_her_doc)
	{
		printf("bad argments\n");
		exit(0);
	}
	if (in_her_doc)
	{
		buf = read_from_herdoc(av[2], buf);
	}
	old_fd = -1;
	cmd_nbr = ac - 3 - in_her_doc;
	lst_cmd = parse_cmd_list(cmd_nbr, av + 2 + in_her_doc, envp);
	i = 0;
	while (i < cmd_nbr)
	{
		if (i != cmd_nbr - 1)
			pipe(fd);
		lst_cmd[i].pid = fork();
		if (lst_cmd[i].pid == 0)
		{
			if (i == 0)
			{
				if (in_her_doc)
				{
					// creat_temp_file(&old_fd, buf);
					if (old_fd == -1)
						exit(1);
				}
				else
					in_file_open(av[1], &old_fd);
			}
			if (i == cmd_nbr - 1)
			{
				out_file_open(in_her_doc, av[ac - 1], &out_fd);
				last_child(lst_cmd[i], envp, old_fd, out_fd);
			}
			else
				child(lst_cmd[i], envp, old_fd, fd);
		}
		else
			parent(&old_fd, fd);
		i++;
	}
	wait_for_prc(lst_cmd, cmd_nbr);
	return (lst_cmd[cmd_nbr - 1].exit_status);
}
// handel leaks
//write heredoc to file instead of malloced buf
// split main into smaller functions
// ctrl + d 