/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:58:36 by byanis            #+#    #+#             */
/*   Updated: 2023/01/30 14:26:19 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	len_ch(char *str, char ch)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ch)
		i++;
	if (str[i] == ch)
		return (i);
	return (-1);
}

int	fileOpen(char *file, int flag)
{
	if (flag == 0)
	{
		if (access(file, F_OK))
		{
			error_handle("File does not exist\n");
			return (0);
		}
		return (open(file, O_RDONLY));
	}
	else
		return (open(file, O_CREAT | O_WRONLY | O_TRUNC));
}

char	*makeCommand(char *path, char *bin)
{
	int		i;
	int		j;
	char	*buff;

	buff = malloc(sizeof(char) * (len_ch(path, 0) + len_ch(bin, 0) + 2));
	if (!buff)
		return (NULL);
	i = 0;
	j = 0;
	while (path[j])
		buff[i++] = path[j++];
	buff[i++] = '/';
	j = 0;
	while (bin[j])
		buff[i++] = bin[j++];
	buff[i] = 0;
	return (buff);
}

char	*commandPath(char *cmd, char **env)
{
	char	*path;
	char	*tmp;
	int		i;
	char	*directory;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (cmd);
	path = ft_strdup(env[i] + 5);
	if (!path)
		error_handle("Error getting path\n");
	while (path && len_ch(path, ':') > -1)
	{
		directory = ft_substr(path, 0, len_ch(path, ':'));
		if (!directory)
			error_handle("Error getting directory\n");
		tmp = makeCommand(directory, cmd);
		if (!tmp)
			error_handle("Error making command\n");
		free(directory);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		free(tmp);
		path += len_ch(path, ':') + 1;
	}
	return (cmd);
}

void	secondCommand(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args)
		error_handle("Error splitting command\n");
	if (len_ch(args[0], '/') != -1)
	{
		if (execve(args[0], args, env) == -1)
			error_handle("Error executing command\n");
	}
	else
	{
		path = commandPath(args[0], env);
		if (!path)
			error_handle("Error getting command path\n");
	}
	if (execve(path, args, env) == -1)
		error_handle("Error executing command\n");
	exit(127);
}

void	firstCommand(char *cmd, char **env, int fileFdIn)
{
	pid_t	pid;
	int		pipefd[2];
	int		status;

	if (pipe(pipefd) == -1)
		error_handle("Pipe error\n");
	pid = fork();
	if (pid == -1)
		error_handle("Fork error\n");
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		waitpid(pid, &status, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		if (fileFdIn == 0)
			exit(1);
		else
			secondCommand(cmd, env);
	}
}

int main(int argc, char **argv, char **env)
{
	int	fileFdIn;
	int	fileFdOut;

	if (argc == 5)
	{
		fileFdIn = fileOpen(argv[1], 0);
		fileFdOut = fileOpen(argv[4], 1);
		dup2(fileFdIn, 0);
		dup2(fileFdOut, 1);
		firstCommand(argv[2], env, fileFdIn);
		secondCommand(argv[3], env);
	}
	else
		error_handle("Wrong number of arguments\n");
	return (1);
}
