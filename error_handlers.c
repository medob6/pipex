/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:45:58 by mbousset          #+#    #+#             */
/*   Updated: 2025/03/01 18:29:44 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(void)
{
	print_err(strerror(errno), "/tmp/temp_file");
	exit(1);
}

void	print_err(char *err, char *str)
{
	char	*buffer;
	char	*tmp;

	buffer = ft_strjoin("Mysh: ", err);
	tmp = buffer;
	buffer = ft_strjoin(tmp, ": ");
	free(tmp);
	tmp = buffer;
	buffer = ft_strjoin(tmp, str);
	free(tmp);
	tmp = buffer;
	buffer = ft_strjoin(tmp, "\n");
	free(tmp);
	ft_putstr_fd(buffer, 2);
	free(buffer);
}

void	validate_arguments(int ac, char **av, int *in_her_doc)
{
	*in_her_doc = (ft_strncmp(av[1], "here_doc", 9) == 0);
	if (ac < 5 + *in_her_doc)
	{
		ft_putstr_fd("bad arguments\n", 1);
		exit(0);
	}
}

void	print_err1(char *err, char *str)
{
	char	*buffer;
	char	*tmp;

	buffer = ft_strjoin("\nMysh: ", err);
	tmp = buffer;
	buffer = ft_strjoin(tmp, str);
	free(tmp);
	tmp = buffer;
	buffer = ft_strjoin(tmp, "')\n");
	free(tmp);
	ft_putstr_fd(buffer, 2);
	free(buffer);
}
