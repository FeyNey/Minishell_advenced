/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:59:27 by aglampor          #+#    #+#             */
/*   Updated: 2024/10/12 00:44:02 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**build_pipe(int nb_t)
{
	int	**pipefd;
	int	i;

	pipefd = malloc(sizeof(int *) * (nb_t + 1));
	if (!pipefd)
		return (NULL);
	i = 0;
	while (i < nb_t)
	{
		pipefd[i] = malloc(sizeof(int) * 2);
		if (!pipefd[i])
		{
			free_pipes(pipefd);
			return (NULL);
		}
		pipe(pipefd[i]);
		i++;
	}
	pipefd[i] = NULL;
	return (pipefd);
}

void	close_pipe(int **pfd)
{
	int	i;

	i = 0;
	while (pfd[i])
	{
		close(pfd[i][0]);
		close(pfd[i][1]);
		i++;
	}
}

void	handle_pip(int **pipefd, int i)
{
	if (i != 0)
		dup2(pipefd[i - 1][0], 0);
	if (pipefd[i + 1])
		dup2(pipefd[i][1], 1);
	close_pipe(pipefd);
}

void	free_pipes(int **pipefd)
{
	int	i;

	i = 0;
	while (pipefd[i])
	{
		if (pipefd[i])
			free(pipefd[i]);
		i++;
	}
	free(pipefd);
}

void	daddy_rout(int **pfd, int nb_fork, pid_t last_pid)
{
	int		i;
	int		status;

	i = 0;
	close_pipe(pfd);
	waitpid(last_pid, &status, 0);
	free_pipes(pfd);
	while (i < nb_fork - 1)
	{
		waitpid(-1, &status, 0);
		i++;
	}
}
