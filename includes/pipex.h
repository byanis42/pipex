/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:33:10 by byanis            #+#    #+#             */
/*   Updated: 2023/01/25 17:34:53 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct s_pipex
{
	int pid;
	int pipefd[2];
}				t_pipex;

/*Utils */

 int		error_handle(char *str);
// int		open_file1(char **argv);
// int		open_file2(char **argv);
// int		pipe_setup(int pipefd[]);

#endif
