/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:42:56 by mbousset          #+#    #+#             */
/*   Updated: 2025/03/01 18:17:30 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(const char *str)
{
	int	i;
	int	counter;
	int	in_word;

	i = 0;
	counter = 0;
	in_word = 0;
	while (str[i])
	{
		if ((str[i] != ' ' && str[i] != '\t') && !in_word)
		{
			in_word = 1;
			counter++;
		}
		else if (str[i] == ' ' || str[i] == '\t')
		{
			in_word = 0;
		}
		i++;
	}
	return (counter);
}

static char	**fill_args(char **arr, const char *str)
{
	int	start;
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		start = i;
		while (str[i] && (str[i] != ' ' && str[i] != '\t'))
			i++;
		if (start < i)
		{
			arr[k] = fill_word(str, start, i);
			if (arr[k++] == NULL)
			{
				free_all(arr);
				return (NULL);
			}
		}
	}
	arr[k] = NULL;
	return (arr);
}

char	**split_tabs_spaces(char *str)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (count_words(str) + 1));
	if (!arr)
		return (NULL);
	arr = fill_args(arr, str);
	return (arr);
}

bool	parse_cmd(t_cmd *cmd, char *av, char **envp)
{
	char	**cmd_args;

	cmd_args = split_tabs_spaces(av);
	if (!cmd_args || cmd_args[0] == NULL)
	{
		if (!cmd_args[0])
			free(cmd_args);
		cmd->args = NULL;
		cmd->path = NULL;
		return (false);
	}
	cmd->args = cmd_args;
	if (cmd_is_path(cmd_args[0]))
		cmd->path = ft_strdup(cmd_args[0]);
	else
		cmd->path = get_cmd_path(cmd_args[0], envp);
	// free_all(cmd_args);
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
