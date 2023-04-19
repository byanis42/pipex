/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:08:54 by byanis            #+#    #+#             */
/*   Updated: 2023/04/19 15:26:45 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*mini_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

void	get_path(char *cmd, char *envp[], char **f_path)
{
	char	**paths;
	char	*path;
	char	*path_cmd;
	int		i;
	int		fd;

	i = 0;
	paths = ft_split(ft_strchr(mini_path(envp), '/'), ':');
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin(path, cmd);
		free(path);
		fd = open(path_cmd, O_RDONLY);
		if (fd >= 0)
		{
			*f_path = path_cmd;
			free_matrix(paths);
			close(fd);
			return ;
		}
		free(path_cmd);
		i++;
	}
	free_matrix(paths);
}

char	**split_cmd_arg(char *argv)
{
	char	**cmd_arg;

	cmd_arg = ft_split(argv, ' ');
	return (cmd_arg);
}
