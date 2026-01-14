/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:26:40 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/14 15:36:43 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	close_fd(int fd1, int fd2)
{
	if (fd1)
		close(fd1);
	if (fd2)
		close(fd2);
}

int	handle_pipe(t_ast *root, t_shell *sh)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (1);
	if (fork() == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_fd(fd[0], fd[1]);
		exit(execute_ast(root->left, sh));
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close_fd(fd[0], fd[1]);
		exit(execute_ast(root->right, sh));
	}
	close_fd(fd[0], fd[1]);
	waitpid(-1, NULL, 0);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
